#include<iostream>
#include<string>
#include<cstdlib>
#include<cstdio>
#include<time.h>
#include<fstream>
#include<cstring>
#include<unistd.h>
#include<termios.h>

/*
 * Projekt na zajecia z logiki
 * Arkadiusz Szot
 *
 * */

using namespace std;

int lvl;
int K;
int sword, cav, bow;
int opsword, opcav, opbow;
long long wynik;
int TabNot[2][3] = {
                { 0, 2, 1 },
                { 1, 2, 0 },
         };
int TabOr[9][3] = {
                { 0, 0, 0 },
                { 0, 2, 2 },
                { 0, 1, 1 },
                { 2, 0, 2 },
                { 2, 2, 2 },
                { 2, 1, 1 },
                { 1, 0, 1 },
                { 1, 2, 1 },
                { 1, 1, 1 },
        };
int TabAnd[9][3] = {
                { 0, 0, 0 },
                { 0, 2, 0 },
                { 0, 1, 0 },
                { 2, 0, 0 },
                { 2, 2, 2 },
                { 2, 1, 2 },
                { 1, 0, 0 },
                { 1, 2, 2 },
                { 1, 1, 1 },
        };
int TabImpl[9][3] = {
                { 0, 0, 1 },
                { 0, 2, 1 },
                { 0, 1, 1 },
                { 2, 0, 2 },
                { 2, 2, 2 },
                { 2, 1, 1 },
                { 1, 0, 0 },
                { 1, 2, 2 },
                { 1, 1, 1 },
        };

void ClearScreen(){
    cout << string( 100, '\n' );
}

int mygetch( ) {
        struct termios oldt,  newt;
        int ch;
        tcgetattr( STDIN_FILENO, &oldt );
        newt = oldt;
        newt.c_lflag &= ~( ICANON | ECHO );
        tcsetattr( STDIN_FILENO, TCSANOW, &newt );
        ch = getchar();
        tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
        return ch;
}

void converttotab(string name, int T[][3], int a ){
    ifstream plik;
    char odczyt;
    plik.open( name.c_str() );
    if( plik.good() == true ){
        cout << "Access to " << name <<" permitted!" << endl;
        for(int i=0 ; i < a ; i++){
                for(int j=0 ; j < 3 ; j++) {
                        plik >> odczyt ;
                        if(odczyt != '1' and odczyt != '0')
                                T[i][j]=2;
                        else
                        {
                          T[i][j]=odczyt;
                          T[i][j]-=48;
                         }
                }
        }
    }
      else
    {
        cout<< "Access to " << name <<" forbidden" << endl;
        cout<<" Try start a program again with correct parameters! " << endl;
        cout<<"Correct way to start a program: "<<endl;
        cout<<"run_my_game --not not.txt --impl impl.txt --or or.txt --and and.txt"<<endl;
    }
}

int getkey(){
    char key;
    do{
        key=mygetch();
    }while(key!='0' && key!='1' && key!='2' && key!='3');
    if(key=='0') return 0;
    if(key=='1') return 1;
    if(key=='2') return 2;
    if(key=='3') return 3;
}

int opp(int arg1){
        if(arg1==0) return 1;
        else if(arg1==1) return 0;
        else if(arg1==2) return 2;
}

int alt(int arg1, int arg2){
        for(int i=0; i<9; i++)
                if(TabOr[i][0]==arg1 && TabOr[i][1]==arg2) return TabOr[i][2];
}

int kon(int arg1, int arg2){
        for(int i=0; i<9; i++)
                if(TabAnd[i][0]==arg1 && TabAnd[i][1]==arg2) return TabAnd[i][2];
}
int impl(int arg1, int arg2){
        for(int i=0; i<9; i++)
                if(TabImpl[i][0]==arg1 && TabImpl[i][1]==arg2) return TabImpl[i][2];
}

void showforces(){
        cout<<"______________________________________________________"<<endl;
        cout<<"____________________ ALLY  FORCES  ___________________"<<endl;
        cout<<"______________________________________________________"<<endl;
        cout<<"___ SWORDS : "<<sword<<endl;
        cout<<"______________________________________________________"<<endl;
        cout<<"___ CAVALRY : "<<cav<<endl;
        cout<<"______________________________________________________"<<endl;
        cout<<"___ BOWS : "<<bow<<endl;
        cout<<"______________________________________________________"<<endl;
        cout<<"____________________ ENEMY FORCES  ___________________"<<endl;
        cout<<"______________________________________________________"<<endl;
        cout<<"___ SWORDS : "<<opsword<<endl;
        cout<<"______________________________________________________"<<endl;
        cout<<"___ CAVALRY : "<<opcav<<endl;
        cout<<"______________________________________________________"<<endl;
        cout<<"___ BOWS : "<<opbow<<endl;
        cout<<"______________________________________________________"<<endl;
}

int neguj(int who){
        if(who==0) return 2;
        if(who==1) return 0;
        if(who==2) return 1;
}

void makeloss(int who){
        if(who==0) sword*=0.8;
        if(who==1) cav*=0.8;
        if(who==2) bow*=0.8;
        if(sword < 50)sword=0;
        if(cav<50)cav=0;
        if(bow<50) bow=0;
}

void makegains(int who){
        if(who==0) opsword*=0.8;
        if(who==1) opcav*=0.8;
        if(who==2) opbow*=0.8;
        if(opsword < 50)opsword=0;
        if(opcav<50)opcav=0;
        if(opbow<50) opbow=0;

}

void makestatement( int arg1, int arg2){
        int switcher=rand()%5;
        int switch2=rand()%5;
        if(switch2==switcher) switch2++;
        switch2%=5;
                cout<<"___________________________________________________________________"<<endl;
        if( arg1==1 ){
                if(switcher==0) cout<<"Kapitan mowi, ze na wlasne oczy widzial przygotowujaca sie do szarzy oddzialy wroga."<<endl;
                if(switcher==1) cout<<"Twoj szef szpiegow donosi o planowanym ataku wrogich jednostek."<<endl;
                if(switcher==2) cout<<"Zaprzyjaznieni najemni zolnierze donosza, ze dostali oferte udzialu w dzisiejszej szarzy wroga"<<endl;
                if(switcher==3) cout<<"Slychac dzwiek kawaleryjskiego rogu, a z obozu wroga dochodzi tetent kopyt to moze oznaczac tylko jedno"<<endl;
                if(switcher==4) cout<<"Z pogranicznego posterunku przybywa poslaniec dajacy znac o szarzy kawalerii wroga"<<endl;
        }
        if( arg1==2 ){
                if(switcher==0) cout<<"Dzien byl spokojny, nic wielkiego sie nie wydarzylo"<<endl;
                if(switcher==1) cout<<"Poslancy zostali na posterunkach"<<endl;
                if(switcher==2) cout<<"Donsieno nam o ataku, jednak zrodlo informacji moze byc mylne"<<endl;
                if(switcher==3) cout<<"W obozowej gospodzie roznosza sie plotki o ataku"<<endl;
                if(switcher==4) cout<<"Z pogranicznego posterunku przybywa nieznany poslaniec dajacy znac o szarzy kawalerii wroga"<<endl;
        }
        if( arg1==0 ){
                if(switcher==0) cout<<"Szef szpiegow donosi, ze ataku  z pewnoscia nie bedzie"<<endl;
                if(switcher==1) cout<<"Od wiernego sojusznika dostalismy informacje ze ta jednostka dzis nie zaatakuje"<<endl;
                if(switcher==2) cout<<"Siatka szpiegow donosi, ze ta czesc armii wroga wykonuje inne zadania"<<endl;
                if(switcher==3) cout<<"Za duze srodki kupilismy informacje ze ataku tego oddzialu nie bedzie"<<endl;
                if(switcher==4) cout<<"Jestesmy przekonani, ze te wojska nie rusza na nas"<<endl;
        }
                cout<<"___________________________________________________________________"<<endl;

        if( arg2==1 ){
                if(switch2==0) cout<<"Kapitan mowi, ze na wlasne oczy widzial przygotowujaca sie do szarzy oddzialy wroga."<<endl;
                if(switch2==1) cout<<"Twoj szef szpiegow donosi o planowanym ataku wrogich jednostek."<<endl;
                if(switch2==2) cout<<"Zaprzyjaznieni najemni zolnierze donosza, ze dostali oferte udzialu w dzisiejszej szarzy wroga"<<endl;
                if(switch2==3) cout<<"Slychac dzwiek kawaleryjskiego rogu, a z obozu wroga dochodzi tetent kopyt to moze oznaczac tylko jedno"<<endl;
                if(switch2==4) cout<<"Z pogranicznego posterunku przybywa poslaniec dajacy znac o szarzy kawalerii wroga"<<endl;
        }
        if( arg2==2 ){
                if(switch2==0) cout<<"Dzien byl spokojny, nic wielkiego sie nie wydarzylo"<<endl;
                if(switch2==1) cout<<"Poslancy zostali na posterunkach"<<endl;
                if(switch2==2) cout<<"Donsieno nam o ataku, jednak zrodlo informacji moze byc mylne"<<endl;
                if(switch2==3) cout<<"W obozowej gospodzie roznosza sie plotki o ataku"<<endl;
                if(switch2==4) cout<<"Z pogranicznego posterunku przybywa nieznany poslaniec dajacy znac o szarzy kawalerii wroga"<<endl;
        }
        if( arg2==0 ){
                if(switch2==0) cout<<"Szef szpiegow donosi, ze ataku  z pewnoscia nie bedzie"<<endl;
                if(switch2==1) cout<<"Od wiernego sojusznika dostalismy informacje ze ta jednostka dzis nie zaatakuje"<<endl;
                if(switch2==2) cout<<"Siatka szpiegow donosi, ze ta czesc armii wroga wykonuje inne zadania"<<endl;
                if(switch2==3) cout<<"Za duze srodki kupilismy informacje ze ataku tego oddzialu nie bedzie"<<endl;
                if(switch2==4) cout<<"Jestesmy przekonani, ze te wojska nie rusza na nas"<<endl;
        }
                cout<<"___________________________________________________________________"<<endl;

}

void gameloop(){
        int ours=1000 + lvl * 10;
        int theirs = 1000 + lvl * 20;
        sword=(ours/2);
        cav=(ours/4);
        bow=ours - sword - cav;
        opsword=(theirs/2);
        opcav=(theirs/4);
        opbow=theirs - opcav - opsword;
        showforces();
        long long czas;
        int dzialanie, arg1, arg2, who, wart;
        while( (sword>0 || cav > 0 || bow > 0) && (opsword>0 || opcav>0 || opbow>0 )){
                ClearScreen();
                showforces();
                dzialanie=rand()%3;
                if(dzialanie==0){
                        cout<<"Oto raport, zdania w raporcie(raport dziala jak koniunkcja) sa potwierdzone:"<<endl;
                        cout<<"Raport dotyczy: ";
                }
                if(dzialanie==1){
                        cout<<"Oto kiepski raport, w którym jedno zdanie jest z pewnoscia prawdziwe, drugie zas wymyslone."<<endl;
                        cout<<"Raport dziala na zasadzie alternatywy i dotyczy:"<<endl;
                }
                if(dzialanie==2){
                        cout<<"Oto raport w ktorym z pierwszej informacji uzyskalismy druga."<<endl;
                        cout<<"Raport dziala na zasadzie implikacji i dotyczy:"<<endl;
                }
                who=rand()%3;
                if(who == 0 ) cout<<"piechoty"<<endl;
                if(who == 1 ) cout<<"kawalerii"<<endl;
                if(who == 2 ) cout<<"lucznikow"<<endl;
                arg1=rand()%3;
                arg2=rand()%3;
                if(dzialanie==0) wart=kon(arg1,arg2);
                if(dzialanie==1) wart=alt(arg1,arg2);
                if(dzialanie==2) wart=impl(arg1,arg2);
                makestatement(arg1,arg2);
                cout<<"1 - nalezy sie bronic, 2 - pozostac w gotowosci, 0 - odpoczac"<<endl;
                cout<<"Wybierz decyzje co do ataku: "<<endl;
                czas=time(NULL);
                K=getkey();
                czas=time(NULL)-czas;
                wynik+=czas;
                if(K!=wart && K==1){
                        cout<<"Wybierz glowna jednostke obronna: "<<endl;
                        cout<<"0 - piechota , 1 - kawaleria, 2 - lucznicy"<<endl;
                        K=getkey();
                        if(K==neguj(who)){
                                 makegains(who);
                                 cout<<"Doskonala obrona!"<<endl;
                        }
                        else makeloss(who);
                }
                else if(K==1 && K!=wart){
                        makeloss(0);
                        makeloss(1);
                        makeloss(2);
                        cout<<"Zmasakrowano nas niespodziewanym atakiem"<<endl;
                }
                else if(K==wart){
                        cout<<"Dobra decyzja wodzu, nadciagneli rekruci"<<endl;
                        sword+=50;
                        cav+=50;
                        bow+=50;
                }
                else {
                        cout<<"Nikt nie chce sluzyc nielogicznie myslacemu wladcy."<<endl;
                        cout<<"DEZERCJA!"<<endl;
                        sword-=150;
                        cav-=30;
                        bow-=30;
                }
                usleep(2000000);
        }
        cout<<"Zwyciezyles w wielkim boju myslac jedynie: "<<wynik/1000000<<" sekund!."<<endl;
        cout<<"Gratulacje!!!"<<endl;
}



void menu(){
        cout<<"_________________________________________________"<<endl;
        cout<<"________________ GRA  LOGICZNA   ________________"<<endl;
        cout<<"________ ''Polscy Logicy --- BITWA '' ___________"<<endl;
        cout<<"_________________________________________________"<<endl;
        cout<<"_Celem gry jest uzyskanie jak najlepszego wyniku_"<<endl;
        cout<<"_ktory zalezy od poprawnosci odpowiedzi i czasu _"<<endl;
        cout<<"_zastanowienia nad poszczegolnymi odpowiedziami _"<<endl;
        cout<<"_gracz musi sie wykazac znajomoscia podstawowych_"<<endl;
        cout<<"_zasad logiki trojwartosciowej. Gracz wciela sie_"<<endl;
        cout<<"_w role dowodcy ktory musi podejmowac decyzje na_"<<endl;
        cout<<"_froncie, bazujac na informacjach od zwiadowcow _"<<endl;
        cout<<"_i poslancoworaz tych wynikajacych z obserwacji _"<<endl;
        cout<<"_Jak to bywa podczas walki informacje te nie    _"<<endl;
        cout<<"_zawsze sa zgodne z prawda, jednak nie wymagamy _"<<endl;
        cout<<"_od gracza oceny wiarygodnosci, ta jest juz     _"<<endl;
        cout<<"_dostarczana przez gre, jednak musi wykazac sie _"<<endl;
        cout<<"_________________________________________________"<<endl;
        cout<<"________________  ZASADY  _______________________"<<endl;
        cout<<"_->  Konnica bije w boju lucznikow ale przegrywa_"<<endl;
        cout<<"_    z piechota__________________________________"<<endl;
        cout<<"_->  Piechota pokonuje kawalerie ale przegrywa z_"<<endl;
        cout<<"_    lucznikami__________________________________"<<endl;
        cout<<"_->  Gracz nie uzyskujac potrzebnych informacji _"<<endl;
        cout<<"_    powinien sie bronic unikajac walki         -"<<endl;
        cout<<"_->  Atak bez informacji jest kosztowny i nieopl_"<<endl;
        cout<<"_    acalny, zas o informacji decyduje wynik    _"<<endl;
        cout<<"_    ukrytego za zapisem slownym zdania         _"<<endl;
        cout<<"_    logicznego                                 _"<<endl;
        cout<<"_ -> wyniki na minusie to najemnicy, ktorych    _"<<endl;
        cout<<"_    musimy wynajc by dalej walczyc             _"<<endl;
        cout<<"_________________________________________________"<<endl;
        cout<<"__________________ MENU _________________________"<<endl;
        cout<<"_________________________________________________"<<endl;
        cout<<"___________ Nowa Gra ( Wcisnij 1 )_______________"<<endl;
        cout<<"___________ Wyjscie  ( Wcisnij 2 )_______________"<<endl;
        cout<<"___________ Obniz poziom ( Wcisnij 3 )___________"<<endl;
        cout<<"___________ Zwieksz poziom ( Wcisnij 0 )_________"<<endl;
        cout<<"_________________________________________________"<<endl;
        cout<<"___ Obecny poziom trudnosci ( NIESKONCZONY ): "<<lvl<<endl;
        cout<<"_________________________________________________"<<endl;
        K=getkey();
        if(K==0){
                lvl++;
                ClearScreen();
                menu();
        }
        else if(K==1){
                gameloop();
                ClearScreen();
        }
        else if(K==2){
                 exit(1);
                 ClearScreen();
        }
        else if(K==3){
                lvl--;
                ClearScreen();
                menu();
        }
        else menu();
}

int main(int argc, char **arg)
{
    srand( time(NULL) );
    if(argc<9){
        cout<<"Program started with not enough arguments. Basic Values were loaded."<<endl;
        cout<<"Correct way to start a program: "<<endl;
        cout<<"run_my_game --not not.txt --impl impl.txt --or or.txt --and and.txt"<<endl;
    }
    else if(argc==9){
        for(int i=1; i<argc; i+=2){
            if(static_cast<string>(arg[i])=="--not") converttotab(arg[i+1], TabNot, 2);
            if(static_cast<string>(arg[i])=="--or") converttotab(arg[i+1], TabOr, 9);
            if(static_cast<string>(arg[i])=="--and") converttotab(arg[i+1], TabAnd, 9);
            if(static_cast<string>(arg[i])=="--impl") converttotab(arg[i+1], TabImpl, 9);
        }
    }
    else{
        cout<<"Program was started with too many arguments. Basic values were loaded."<<endl;
    }
    usleep(1000000);
    ClearScreen();
    lvl=0;
    menu();
}

                                                                                         