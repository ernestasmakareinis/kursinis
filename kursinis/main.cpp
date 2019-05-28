#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

void SaliesPasirinkimas( int allcountries, bool& zaidejaspasirinko);
void StiliuTaskai();
void StiliuPasirinkimuLentele(int& stiliausnr, bool zaidejaspasirinko);
int StiliausPasirinkimasUser ( int a );
void PradziosPavadinimas();
void convert (string& s);

string zaidejovardas = "nepasirinkote";
int StilTaskai [10];
string Stiliai [10];
int random;


class Salis{
  private:
  string vardas;
  int taskai;
  int originalustaskai;
  public:
    /**< konstruktoriai */
  Salis ()
  {
    vardas = "nera vardo";
    taskai = 0;
  }
  Salis (string a)
  {
      vardas = a;
  }
  Salis (int a)
  {
      taskai = a;
  }
  Salis (string a, int b)
  {
      vardas = a;
      taskai = b;
  }
    /**< kopijavimo konstruktorius */
  Salis (const Salis &Salis2)
  {
  vardas = Salis2.vardas;
  taskai = Salis2.taskai;
  }
  void setTaskai( int x){
    taskai = x;
    originalustaskai = x;
  }
  void resetTaskai(){
    taskai = originalustaskai;
  }
  void addTaskai( int x){
    taskai = taskai + x;
  }
  int getTaskai(){
    return taskai;
  }
  void setVardas(string a){
    vardas = a;
  }
  string getVardas(){
    return vardas;
  }
  /**< unarinio operatorio perkrovimas */
  void operator-(){
      taskai--;
  }
};

class Zaidejas : public Salis{
    public:
        int kelintaszaidejas;
        Zaidejas (int numeris)
        {
            kelintaszaidejas = numeris;
            cout << "Sveikas numeri " << numeris << "\n";
        }

};

/**< ----------------------MAIN------------------------- */
int main() {
  int points, allcountries(0), stiliausnr(0), didziausitaskai(0);
  bool empty_line = false; bool zaidejaspasirinko = false;
  string laimetojas;

  srand(time(0));           //Atsiktine tvarka generuojamas skaicius
  ifstream inFile;
  vector<Salis*> salys;
  inFile.open("salys.txt");
  while(!empty_line){
        string pavadinimas;
      Salis *aktSalis = new Salis();
      inFile >> pavadinimas;
    if(pavadinimas.empty()){
      empty_line = true;
    }else{
      aktSalis->setVardas(pavadinimas);
      inFile >> points;
      aktSalis->setTaskai(points);
      salys.push_back(aktSalis);
      allcountries++;
    }
  }
  inFile.close();

  int zaidejuskaicius;
  vector<Zaidejas*> zaidejai;
  cout << "kiek zais zaideju? ";
  cin >> zaidejuskaicius;
  for(int i = 1; i <= zaidejuskaicius ; i++)
    {
    Zaidejas aktZaidejas(i);
    cout << "\n";
    PradziosPavadinimas();    //Uzraso EUROVIZIJA
    SaliesPasirinkimas(allcountries, zaidejaspasirinko);
    StiliuPasirinkimuLentele(stiliausnr, zaidejaspasirinko);
    cout << "\n";
    cout << endl;
    cout << "Spauskit ENTER"<<endl;
    cout << endl;
    cin.ignore();
    for(Salis *sal: salys){
        string vardas;
        random = rand() % 10 ;      //generuoja skaiciu nuo 0 iki 9
        sal->resetTaskai();
        sal->addTaskai(random+1);   //prideda atsitiktini skaiciu nuo 1 iki 10
        vardas = sal->getVardas();
        if(vardas != zaidejovardas){
            int saliesstilius = random;
            cout << vardas << " \t" << sal ->getTaskai() << " + \t" << StilTaskai[saliesstilius];
            sal->addTaskai(StilTaskai [saliesstilius]);
            cout << " = " <<sal->getTaskai() << "\t  [ " <<Stiliai[saliesstilius]<< " ]\n";
            if(zaidejaspasirinko)
            cin.ignore();
        }else{
            convert(vardas);
            cout << "-> "<< vardas << " \t" << sal ->getTaskai() << " + \t" << StilTaskai[stiliausnr];
            sal->addTaskai(StilTaskai[stiliausnr]);
            cout << " = " <<sal->getTaskai() <<  "\t [ " <<Stiliai[stiliausnr]<< " ]\n";;
            cin.ignore();
        }
    if(sal->getTaskai() > didziausitaskai){
        didziausitaskai = sal->getTaskai();
        laimetojas = sal->getVardas();
    }
  }
  if(zaidejovardas == laimetojas){
    cout << "\n*** JUS LAIMEJOTE! ***\n";
    cout << "\nZaidete uz sali - " << zaidejovardas <<" . Surinkote " << didziausitaskai << " tasku!\n";
    cin.ignore();
  }else {
    cout << endl;
    cout << "Jusu salis buvo - " << zaidejovardas;
    cout << endl;
    cout << "\nLaimejo " << laimetojas << " su " << didziausitaskai <<" taskais/u\n";
    cin.ignore();
  }
        }
  return 0;

}
/**< ----------------------MAIN-END-------------------- */

void SaliesPasirinkimas(int allcountries, bool& zaidejaspasirinko){
  int nr(0), innr, taskai;
  string pavadinimas;
  string SaliuMasyvas [allcountries];
  ifstream inFile;
  inFile.open("salys.txt");
  for(int i = 0 ; i < allcountries ; i++){
    inFile >> pavadinimas;
    inFile >> taskai;
    cout << nr+1 << ") " << pavadinimas <<endl;
    SaliuMasyvas[nr] = pavadinimas;
    nr++;
  }
  cout << endl;
  cout << "Pasirink sali ivesdamas jos numeri: ";
  cout << endl;
  cin >> innr;
  if(innr > nr || innr < 1 ){
    cout << "tokios salies numerio nera"<<endl;
    zaidejaspasirinko = false;
  }else{
    zaidejovardas = SaliuMasyvas[innr-1];
    zaidejaspasirinko = true;
  }
  inFile.close();
}

void StiliuTaskai(){
    bool empty_line = false;
    string stilius, stilius2;
    int counter(0);
    srand(time(0));
    ifstream inFile;
    inFile.open("stiliai.txt");
      while(!empty_line){
            inFile >> stilius;
        if(stilius==stilius2  || stilius.empty()){
            empty_line = true;
        }else{
            random = rand() % 10 + 1;
            StilTaskai[counter] = random;
            Stiliai[counter]=stilius;
            stilius2 = stilius;
        }
        counter++;
    }
    inFile.close();
}

void StiliuPasirinkimuLentele(int& stiliausnr, bool zaidejaspasirinko){
      StiliuTaskai();
      bool empty_line = false;
      string stilius, stilius2;
      int nr(1);
      ifstream inFile;
      inFile.open("stiliai.txt");

      cout << "  === S T I L I A I ===" << endl;

        while(!empty_line){
        inFile >> stilius;
        if(stilius==stilius2  || stilius.empty()){
            empty_line = true;
        }else{
            cout << nr << ") " << stilius <<endl;
            nr++;
            stilius2 = stilius;
        }
      }
      if(zaidejaspasirinko){
      stiliausnr = StiliausPasirinkimasUser(stiliausnr);
      }
}

int StiliausPasirinkimasUser ( int a ){
cout << endl;
      cout << "Iveskite norimo stiliaus numeri: \n" ;
      cin >> a;
      a = a-1;
return a;
}

void convert(string& s){
    for(int i = 0; i < s.length() ; i++){
        s[i] = toupper(s[i]);
    }
}

void PradziosPavadinimas(){
cout << " ------------------------- " <<endl;
cout << "|                         |" <<endl;
cout << "|   E U R O V I S I O N   |" <<endl;
cout << "|                         |" <<endl;
cout << " ------------------------- " <<endl;
}
