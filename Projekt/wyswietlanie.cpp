// Plik zawiera fukcje wy�wietlaj�ce st� ruletki oraz tor wy�cigowy

#include <iostream>
#include <iomanip>
#include "Header.h"

using namespace std;

const char znakLewyGornyRog = 218;
const char znakPrawyGornyRog = 191;
const char znakLewyDolnyRog = 192;
const char znakPrawyDolnyRog = 217;
const char znakSciana = 179;
const char znakSufit = 196;
const char znakTabelaSrodek = 197;
const char znakTabelaGora = 194;
const char znakTabelaDol = 193;
const char znakTabelaLewo = 195;
const char znakTabelaPrawo = 180;

const string redBackground = "\033[41m";
const string greenBackground = "\033[42m";
const string reset = "\033[0m";

void wyswietlTablice() {
    const char separator = ' ';
    const int szerokoscKom = 5;
    setlocale(LC_ALL, "C"); // W celu wy�wietlenia prawid�owo tablicy, ustawiam locale na Classic, na ko�cu wracam do pl_PL

    // pierwszy rzad znakow
    cout << znakLewyGornyRog;
    for (int i = 0; i < 13; i++)
        cout << string(5, znakSufit) << znakTabelaGora;
    cout << string(8, znakSufit) << znakPrawyGornyRog << endl;

    // 3 rzedy liczb
    for (int j = 3; j > 0; j--) {
        // Wstawienie zera tylko na �rodku
        if (j == 2)
            cout << znakSciana << greenBackground << "  " << 0 << "  " << reset;
        else
            cout << znakSciana << greenBackground << string(5, ' ') << reset;

        // Wy�wietlenie liczb w pozosta�ych kolumnach
        for (int i = j; i <= 36; i += 3) {
            if (znajdzCzyCzerwone(i))
                cout << znakSciana << redBackground << setw(szerokoscKom) << setfill(separator) << left << i << reset;
            else
                cout << znakSciana << setw(szerokoscKom) << setfill(separator) << left << i;
        }

        cout << znakSciana << setw(7) << "linia:" << 3 - j + 1 << znakSciana << endl;

        // Separator mi�dzy wierszami liczbowymi
        if (j == 1) break;
        cout << znakSciana << greenBackground << string(5, ' ') << reset << znakTabelaLewo;
        for (int i = 0; i < 12; i++)
            cout << string(5, znakSufit) << znakTabelaSrodek;
        cout << string(8, znakSufit) << znakTabelaPrawo << endl;
    }
    //Seperator mi�dzy obstawieniami poza tabela
    cout << znakLewyDolnyRog << string(5, znakSufit) << znakTabelaSrodek;
    for (int j = 0;j < 3;j++) {
        for (int i = 0;i < 3;i++)
            cout << string(5, znakSufit) << znakTabelaDol;
        cout << string(5, znakSufit) << znakTabelaSrodek;
    }
    cout << string(8, znakSufit) << znakPrawyDolnyRog << endl;
    //tuziny
    cout << string(6, ' ') << znakSciana;
    for (int i = 0;i < 3;i++)
        cout << setw(szerokoscKom * 4 + 2) << setfill(separator) << left << "tuzin: " << i + 1 << znakSciana;
    cout << endl << string(6, ' ');
    cout << znakTabelaLewo;
    for (int i = 0;i < 3;i++) {
        cout << string(szerokoscKom * 2 + 1, znakSufit) << znakTabelaGora << string(szerokoscKom * 2 + 1, znakSufit);
        if (i == 2)
            cout << znakTabelaPrawo << endl;
        else
            cout << znakTabelaSrodek;
    }
    //specjalne
    cout << string(6, ' ')
        << znakSciana << setw(szerokoscKom * 2 + 1) << setfill(separator) << "low 1-18"
        << znakSciana << setw(szerokoscKom * 2 + 1) << setfill(separator) << "even"
        << znakSciana << redBackground << setw(szerokoscKom * 2 + 1) << setfill(separator) << "red" << reset
        << znakSciana << setw(szerokoscKom * 2 + 1) << setfill(separator) << "black"
        << znakSciana << setw(szerokoscKom * 2 + 1) << setfill(separator) << "odd"
        << znakSciana << setw(szerokoscKom * 2 + 1) << setfill(separator) << "high 19-36"
        << znakSciana << endl;
    //koniec tabeli
    cout << string(6, ' ') << znakLewyDolnyRog;
    for (int i = 0;i < 5;i++)
        cout << string(szerokoscKom * 2 + 1, znakSufit) << znakTabelaDol;
    cout << string(szerokoscKom * 2 + 1, znakSufit) << znakPrawyDolnyRog << endl;
    setlocale(LC_ALL, "pl_PL"); //Powrot do pl_PL
}

void wyswietlTabliceOgloszona() {
    const char separator = ' ';
    const int szerokoscKom = 4;
    int liczby[2][19] = { {23,10,5,24,16,33,1,20,14,31,9,22,18,29,7,28,12,35,3},
                          {8,30,11,36,13,27,6,-1,34,-1,17,25,2,21,4,19,15,32,0} };
    int liczbyNaBokach[2] = { -1,26 };
    setlocale(LC_ALL, "C");
    //Pierwsza linia znak�w
    cout << znakLewyGornyRog;
    for (int i = 1;i <= 18;i++)
        cout << string(szerokoscKom, znakSufit) << znakTabelaGora;
    cout << string(szerokoscKom, znakSufit) << znakPrawyGornyRog << endl;
    //Pierwsza linia liczb
    for (int i = 0;i < 19;i++) {
        cout << znakSciana;
        if (znajdzCzyCzerwone(liczby[0][i]))
            cout << redBackground << setw(szerokoscKom)<< liczby[0][i] << reset;
        else if (liczby[0][i] == 0)
            cout << greenBackground << setw(szerokoscKom)<< liczby[0][i] << reset;
        else
            cout << setw(szerokoscKom)<< liczby[0][i];
    }
    cout << znakSciana << endl;
    //Druga linia znakow
    cout << znakSciana;
    cout << string(szerokoscKom, separator) << znakTabelaLewo;
    for (int j = 1;j <= 2;j++) {
        for (int i = 1;i <= 4;i++)
            cout << string(szerokoscKom, znakSufit) << znakTabelaDol;
        cout << string(szerokoscKom, znakSufit) << znakTabelaSrodek;
    }
    for (int i = 1;i <= 6;i++)
        cout << string(szerokoscKom, znakSufit) << znakTabelaDol;
    cout << string(szerokoscKom, znakSufit) << znakTabelaSrodek;
    cout << string(szerokoscKom, znakSufit) << znakTabelaPrawo << endl;
    //Nazwy zak�ad�w og�oszonych
    cout << znakTabelaLewo << string(szerokoscKom, znakSufit);
    cout << znakTabelaPrawo << setw(szerokoscKom * 5 + 5 - 1) << "Tier"
        << znakSciana << setw(szerokoscKom * 5 + 5 - 1) << "Orphelins"
        << znakSciana << setw(szerokoscKom * 7 + 7 - 1) << "Voisins Du Zero";
    cout << znakSciana << setw(szerokoscKom);
    cout << liczbyNaBokach[1];
    cout << znakSciana << endl;
    //Trzecia linia znakow
    cout << znakSciana;
    cout << string(szerokoscKom, separator) << znakTabelaLewo;
    for (int j = 1;j <= 2;j++) {
        for (int i = 1;i <= 4;i++)
            cout << string(szerokoscKom, znakSufit) << znakTabelaGora;
        cout << string(szerokoscKom, znakSufit) << znakTabelaSrodek;
    }
    for (int i = 1;i <= 6;i++)
        cout << string(szerokoscKom, znakSufit) << znakTabelaGora;
    cout << string(szerokoscKom, znakSufit) << znakTabelaSrodek;
    cout << string(szerokoscKom, znakSufit) << znakTabelaPrawo << endl;
    //Druga linia liczb
    for (int i = 0;i < 19;i++) {
        cout << znakSciana;
        if (liczby[1][i] == -1)
            cout << string(szerokoscKom,' ');
        else {
            if (znajdzCzyCzerwone(liczby[1][i]))
                cout << redBackground << setw(szerokoscKom) << liczby[1][i] << reset;
            else if (liczby[1][i] == 0)
                cout << greenBackground << setw(szerokoscKom) << liczby[1][i] << reset;
            else
                cout << setw(szerokoscKom) << liczby[1][i];
        }
    }
    cout << znakSciana << endl;
    //Czwarta linia znakow
    cout << znakLewyDolnyRog;
    for (int i = 1;i <= 18;i++)
        cout << string(szerokoscKom, znakSufit) << znakTabelaDol;
    cout << string(szerokoscKom, znakSufit) << znakPrawyDolnyRog << endl;
    setlocale(LC_ALL, "pl_PL");
}