// Plik zawiera fukcje wyœwietlaj¹ce stó³ ruletki oraz tor wyœcigowy

#include <iostream>
#include <iomanip>
#include <conio.h>
#include <chrono>
#include <thread>
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
const string yellowBackground = "\033[43m";

void wyswietlTablice() {
    const char separator = ' ';
    const int szerokoscKom = 5;
    setlocale(LC_ALL, "C"); // W celu wyœwietlenia prawid³owo tablicy, ustawiam locale na Classic, na koñcu wracam do pl_PL

    // pierwszy rzad znakow
    cout << znakLewyGornyRog;
    for (int i = 0; i < 13; i++)
        cout << string(5, znakSufit) << znakTabelaGora;
    cout << string(8, znakSufit) << znakPrawyGornyRog << endl;

    // 3 rzedy liczb
    for (int j = 3; j > 0; j--) {
        // Wstawienie zera tylko na œrodku
        if (j == 2)
            cout << znakSciana << greenBackground << "  " << 0 << "  " << reset;
        else
            cout << znakSciana << greenBackground << string(5, ' ') << reset;

        // Wyœwietlenie liczb w pozosta³ych kolumnach
        for (int i = j; i <= 36; i += 3) {
            if (znajdzCzyCzerwone(i))
                cout << znakSciana << redBackground << setw(szerokoscKom) << setfill(separator) << left << i << reset;
            else
                cout << znakSciana << setw(szerokoscKom) << setfill(separator) << left << i;
        }

        cout << znakSciana << setw(7) << "linia:" << 3 - j + 1 << znakSciana << endl;

        // Separator miêdzy wierszami liczbowymi
        if (j == 1) break;
        cout << znakSciana << greenBackground << string(5, ' ') << reset << znakTabelaLewo;
        for (int i = 0; i < 12; i++)
            cout << string(5, znakSufit) << znakTabelaSrodek;
        cout << string(8, znakSufit) << znakTabelaPrawo << endl;
    }
    //Seperator miêdzy obstawieniami poza tabela
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
    //Pierwsza linia znaków
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
    //Nazwy zak³adów og³oszonych
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

bool sprawdzCzyJest(int a,int tab[],int rozmiar) {
    for (int i = 0;i <= rozmiar;i++) {
        if (tab[i] == a)
            return true;
    }
    return false;
}

void wyswietlTabliceZPodswietleniem(int doPodswietlenia[],int rozmiar) {
    const char separator = ' ';
    const int szerokoscKom = 5;
    setlocale(LC_ALL, "C"); // W celu wyœwietlenia prawid³owo tablicy, ustawiam locale na Classic, na koñcu wracam do pl_PL

    // pierwszy rzad znakow
    cout << znakLewyGornyRog;
    for (int i = 0; i < 13; i++)
        cout << string(5, znakSufit) << znakTabelaGora;
    cout << string(8, znakSufit) << znakPrawyGornyRog << endl;

    // 3 rzedy liczb
    for (int j = 3; j > 0; j--) {
        // Wstawienie zera tylko na œrodku
        if (j == 2)
            cout << znakSciana << greenBackground << "  " << 0 << "  " << reset;
        else
            cout << znakSciana << greenBackground << string(5, ' ') << reset;

        // Wyœwietlenie liczb w pozosta³ych kolumnach
        for (int i = j; i <= 36; i += 3) {
            if(sprawdzCzyJest(i,doPodswietlenia,rozmiar))
                cout << znakSciana << yellowBackground << setw(szerokoscKom) << setfill(separator) << left << i << reset;
            else if (znajdzCzyCzerwone(i))
                cout << znakSciana << redBackground << setw(szerokoscKom) << setfill(separator) << left << i << reset;
            else
                cout << znakSciana << setw(szerokoscKom) << setfill(separator) << left << i;
        }

        cout << znakSciana << setw(7) << "linia:" << 3 - j + 1 << znakSciana << endl;

        // Separator miêdzy wierszami liczbowymi
        if (j == 1) break;
        cout << znakSciana << greenBackground << string(5, ' ') << reset << znakTabelaLewo;
        for (int i = 0; i < 12; i++)
            cout << string(5, znakSufit) << znakTabelaSrodek;
        cout << string(8, znakSufit) << znakTabelaPrawo << endl;
    }
    //Seperator miêdzy obstawieniami poza tabela
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

void wyswietlInstrukcje() {
    char wybor;
    system("CLS");
    cout << "W europejskiej ruletce obstawiamy na ró¿ne liczby (zak³ady wewnêtrzne) oraz specjalne pola (zak³ady zewnêtrzne):\n"
        << "czarne/czerwone, niskie/wysokie, parzyste/nieparzyste, tuzin oraz linia. "
        << greenBackground << "Zero" << reset << " jest specyficzn¹ liczb¹,\ngdy¿ gdy zostanie wylosowane to nie mo¿emy wygraæ ¿adnego "
        << "zak³adu zewnêtrznego, dlatego warto zastanowiæ siê nad\nobstawieniem zera za ka¿dym razem.\n\n"
        << "Obstawiaæ mo¿emy tyle pól ile chcemy, jedynym ograniczeniem jest krupier, który mo¿e zakoñczyæ\nobstawianie mówi¹c "
        << "\"Koniec obstawiania\". Po obstawianiu losowana jest liczba oraz przyznawane s¹ nagrody."
        << "\n\nKliknij ESC aby wyjœæ z instrukcji\nKliknij dowolny przycisk aby kontynuowaæ...";
    wybor = _getch();
    system("CLS");
    if (wybor == 27) {
        wyswietlMenu();
        return;
    }
    cout << "Po rozpoczêciu gry zobaczysz stó³ do gry oraz menu dziêki któremu wybierzesz swoje obstawienia:\n\n"
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
        << "a - zaklady og³oszone\n\n"
        <<"Teraz opiszemy pokolei ka¿dy rodzaj zak³adu..."
        << "\n\nKliknij ESC aby wyjœæ z instrukcji\nKliknij dowolny przycisk aby kontynuowaæ...";
    wybor = _getch();
    system("CLS");
    if (wybor == 27) {
        wyswietlMenu();
        return;
    }
    int tab[37];
    cout << "POSTAW NA JEDEN - polega na postawieniu ¿etonu na jedno pole, potencjalna nagroda wtedy wynosi 35*wartoœæ zak³adu.\n";
    tab[0]=5;
    wyswietlTabliceZPodswietleniem(tab, 1);
    cout << "\n\nKliknij ESC aby wyjœæ z instrukcji\nKliknij dowolny przycisk aby kontynuowaæ...";
    wybor = _getch();
    system("CLS");
    if (wybor == 27) {
        wyswietlMenu();
        return;
    }
    cout << "POSTAW NA WIELE - polega na postawieniu ¿etonu miêdzy dwa, trzy, cztery lub szeœæ pól,\n"
        << "potencjalna nagroda wynosi wtedy:\n"
        << "- na dwa: 17*wartoœæ zak³adu\n"
        << "- na trzy: 12*wartoœæ zak³adu\n"
        << "- na cztery: 8*wartoœæ zak³adu\n"
        << "- na szeœæ: 5*wartoœæ zak³adu\n";
    for (int i = 0;i < 6;i++)
        tab[i] = i + 1;
    tab[6] = 12; tab[7] = 11; tab[8] = 14; tab[9] = 15;
    tab[10] = 19; tab[11] = 20; tab[12] = 21;
    tab[13] = 26; tab[14] = 29;
    wyswietlTabliceZPodswietleniem(tab, 15);
    cout << "\n\nKliknij ESC aby wyjœæ z instrukcji\nKliknij dowolny przycisk aby kontynuowaæ...";
    wybor = _getch();
    system("CLS");
    if (wybor == 27) {
        wyswietlMenu();
        return;
    }
    cout << "POSTAW NA 1/3 STO£U - \n"
        << "- na tuzin - stawia na jedno z 3 opcji: 1-12, 13-24, 25-36\n"
        << "- na liniê - stawia na jedno z 3 opcji: {1,4,7,...,34}, {2,5,8,...,35}, {3,6,9,...,36}\n"
        <<"potencjalna wygrana wynosi wtedy: 2*wartoœæ zak³adu.\n";
    wyswietlTablice();
    cout << "\n\nKliknij ESC aby wyjœæ z instrukcji\nKliknij dowolny przycisk aby kontynuowaæ...";
    wybor = _getch();
    system("CLS");
    if (wybor == 27) {
        wyswietlMenu();
        return;
    }
    cout << "POSTAW NA 1/2 STO£U - \n"
        << "- na czerwone/czarne - stawia na czarne lub czerwone\n"
        << "- na niskie/wysokie - stawia na pierwsz¹ (1-18) lub drug¹ (19-36) po³owe sto³u\n"
        << "- na parzyste/nieparzyste - stawia na wszystkie liczby parzyste lub nieparzyste\n"
        << "potencjalna wygrana wynosi wtedy: wartoœæ zak³adu.\n";
    wyswietlTablice();
    cout << "\n\nKliknij ESC aby wyjœæ z instrukcji\nKliknij dowolny przycisk aby kontynuowaæ...";
    wybor = _getch();
    system("CLS");
    if (wybor == 27) {
        wyswietlMenu();
        return;
    }
    cout << "ZAK£ADY OG£OSZONE - s¹ to zak³ady wielu ¿etonów które bazuj¹ siê na u³o¿eniu \n"
        << "liczb na tarczy ko³a do ruletki, rzadko u¿ywane, czêœciej przez zaawansowanych graczy.\n"
        << "Finals - obstawienie na wszystkie liczby które koñcz¹ siê na dan¹ cyfrê\n"
        << "S¹siedzi (Neighbors) - obstawienie 1-5 liczb s¹siaduj¹cych z liczb¹ na kole (z obu stron), wraz z dan¹ liczb¹\n"
        << "Potencjalna nagroda ró¿ni siê dla ka¿dego zak³adu oraz dla wylosowanej liczby z tego zak³adu.\n";
    wyswietlTabliceOgloszona();
    cout << "\n\nKliknij ESC aby wyjœæ z instrukcji\nKliknij dowolny przycisk aby kontynuowaæ...";
    wybor = _getch();
    system("CLS");
    if (wybor == 27) {
        wyswietlMenu();
        return;
    }
    cout << "W celu postawieniu zak³adu nale¿y wybraæ rodzaj zak³adu a nastêpnie postêpowaæ zgodnie z informacjami\n"
        << "na ekranie. Kwoty nale¿y wpisywaæ z kropk¹ zamiast przecinka, np. 1,50 z³ nale¿y wpisaæ jako 1.50\n"
        << "w przeciwnym razie obstawimy tylko 1 z³ (zostanie uciêta wartoœæ po przecinku)\n";
    cout << "\n\nKliknij ESC aby wyjœæ z instrukcji\nKliknij dowolny przycisk aby kontynuowaæ...";
    wybor = _getch();
    system("CLS");
    if (wybor == 27) {
        wyswietlMenu();
        return;
    }
    cout << "DZIENNY BONUS\n"
        << "co 24h gracz otrzymuje 20 z³, aby otrzymaæ bonus wystarczy urochomiæ grê.\n"
        << "Po wykorzystaniu ca³ej puli pieniêdzy kontynuwanie gry bêdzie niemo¿liwe.\n";
    cout << "\n\nKliknij ESC aby wyjœæ z instrukcji\nKliknij dowolny przycisk aby kontynuowaæ...";
    wybor = _getch();
    system("CLS");
    if (wybor == 27) {
        wyswietlMenu();
        return;
    }
    cout << "MINIMALNE ZAK£ADY\n"
        << "dla 1-6 pól - 0,50 z³\n"
        << "dla zak³adów na 1/3 sto³u - 2,50 z³\n"
        << "dla zak³adów na 1/2 sto³u - 5,00 z³\n"
        << "dla zak³adów og³oszonych - 0,50 z³ * iloœæ ustawionych ¿etonów";
    cout << "\n\nKliknij dowolny przycisk aby wyjœæ z instrukcji...";
    wybor = _getch();
    system("CLS");
    wyswietlMenu();
}

void wyswietlMenu() {
    cout << string(25, '-') << endl << "   EUROPEJSKA RULETKA  " << endl << string(25, '-') << endl << endl;
    cout << "> Start - SPACE\n> Instrukcja - H\n> WyjdŸ - ESC\n";
}