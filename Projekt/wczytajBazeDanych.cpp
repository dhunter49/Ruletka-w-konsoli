#include <fstream>
#include <iostream>
#include <ctime>
#include "Header.h"

using namespace std;

bool czyGraczJuzGral() {
	ifstream bazaDanych("Ruletka_ZapisGry.txt");
	if (bazaDanych.is_open()) {
		bazaDanych.close();
		return true;
	}
	//ofstream bazaDanychOut("Ruletka_ZapisGry.txt");
	//bazaDanychOut << "";
	//bazaDanychOut.close();
	return false;
}

double wczytajKaseGracza() {
	ifstream bazaDanych("Ruletka_ZapisGry.txt");
	double kasaZPliku;
	bazaDanych >> kasaZPliku;
	//SPRAWDZ DATE
	time_t zapisanyCzas;
	bazaDanych >> zapisanyCzas;
	time_t obecnyCzas = time(nullptr);
	const time_t dwadziesciaCzteryGodziny = 24 * 60 * 60;
	//Sprawdzamy czy data zapisana jest mniejsza od obecnej o jeden dzien - przypisujemy dzienny bonus
	if ((obecnyCzas - zapisanyCzas) >= dwadziesciaCzteryGodziny) {
		kasaZPliku += 20;
		if (zapiszGre(kasaZPliku, true)) {
			cout << "Dzienny bonus!  +20 z³\n";
		}
		else {
			cout << "B³¹d w przydzielaniu dziennego bonusu! Gra nie zostanie zapisana.";
		}
	}
	else {
		time_t pozostalyCzas = dwadziesciaCzteryGodziny - (obecnyCzas - zapisanyCzas);

		// Konwersja pozosta³ego czasu na godziny, minuty, sekundy
		int godziny = pozostalyCzas / 3600;
		int minuty = (pozostalyCzas % 3600) / 60;

		cout << "Do dziennego bonusu zosta³o: "
			<< godziny << " godz. "
			<< minuty << " min.\n";
	}

	bazaDanych.close();
	return kasaZPliku;
}

bool zapiszGre(double kasaDoZapisu,bool czyZapisacDate) {
	ifstream bazaDanychWczyt("Ruletka_ZapisGry.txt");
	double kasaTemp;
	time_t czasZPliku;
	bazaDanychWczyt >> kasaTemp >> czasZPliku;
	bazaDanychWczyt.close();
	fstream bazaDanych;
	bazaDanych.open("Ruletka_ZapisGry.txt", ios::out | ios::trunc);
	if (!(bazaDanych.is_open())) {
		return false;
	}
	bazaDanych << kasaDoZapisu << endl;
	//ZAPISZ DATE
	if (czyZapisacDate) {
		time_t obecnyCzas = time(nullptr);
		bazaDanych << obecnyCzas << endl;
	}
	else
		bazaDanych << czasZPliku << endl;
	if (!(bazaDanych.is_open())) {
		return false;
	}
	bazaDanych.close();
	return true;
}