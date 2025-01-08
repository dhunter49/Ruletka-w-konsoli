// Plik zawiera funkcje odpowiedzialne za wszystkie rodzaje zak³adów

#include <chrono>
#include <thread>
#include <istream>
#include <locale>
#include <iostream>
#include <iomanip>
#include <limits>
#include <conio.h>
#include "Header.h"

using namespace std;

void postawNaJedenObl(int pole, double kwota) {
    kasaGracza -= kwota;
    tabelaWygranych[pole] += kwota * 36;
}

void postawNaJeden() {
    double kwota = wartoscZakladu(0.5);
    int pole;
    while (true) {
        cout << "Podaj pole zak³adu: ";
        while (!(cin >> pole)) {
            cout << "Niepoprawne pole!\n"
                << "Podaj pole zak³adu: ";
            cin.clear();
            cin.ignore(numeric_limits<int>::max(), '\n');
        }
        if (pole >= 0 && pole <= 36)
            break;
        else
            cout << "Niepoprawne pole!\n";
        cin.ignore(numeric_limits<int>::max(), '\n');
    }
    postawNaJedenObl(pole, kwota);
}

bool postawNaWieleObl(int poleGorne, int poleDolne, double kwota) {
    double iloscPostawionychLiczb = 0;
    if ((poleDolne == poleGorne + 3) || (poleDolne == poleGorne - 1) && (poleGorne % 3 == 2 || poleGorne % 3 == 0)) {
        // Gracz stawia na dwa pola {poleGorne, poleDolne}
        iloscPostawionychLiczb = 2;
        tabelaWygranych[poleGorne] += kwota * 36 / iloscPostawionychLiczb;
        tabelaWygranych[poleDolne] += kwota * 36 / iloscPostawionychLiczb;
        return true;
    }
    else if (poleDolne == poleGorne - 2 && poleGorne % 3 == 0) {
        //Gracz stawia na trzy pola {poleGorne, poleGorne - 1, poleDolne}
        iloscPostawionychLiczb = 3;
        tabelaWygranych[poleGorne] += kwota * 36 / iloscPostawionychLiczb;
        tabelaWygranych[poleGorne - 1] += kwota * 36 / iloscPostawionychLiczb;
        tabelaWygranych[poleDolne] += kwota * 36 / iloscPostawionychLiczb;
        return true;
    }
    else if (poleDolne == poleGorne + 2 && (poleGorne % 3 == 0 || poleGorne % 3 == 2)) {
        //Gracz stawia na cztery pola {poleGorne, poleGorne - 1, poleDolne + 1, poleDolne}
        iloscPostawionychLiczb = 4;
        tabelaWygranych[poleGorne] += kwota * 36 / iloscPostawionychLiczb;
        tabelaWygranych[poleGorne - 1] += kwota * 36 / iloscPostawionychLiczb;
        tabelaWygranych[poleDolne + 1] += kwota * 36 / iloscPostawionychLiczb;
        tabelaWygranych[poleDolne] += kwota * 36 / iloscPostawionychLiczb;
        return true;
    }
    else if (poleDolne == poleGorne + 1 && poleGorne % 3 == 0) {
        //Gracz stawia na szeœæ pól <poleGorne - 2, poleDolne+2>
        iloscPostawionychLiczb = 6;
        for (int i = poleGorne - 2;i <= poleDolne + 2;i++) {
            tabelaWygranych[i] += kwota * 36 / iloscPostawionychLiczb;
        }
        return true;
    }
    else
        return false;
}

void postawNaWiele() {
    double kwota = wartoscZakladu(0.5);
    int poleGorne, poleDolne;
    while (true) {
        system("CLS");
        wyswietlTablice();
        while (true) {
            cout << "Podaj LEWE GÓRNE pole zak³adu: ";
            while (!(cin >> poleGorne)) {
                cout << "Niepoprawne pole!\n"
                    << "Podaj LEWE GÓRNE pole zak³adu: ";
                cin.clear();
                cin.ignore(numeric_limits<int>::max(), '\n');
            }
            if (poleGorne >= 0 && poleGorne <= 36)
                break;
            else
                cout << "Niepoprawne pole!\n";
            cin.ignore(numeric_limits<int>::max(), '\n');
        }
        while (true) {
            cout << "Podaj PRAWE DOLNE pole zak³adu: ";
            while (!(cin >> poleDolne)) {
                cout << "Niepoprawne pole!\n"
                    << "Podaj PRAWE DOLNE pole zak³adu: ";
                cin.clear();
                cin.ignore(numeric_limits<int>::max(), '\n');
            }
            if (poleDolne >= 0 && poleDolne <= 36)
                break;
            else
                cout << "Niepoprawne pole!\n";
            cin.ignore(numeric_limits<int>::max(), '\n');
        }
        if (poleGorne == 0 && (poleDolne == 1 || poleDolne == 2 || poleDolne == 3)) { //Rozprawianie siê z sytuacjami problematycznymi tj. gdzie stawiamy na 0
            postawNaZero(poleGorne, poleDolne, kwota);
            cin.ignore(numeric_limits<int>::max(), '\n');
            break;
        }
        else {
            if(!(postawNaWieleObl(poleGorne,poleDolne,kwota)))
            {
                //Z³a kombinacja liczb
                cout << "Nieprawid³owa kombinacja liczb. Kliknij dowolny przycisk aby ponowiæ obstawianie.";
                _getch();
                continue;
            }
            else
                break;
        }
    }
    kasaGracza -= kwota;
}

void postawNaZeroObl(int postawNa[], double iloscPostawionychLiczb, double kwota) {
    for (int i = 0;i < iloscPostawionychLiczb; i++) {
        tabelaWygranych[postawNa[i]] += kwota * 36 / iloscPostawionychLiczb;
    }
}
void postawNaZero(int poleGorne, int poleDolne, double kwota) {
    double iloscPostawionychLiczb = 0;
    int opcja;
    int postawNa[4];
    switch (poleDolne) {
    case 3:
        //Postawiono na dwa {0,3}
        iloscPostawionychLiczb = 2;
        postawNa[0] = 0;
        postawNa[1] = 3;
        postawNaZeroObl(postawNa, iloscPostawionychLiczb, kwota);
        return;
    case 2:
        //2 opcje postawienia {0,2}, lub {0,3,2}
        system("CLS");
        wyswietlTablice();
        cout << "Wybierz opcje:\n"
            << "2. Stawiam na 2 liczby {0,2}.\n"
            << "3. Stawiam na 3 liczby {0,2,3}.\n";
        while (true) {
            while (!(cin >> opcja)) {
                cout << "Nieprawid³owa pozycja z menu, wpisz ponownie: ";
                cin.clear();
                cin.ignore(numeric_limits<int>::max(), '\n');
            }
            if (opcja == 2) {
                //Postawiono na dwa {0,2}
                iloscPostawionychLiczb = 2;
                postawNa[0] = 0;
                postawNa[1] = 2;
                postawNaZeroObl(postawNa, iloscPostawionychLiczb, kwota);
                return;
            }
            else if (opcja == 3) {
                //Postawiono na trzy {0,3,2}
                iloscPostawionychLiczb = 3;
                postawNa[0] = 0;
                postawNa[1] = 3;
                postawNa[2] = 2;
                postawNaZeroObl(postawNa, iloscPostawionychLiczb, kwota);
                return;
            }
            else {
                //Nieprawid³owa wartoœæ
                cout << "Nieprawid³owa pozycja z menu, wpisz ponownie: ";
            }
            cin.ignore(numeric_limits<int>::max(), '\n');
        }
    case 1:
        //3 opcje postawienia {0,1}, {0,2,1}, {0,3,2,1}
        system("CLS");
        wyswietlTablice();
        cout << "Wybierz opcje:\n"
            << "2. Stawiam na 2 liczby {0,1}.\n"
            << "3. Stawiam na 3 liczby {0,2,1}.\n"
            << "4. Stawiam na 4 liczby {0,3,2,1}.\n";
        while (true) {
            while (!(cin >> opcja)) {
                cout << "Nieprawid³owa pozycja z menu, wpisz ponownie: ";
                cin.clear();
                cin.ignore(numeric_limits<int>::max(), '\n');
            }
            if (opcja == 2) {
                //Postawiono na dwa {0,1}
                iloscPostawionychLiczb = 2;
                postawNa[0] = 0;
                postawNa[1] = 1;
                postawNaZeroObl(postawNa, iloscPostawionychLiczb, kwota);
                return;
            }
            else if (opcja == 3) {
                //Postawiono na trzy {0,2,1}
                iloscPostawionychLiczb = 3;
                postawNa[0] = 0;
                postawNa[1] = 2;
                postawNa[2] = 1;
                postawNaZeroObl(postawNa, iloscPostawionychLiczb, kwota);
                return;
            }
            else if (opcja == 4) {
                //Postawiono na cztery {0,3,2,1}
                iloscPostawionychLiczb = 4;
                postawNa[0] = 0;
                postawNa[1] = 1;
                postawNa[2] = 2;
                postawNa[3] = 3;
                postawNaZeroObl(postawNa, iloscPostawionychLiczb, kwota);
                return;
            }
            else {
                //Nieprawid³owa wartoœæ
                cout << "Nieprawid³owa pozycja z menu, wpisz ponownie: ";
            }
            cin.ignore(numeric_limits<int>::max(), '\n');
        }
    }
}

void postawNaParzyste(bool parzyste) {
    double kwota = wartoscZakladu(5);
    double iloscPostawionychLiczb = 18;
    int resztaZDzielenia;
    if (parzyste)
        resztaZDzielenia = 0;
    else
        resztaZDzielenia = 1;
    for (int i = 1;i <= 36;i++) {
        if (i % 2 == resztaZDzielenia)
            tabelaWygranych[i] += kwota * 36 / iloscPostawionychLiczb;
    }
    kasaGracza -= kwota;
}

void postawNaCzerwone(bool czerwone) {
    double kwota = wartoscZakladu(5);
    double iloscPostawionychLiczb = 18;
    for (int i = 1;i <= 36;i++) {
        if (czerwone) {
            if (znajdzCzyCzerwone(i))
                tabelaWygranych[i] += kwota * 36 / iloscPostawionychLiczb;
        }
        else {
            if (!znajdzCzyCzerwone(i))
                tabelaWygranych[i] += kwota * 36 / iloscPostawionychLiczb;
        }
    }
    kasaGracza -= kwota;
}

void postawNaWysokie(bool wysokie) {
    double kwota = wartoscZakladu(5);
    double iloscPostawionychLiczb = 18;
    int poczatek;
    if (wysokie)
        poczatek = 19;
    else
        poczatek = 1;
    for (int i = poczatek;i < poczatek + 18;i++) {
        tabelaWygranych[i] += kwota * 36 / iloscPostawionychLiczb;
    }
    kasaGracza -= kwota;
}

void postawNaTuzin() {
    double kwota = wartoscZakladu(2.5);
    double iloscPostawionychLiczb = 12;
    int tuzin;
    while (true) {
        cout << "Podaj numer tuzina: ";
        while (!(cin >> tuzin)) {
            cout << "Niepoprawny numer!\n"
                << "Podaj numer tuzina: ";
            cin.clear();
            cin.ignore(numeric_limits<int>::max(), '\n');
        }
        if (tuzin >= 1 && tuzin <= 3)
            break;
        else
            cout << "Niepoprawny numer!\n";
        cin.ignore(numeric_limits<int>::max(), '\n');
    }
    for (int i = 1 + (tuzin - 1) * 12;i <= tuzin * 12;i++) {
        tabelaWygranych[i] += kwota * 36 / iloscPostawionychLiczb;
    }
    kasaGracza -= kwota;
}

void postawNaLinie() {
    double kwota = wartoscZakladu(2.5);
    double iloscPostawionychLiczb = 12;
    int linia;
    while (true) {
        cout << "Podaj numer linii: ";
        while (!(cin >> linia)) {
            cout << "Niepoprawny numer!\n"
                << "Podaj numer linii: ";
            cin.clear();
            cin.ignore(numeric_limits<int>::max(), '\n');
        }
        if (linia >= 1 && linia <= 3)
            break;
        else
            cout << "Niepoprawny numer!\n";
        cin.ignore(numeric_limits<int>::max(), '\n');
    }
    for (int i = 3 - linia + 1;i <= 36;i += 3) {
        tabelaWygranych[i] += kwota * 36 / iloscPostawionychLiczb;
    }
    kasaGracza -= kwota;
}

void postawNaTiers() { // 6 ¿etonów
    double kwota = wartoscZetonu(6,0.5);
    postawNaWieleObl(5, 8, kwota);
    postawNaWieleObl(11, 10, kwota);
    postawNaWieleObl(13, 16, kwota);
    postawNaWieleObl(24, 23, kwota);
    postawNaWieleObl(27, 30, kwota);
    postawNaWieleObl(33, 36, kwota);
    kasaGracza -= kwota * 6;
}

void postawNaOrphelins() { // 5 ¿etonów
    double kwota = wartoscZetonu(5,0.5);
    postawNaJedenObl(1, kwota);
    postawNaWieleObl(3, 9, kwota);
    postawNaWieleObl(14, 17, kwota);
    postawNaWieleObl(17, 20, kwota);
    postawNaWieleObl(31, 34, kwota);
    kasaGracza -= kwota * 5;
}

void postawNaVoisins() { // 7 ¿etonów
    double kwota = wartoscZetonu(7,0.5);
    int postawione[3] = { 0,2,3 };
    postawNaZeroObl(postawione, 3, kwota);
    postawNaWieleObl(4, 7, kwota);
    postawNaWieleObl(12, 15, kwota);
    postawNaWieleObl(18, 21, kwota);
    postawNaWieleObl(19, 22, kwota);
    postawNaWieleObl(26, 28, kwota);
    postawNaWieleObl(32, 35, kwota);
    kasaGracza -= kwota * 7;
}

void postawNaSasiadow() {
    cout << "Podaj liczbê s¹siadów (1-5): ";
    int iloscSasiadow;
    int koloRuletki[37] = { 23,10,5,24,16,33,1,20,14,31,9,22,18,29,7,28,12,35,3,26,0,32,15,19,4,21,2,25,17,34,6,27,13,36,11,30,8 };
    while (true) {
        while (!(cin >> iloscSasiadow)) {
            cout << "Niepoprawny numer!\n"
                << "Podaj liczbê s¹siadów (1-5): ";
            cin.clear();
            cin.ignore(numeric_limits<int>::max(), '\n');
        }
        if (iloscSasiadow >= 1 && iloscSasiadow <= 5)
            break;
        else
            cout << "Niepoprawny numer!\n";
        cin.ignore(numeric_limits<int>::max(), '\n');
    }
    double kwota = wartoscZetonu(iloscSasiadow*2+1,0.5);
    int pole;
    while (true) {
        cout << "Podaj pole œrodkowe: ";
        while (!(cin >> pole)) {
            cout << "Niepoprawne pole!\n"
                << "Podaj pole œrodkowe: ";
            cin.clear();
            cin.ignore(numeric_limits<int>::max(), '\n');
        }
        if (pole >= 0 && pole <= 36)
            break;
        else
            cout << "Niepoprawne pole!\n";
        cin.ignore(numeric_limits<int>::max(), '\n');
    }
    int numerMiejscaWKole;
    for (numerMiejscaWKole = 0; numerMiejscaWKole < 37; numerMiejscaWKole++) { // Znajdujemy ID komrki tablicy koloRuletki w ktorym znajduje sie pole
        if (koloRuletki[numerMiejscaWKole] == pole)
            break;
    }
    int itDoGory = numerMiejscaWKole + 1;
    int itDoDolu = numerMiejscaWKole - 1;
    postawNaJedenObl(koloRuletki[numerMiejscaWKole], kwota);
    for (int i = iloscSasiadow;i > 0;i--) {
        if (itDoDolu < 0)
            itDoDolu = 36;
        if (itDoGory > 36)
            itDoGory = 0;
        postawNaJedenObl(koloRuletki[itDoDolu], kwota);
        postawNaJedenObl(koloRuletki[itDoGory], kwota);
        itDoDolu--;itDoGory++;
    }
}

void postawNaFinals() {
    int finalCyfra;
    while (true) {
        cout << "Podaj ostatni¹ cyfrê obstawianych liczb (0-9): ";
        while (!(cin >> finalCyfra)) {
            cout << "Niepoprawny numer!\n"
                << "Podaj ostatni¹ cyfrê obstawianych liczb (0-9): ";
            cin.clear();
            cin.ignore(numeric_limits<int>::max(), '\n');
        }
        if (finalCyfra >= 0 && finalCyfra <= 9) {
            if (finalCyfra <= 6 && kasaGracza < 2) {
                cout << "Za ma³o pieniêdzy na ten zak³ad! Minimalny zak³ad: 2 z³\nKliknij dowolny przycisk aby kontynuowaæ...";
                _getch();
                return;
            }
            break;
        }
        else
            cout << "Niepoprawny numer!\n";
        cin.ignore(numeric_limits<int>::max(), '\n');
    }
    double iloscPostawionychLiczb{};
    if (finalCyfra <= 6)
        iloscPostawionychLiczb = 4;
    else
        iloscPostawionychLiczb = 3;
    double kwota = wartoscZetonu(iloscPostawionychLiczb, 0.5);
    for (int i = finalCyfra;i <= 36;i += 10) {
        postawNaJedenObl(i, kwota);
    }
}

void zakladyOgloszone() {
    char wyborZMenu;
    while (true) {
        system("CLS");
        wyswietlTabliceOgloszona();
        cout << "Wybierz: \n"
            << "t - Tiers du Cylindre\n"
            << "o - Orphelins\n"
            << "v - Voisins Du Zero\n"
            << "n - S¹siedzi\n"
            << "f - Finals\n"
            << "b - cofnij\n"
            << "Wpisz litere: ";
        cin >> wyborZMenu;
        cin.ignore(numeric_limits<int>::max(), '\n');
        if (wyborZMenu == 't') {
            if(kasaGracza>=3)
                postawNaTiers();
            else {
                cout << "Za ma³o pieniêdzy na ten zak³ad! Minimalny zak³ad: 3 z³\nKliknij dowolny przycisk aby kontynuowaæ...";
                _getch();
            }
            break;
        }
        else if (wyborZMenu == 'o') {
            if(kasaGracza>=2.5)
                postawNaOrphelins();
            else {
                cout << "Za ma³o pieniêdzy na ten zak³ad! Minimalny zak³ad: 2.50 z³\nKliknij dowolny przycisk aby kontynuowaæ...";
                _getch();
            }
            break;
        }
        else if (wyborZMenu == 'v') {
            if(kasaGracza>=3.5)
                postawNaVoisins();
            else {
                cout << "Za ma³o pieniêdzy na ten zak³ad! Minimalny zak³ad: 3.50 z³\nKliknij dowolny przycisk aby kontynuowaæ...";
                _getch();
            }
            break;
        }
        else if (wyborZMenu == 'n') {
            if(kasaGracza>=1.5)
                postawNaSasiadow();
            else {
                cout << "Za ma³o pieniêdzy na ten zak³ad! Minimalny zak³ad: 1.50 z³\nKliknij dowolny przycisk aby kontynuowaæ...";
                _getch();
            }
            break;
        }
        else if (wyborZMenu == 'f') {
            if(kasaGracza>=1.5)
                postawNaFinals();
            else {
                cout << "Za ma³o pieniêdzy na ten zak³ad! Minimalny zak³ad: 1.50 z³\nKliknij dowolny przycisk aby kontynuowaæ...";
                _getch();
            }
            break;
        }
        else if (wyborZMenu == 'b') {
            break;
        }
        else {
            cout << "Niepoprawny punkt z menu!\n";
            this_thread::sleep_for(chrono::seconds(3));
        }
    }
}

void wyswietlZaklady() {
    system("CLS");
    for (int i = 0;i <= 36;i++) {
        cout << i << ": " << tabelaWygranych[i] << endl;
    }
    system("PAUSE");
}