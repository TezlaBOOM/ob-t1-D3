#include <iostream>
#include <string>
#include <vector>
#include <list>


using namespace std;
class samochod{
    friend class garaz;
    friend class osoba;
  private:
    string marka;
    string model;
    string numerRejestracyjny[3];
    int iloscdrzwi;
    double pojemnosc;
    double srednieSpalanie;
protected:
    static int iloscSamochodow;
private:
    ObliczSpalanie(double dlugoscTrasy){
    double spalanie;
    spalanie = (srednieSpalanie * dlugoscTrasy) / 100.0;
    return spalanie;
    }
public:
   samochod(){
    marka = "nieznady";
    model = "nieznady";
    iloscdrzwi = 0;
    pojemnosc = 0.0;
    srednieSpalanie = 0.0;
    iloscSamochodow ++;
}
  samochod(string marka_,string model_,string numerRejestracyjny_,int iloscDrzwi_, double pojemnoscSilnika_,double yd){
    marka = marka_;
    model = model_;
    iloscdrzwi = iloscDrzwi_;
    pojemnosc = pojemnoscSilnika_;
    srednieSpalanie = yd;
    iloscSamochodow ++;
    numerRejestracyjny[iloscSamochodow] = numerRejestracyjny_;
    }


 void WypisInfo(){
 cout<<"marka: "<<marka <<" model: "<<model <<" ilosc drzwi: "<<iloscdrzwi <<" pojemnosc: "<<pojemnosc <<" srednie spalanie: "<<srednieSpalanie <<endl;

}

 ObliczKosztPrzejazdu(double dlugoscTras,double cenaPaliwa){
     double kosztPrzejazdu;
     kosztPrzejazdu = ObliczSpalanie(dlugoscTras) * cenaPaliwa;
     return kosztPrzejazdu;
     }
void WypiszIloscSamochodow(){
 cout<<"ilosc samochodw "<<iloscSamochodow <<endl;
}



 };
 int samochod::iloscSamochodow =0;

class garaz{
    friend class samochod;
    friend class osoba;
public:
    string adres;
    int pojemnosc;
    int liczbaSamochodow = 0;
    vector<samochod*> samochody;

public:
    garaz(){
        adres = "nieznady";
        pojemnosc = 0;
      samochody = vector<samochod*>();
};
    garaz(string adres_, int pojemnosc_){
        adres = adres_;
        pojemnosc =  pojemnosc_;
        samochody = vector<samochod*>(pojemnosc);

};

void WprowadzSamochod(samochod *samochod_)
{
	if (liczbaSamochodow == pojemnosc)
	{
		cout << "Garaz jest już pełny" << endl;
	}
	else
	{
		samochody[liczbaSamochodow] = samochod_;
		liczbaSamochodow += 1;
	}
}


  void WyprowadzSamochod()
{
	if (liczbaSamochodow == 0)
	{
		cout << "Garaż jest pusty" << endl;
	}
	else
	{
		samochody[liczbaSamochodow - 1] = nullptr;
		liczbaSamochodow -= 1;
	}
}



void setAdres(string value){
	adres = value;
}

string getAdres(){
	return adres;
}

void setPojemnosc(int value){
	pojemnosc = value;
	samochody = vector<samochod*>(pojemnosc);
}

int getPojemnosc(){
	return pojemnosc;
}





void WypiszInfo()
{
	for (int i = 1; i <= liczbaSamochodow; i++)
	{
		cout << "Samochód na miejscu parkingowym numer " << i << endl;
		samochody[i - 1] -> WypisInfo();
	}

}
};

class osoba :public samochod{
    friend class garaz;
    friend class samochod;
private:
    string imie;
    string nazwisko;
    string adreszamieszkania;
    list <samochod>samochod;
    int liczbaSamochodow = 0;
public:
    osoba(){
        imie = "nieznany";
        nazwisko = "nieznany";
        adreszamieszkania = "nieznany";
        liczbaSamochodow = 0;
    };
    osoba(string imie_,string nazwisko_,string adres_,int liczbaSamochodow_){
        imie = imie_;
        nazwisko = nazwisko_;
        adreszamieszkania = adres_;
        liczbaSamochodow = liczbaSamochodow_;
    };
    void dodajsamochod(string nrRejestracyjny){
        if(liczbaSamochodow >= 3){
            cout<<"przekroczono liczbe zamochodow ~ max 3"<<endl;
        }else{
           numerRejestracyjny[liczbaSamochodow]=nrRejestracyjny;
            liczbaSamochodow++;
        }
    };
    void usunsamochod(string nrRejestracyjny){
         if(liczbaSamochodow < 0){
            cout<<"nie ma  przypisanych samochodow"<<endl;
        }else{
            for(int i=0;i<3;i++){
                if(numerRejestracyjny[i]==nrRejestracyjny){
                     numerRejestracyjny[i] = "";
                    liczbaSamochodow--;
                }



            }

        }
    };
    void WypiszInfo(){
    cout<<imie<<" "<<nazwisko<<" "<<adreszamieszkania<< " "<<endl;

        for(int i=0;i<liczbaSamochodow;i++){
               cout<<" "<< numerRejestracyjny[i] <<" "<<endl;
        }
            cout<<endl;

    };






    };


int main()
{
    samochod *s1 = new samochod("Fiat", "126p","PKA0001",2, 650, 6.0);
    s1 -> WypiszIloscSamochodow();
    s1 -> WypisInfo();
    cout<<s1 -> ObliczKosztPrzejazdu(100,3)<<endl;
    cout<<"--------------------------"<<endl;
    samochod *s2= new samochod("Syrena", "105","PKA0002", 2, 800, 7.6);
    s2 -> WypiszIloscSamochodow();
    s2 ->WypisInfo();
    cout<<s2 ->ObliczKosztPrzejazdu(100,5)<<endl;



    garaz *g1 = new garaz();
	g1 -> setAdres("ul. Garażowa 1");
	g1 -> setPojemnosc(1);
	garaz *g2 = new garaz("ul. Garażowa 2", 2);
	g1 -> WprowadzSamochod(s1);
	g1 -> WypiszInfo();
	g1 -> WprowadzSamochod(s2);
	g2 -> WprowadzSamochod(s2);
	g2 -> WprowadzSamochod(s1);
	g2 -> WypiszInfo();
	g2 -> WyprowadzSamochod();
	g2 -> WypiszInfo();
	g2 -> WyprowadzSamochod();
	g2 -> WyprowadzSamochod();
    osoba *o1 = new osoba("stachu","Jons","magnacka 3/4",1);
    cout<<"---"<<endl;
    o1 ->dodajsamochod("PKA0002");
    o1 ->WypiszInfo();




    return 0;
}
