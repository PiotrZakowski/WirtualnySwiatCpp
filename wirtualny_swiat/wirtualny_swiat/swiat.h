#include <iostream>
#include "conio2.h"

using namespace std;
#define ROZMIAR_PLANSZY_POZIOM 20
#define ROZMIAR_PLANSZY_PION 20
#define PELNY_PIKSEL 219 // W kodzie ASCII pelny kwadrat ma nr 219
#define LICZBA_ORGANIZMOW 2

#ifndef SWIAT_H
#define SWIAT_H

#include "organizm.h"
class organizm;

class swiat
{
public:
	organizm** organizmy;

	swiat();
	void powiekszenie_swiata();
	void wykonajTure();
	void rysujSwiat();
	int zwroc_liczbe_organizmow();
	void ustaw_liczbe_organizmow(int wartosc);
	void dodaj_potomka(const char* klasa, swiat &swiat, int x_potomka, int y_potomka);
	int zwroc_odpowiedni_indeks(int inicjatywa_nowego);

private:
	int liczba_organizmow;
	char plansza[ROZMIAR_PLANSZY_POZIOM][ROZMIAR_PLANSZY_PION];
	
	void zredukuj_tablice_organizmow();
	void zwieksz_wiek();
};

#endif