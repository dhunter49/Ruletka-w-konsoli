// G³ówny plik, znajduje siê tutaj parê koniecznych funkcji

#include <chrono>
#include <thread>
#include <istream>
#include <locale>
#include <iostream>
#include <iomanip>
#include <limits>
#include <conio.h>
#include "Header.h"

// https://i.roulette77.pl/zasady-gry
// https://roulettedoc.com/pl/podstawowe-zasady

using namespace std;

// Tablica czerwonych liczb
const int red[18] = { 1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36 };

// Definiowanie kolorów ANSI
const string redBackground = "\033[41m";
const string greenBackground = "\033[42m";
const string reset = "\033[0m";

// Wartoœci gry
double kasaGracza = 0;
double tabelaWygranych[37] = {};

// Deklaracja funkcji
bool znajdzCzyCzerwone(int liczba); // Sprawdza czy liczba jest czerwona
int zakrecKolem(); // Losuje liczbe z przedzia³u <0;36>
double wartoscZetonu(int iloscZetonow, double minimalnyZaklad); // Prosi o wprowadzenie wartoœci jednego ¿
double wartoscZakladu(double minimalnyZaklad);
void oglosWygrana(int wylosowanaLiczba);
void zresetujTabeleWygranych();

int main() {
    srand(time(0));
    setlocale(LC_ALL, "PL_pl");
    if (czyGraczJuzGral()) { //DODAÆ MENU GRACZA I INSTRUKCJÊ
        cout << "Witaj ponownie!\n";
        kasaGracza = wczytajKaseGracza();
        if (kasaGracza < 0.5) { // Sprawdzamy czy gracz ma wiêcej ni¿ minimalny zak³ad (0.5)
            cout << "Niestety masz za ma³o pieniêdzy aby zagraæ!\nPoczekaj na dzienny bonus!\n\nKliknij dowolny przycisk aby zakoñczyæ dzia³anie gry...";
            _getch();
            return 0;
        }
        cout << "Twój stan konta : " << kasaGracza;
    }
    else {
        cout << "Witaj nowy graczu!\nNa start otrzymujesz 500 z³.";
        kasaGracza = 500;
        if (!(zapiszGre(kasaGracza, true))) {
            cout << "B³¹d w zapisie, gra nie zostanie zapisana!";
        }
    }
    char wyborZMenu;
    cout << "\n\n> Start - SPACE\n> Instrukcja - H\n> WyjdŸ - ESC\n";
    while (true) {
        wyborZMenu = _getch();
        if(wyborZMenu==27)
            return 0;
        else if(wyborZMenu==32)
            break;
        else if(wyborZMenu== 'h')
            wyswietlInstrukcje();
    }
    int wylosowanaLiczba;
    auto czasStartuObstawiania = chrono::steady_clock::now();
    const int duration = 60;
    while (true) {
        zresetujTabeleWygranych();
        czasStartuObstawiania = chrono::steady_clock::now(); // Zapisz czas rozpoczêcia
        while (chrono::steady_clock::now() - czasStartuObstawiania < chrono::seconds(duration)) {
            if (kasaGracza < 0.5) {
                cout << "Masz za ma³o pieniêdzy aby obstawiæ wiêcej!\n";
                break;
            }
            system("CLS");
            wyswietlTablice();
            cout << "Obecny stan konta: " << kasaGracza << endl
                << "Wybierz: \n"
                << "x - koniec zakladów\n"
                << "1 - postaw na jeden\n"
                << "2 - postaw na wiele\n"
                << "e - postaw na parzyste\n"
                << "o - postaw na nieparzyste\n"
                << "b - postaw na czarne\n"
                << "r - postaw na czerwone\n"
                << "l - postaw na niskie (1-18)\n"
                << "h - postaw na wysokie (19-36)\n"
                << "d - postaw na tuzin\n"
                << "w - postaw na linie\n"
                << "a - zaklady og³oszone\n"
                << "Wpisz litere: ";
            cin >> wyborZMenu;
            cin.ignore(numeric_limits<int>::max(), '\n');
            if (wyborZMenu == 'x') {
                system("CLS");
                break;
            }
            switch (wyborZMenu) {
            case '1':
                postawNaJeden();
                break;
            case '2':
                postawNaWiele();
                break;
            case 'e':
                if(kasaGracza>=5)
                    postawNaParzyste(true);
                else {
                    cout << "Za ma³o pieniêdzy na ten zak³ad! Minimalny zak³ad: 5 z³\nKliknij dowolny przycisk aby kontynuowaæ...";
                    _getch();
                }
                break;
            case 'o':
                if(kasaGracza>=5)
                    postawNaParzyste(false);
                else {
                    cout << "Za ma³o pieniêdzy na ten zak³ad! Minimalny zak³ad: 5 z³\nKliknij dowolny przycisk aby kontynuowaæ...";
                    _getch();
                }
                    break;
            case 'b':
                if (kasaGracza >= 5)
                    postawNaCzerwone(false);
                else {
                    cout << "Za ma³o pieniêdzy na ten zak³ad! Minimalny zak³ad: 5 z³\nKliknij dowolny przycisk aby kontynuowaæ...";
                    _getch();
                }
                break;
            case 'r':
                if (kasaGracza >= 5)
                    postawNaCzerwone(true);
                else {
                    cout << "Za ma³o pieniêdzy na ten zak³ad! Minimalny zak³ad: 5 z³\nKliknij dowolny przycisk aby kontynuowaæ...";
                    _getch();
                }
                break;
            case 'h':
                if (kasaGracza >= 5)
                    postawNaWysokie(true);
                else {
                    cout << "Za ma³o pieniêdzy na ten zak³ad! Minimalny zak³ad: 5 z³\nKliknij dowolny przycisk aby kontynuowaæ...";
                    _getch();
                }
                break;
            case 'l':
                if (kasaGracza >= 5)
                    postawNaWysokie(false);
                else {
                    cout << "Za ma³o pieniêdzy na ten zak³ad! Minimalny zak³ad: 5 z³\nKliknij dowolny przycisk aby kontynuowaæ...";
                    _getch();
                 }
                break;
            case 'd':
                if (kasaGracza >=2.5)
                    postawNaTuzin();
                else {
                    cout << "Za ma³o pieniêdzy na ten zak³ad! Minimalny zak³ad 2.50 z³\nKliknij dowolny przycisk aby kontynuowaæ...";
                    _getch();
                }
                break;
            case 'w':
                if (kasaGracza >=2.5)
                    postawNaLinie();
                else {
                    cout<<"Za ma³o pieniêdzy na ten zak³ad! Minimalny zak³ad 2.50 z³\nKliknij dowolny przycisk aby kontynuowaæ...";
                    _getch();
                }
                break;
            case 'a':
                zakladyOgloszone();
                break;
            case 'z':
                wyswietlZaklady();
                break;
            default:
                cout << "Niepoprawny punkt z menu!\n\nKliknij dowolny przycisk aby kontynuowaæ...";
                _getch();
                break;
            }
            system("CLS");
        }
        cout << "Koniec obstawiania." << endl;
        wylosowanaLiczba = zakrecKolem();
        system("CLS");
        wyswietlTablice();
        cout << "Wylosowana liczba:";
        if (wylosowanaLiczba == 0)
            cout << greenBackground<<" " << wylosowanaLiczba <<" " << reset << endl;
        else if (znajdzCzyCzerwone(wylosowanaLiczba))
            cout << redBackground <<" "<< wylosowanaLiczba <<" "<< reset << endl;
        else
            cout <<" "<< wylosowanaLiczba << endl;
        oglosWygrana(wylosowanaLiczba);
        if (zapiszGre(kasaGracza, false)) {
            cout << "\nGra zosta³a zapisana!\n";
        }
        else {
            cout << "B³¹d! Nie uda³o siê otworzyæ pliku zapisu gry. Gra nie zostanie zapisana!\n";
        }
        cout << "Kliknij dowolny przycisk aby kontynuowaæ...\n";
        _getch();
        system("CLS");
        if (kasaGracza < 0.5) {
            cout << "Niestety masz za ma³o pieniêdzy aby kontynuowaæ grê!\nPoczekaj na dzienny bonus!\n\nKliknij dowolny przycisk aby zakoñczyæ dzia³anie gry...";
            _getch();
            return 0;
        }
        while (true) {
            system("CLS");
            cout << "Wybierz opcje:\n"
                << "k - kontynuuj gre\n"
                << "x - zakoñcz dzia³anie gry\n";
            cin >> wyborZMenu;
            if (wyborZMenu == 'x')
                return 0;
            else if (wyborZMenu == 'k') {
                cin.ignore(numeric_limits<int>::max(), '\n');
                break;
            }
            else {
                cout << "Niepoprawny punkt z menu!";
                cin.clear();
                cin.ignore(numeric_limits<int>::max(), '\n');
                this_thread::sleep_for(chrono::seconds(3));
            }
        }
    }
    return 0;
}

bool znajdzCzyCzerwone(int liczba) {
    for (int i = 0; i < 18;i++) {
        if (red[i] == liczba)
            return true;
    }
    return false;
}

int zakrecKolem() {
    cout << "\nLosowanie liczby";
    for (int i = 0; i < 5;i++) {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(chrono::seconds(1));
    }
    int wylosowana1, wylosowana2, wylosowana3, wylosowana4, wylosowana5;
    wylosowana1 = rand() % 37;
    wylosowana2 = rand() % 37;
    wylosowana3 = rand() % 37;
    wylosowana4 = rand() % 37;
    wylosowana5 = rand() % 37;
    int wylosujWylosowana = rand() % 5 + 1; // Zwiêksza losowoœæ liczby
    switch (wylosujWylosowana) {
    case 1:
        return wylosowana1;
    case 2:
        return wylosowana2;
    case 3:
        return wylosowana3;
    case 4:
        return wylosowana4;
    case 5:
        return wylosowana5;
    }
}

double wartoscZetonu(int iloscZetonow, double minimalnyZaklad) {
    system("CLS");
    wyswietlTabliceOgloszona();
    double kwotaNaZeton;
        while (true) {
            cout << "Obstawiawiasz " << iloscZetonow << (iloscZetonow < 5 ? " ¿etony!\n" : " ¿etonów!\n");
            cout << "Podaj wartoœæ JEDNEGO ¿etonu (obecny stan konta: " << kasaGracza << " PLN): ";
            while (!(cin >> kwotaNaZeton)) {
                cout << "Niepoprawna wartoœæ!\n"
                    << "Podaj wartoœæ JEDNEGO ¿etonu (obecny stan konta: " << kasaGracza << " PLN): ";
                cin.clear();
                cin.ignore(numeric_limits<int>::max(), '\n');
            }
            int tymczasowaDoPrzyblizenia; //Przybli¿ kwotê do 2 miejsc po przecinku, nie ma 0.1 grosza
            kwotaNaZeton = (kwotaNaZeton + 0.005) * 100;
            tymczasowaDoPrzyblizenia = kwotaNaZeton;
            kwotaNaZeton = static_cast<double>(tymczasowaDoPrzyblizenia) / 100;
            if (kwotaNaZeton*static_cast<double>(iloscZetonow) > kasaGracza)
                cout << "Nie masz tyle pieniêdzy!\n";
            else if (kwotaNaZeton < minimalnyZaklad)
                cout << "Minimalny zak³ad na ¿eton to " << minimalnyZaklad << " PLN!\n";
            else
                break;
        }
        cin.ignore(numeric_limits<int>::max(), '\n');
        return kwotaNaZeton;
}

double wartoscZakladu(double minimalnyZaklad) {
    system("CLS");
    wyswietlTablice();
    double kwota;
    while (true) {
        cout << "Podaj wartoœæ zak³adu (obecny stan konta: " << kasaGracza << " PLN): ";
        while (!(cin >> kwota)) { //Sprawdza czy na pewno wartoœæ to double a nie np. tekst.
            cout << "Niepoprawna wartoœæ!\n"
                << "Podaj wartoœæ zak³adu (obecny stan konta: " << kasaGracza << " PLN): ";
            cin.clear();
            cin.ignore(numeric_limits<int>::max(), '\n');
        }
        if (kwota > kasaGracza)
            cout << "Nie masz tyle pieniêdzy!\n";
        else if (kwota < minimalnyZaklad)
            cout << "Minimalny zak³ad to " << minimalnyZaklad << " PLN!\n";
        else
            break;
    }
    cin.ignore(numeric_limits<int>::max(), '\n');
    int tymczasowaDoPrzyblizenia; //Przybli¿ kwotê do 2 miejsc po przecinku, nie ma 0.1 grosza
    kwota = (kwota + 0.005) * 100;
    tymczasowaDoPrzyblizenia = kwota;
    kwota = static_cast<double>(tymczasowaDoPrzyblizenia) / 100;
    return kwota;
}

void oglosWygrana(int wylosowanaLiczba) {
    if (tabelaWygranych[wylosowanaLiczba] == 0)
        cout << "Nic nie wygra³aœ/eœ, powodzenia w dalszych partiach.\n";
    else {
        cout << "Wygrana: " << tabelaWygranych[wylosowanaLiczba]<<" z³\n";
        kasaGracza += tabelaWygranych[wylosowanaLiczba];
    }
    cout << "Obecny stan konta: " << kasaGracza << " z³\n";
}

void zresetujTabeleWygranych() {
    for (int i = 0;i <= 36;i++)
        tabelaWygranych[i] = 0;
}