#pragma once

extern double kasaGracza;
extern double tabelaWygranych[37];

//zaklady.cpp
void postawNaJeden();
void postawNaWiele();
void postawNaZero(int, int, double);
void postawNaParzyste(bool);
void postawNaCzerwone(bool);
void postawNaWysokie(bool);
void postawNaTuzin();
void postawNaLinie();
void zakladyOgloszone();
void wyswietlZaklady();

//projekt.cpp
void wyswietlTablice();
bool znajdzCzyCzerwone(int);
int zakrecKolem();
double wartoscZetonu(int, double);
double wartoscZakladu(double);
bool znajdzCzyCzerwone(int);

//wczytajBazeDanych.cpp
double wczytajKaseGracza();
bool czyGraczJuzGral();
bool zapiszGre(double,bool);

//wyswietlanie.cpp
void wyswietlTablice();
void wyswietlTabliceOgloszona();
