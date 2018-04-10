#include <iostream>
#include "guarana.h"
using namespace std;
#define ZASWIATY -1

guarana::guarana(swiat &swiat, int wsp_x, int wsp_y) : roslina(swiat, wsp_x, wsp_y)
{
	this->ustaw_znak('g');
	this->ustaw_sile(0);
	this->ustaw_inicjatywe(0);
	this->ustaw_kolizje_specjalna(true);
	this->ref_swiat.powiekszenie_swiata();
	//this->ref_swiat.organizmy[this->ref_swiat.zwroc_liczbe_organizmow() - 1] = this;
	this->ref_swiat.organizmy[this->ref_swiat.zwroc_odpowiedni_indeks(this->zwroc_inicjatywe())] = this;
}

void guarana::kolizja()
{
	int liczba_organizmow, x_guarany, y_guarany, x_kolidujacego, y_kolidujacego;
	liczba_organizmow = ref_swiat.zwroc_liczbe_organizmow();
	x_guarany = this->zwroc_polozenie_x();
	y_guarany = this->zwroc_polozenie_y();
	for (int i = 0; i < liczba_organizmow; i++)
	{
		x_kolidujacego = ref_swiat.organizmy[i]->zwroc_polozenie_x();
		y_kolidujacego = ref_swiat.organizmy[i]->zwroc_polozenie_y();
		if (x_guarany == x_kolidujacego && y_guarany == y_kolidujacego && this != this->ref_swiat.organizmy[i])
		{
			int sila_kolidujacego = this->ref_swiat.organizmy[i]->zwroc_sile();
			this->ref_swiat.organizmy[i]->ustaw_sile(sila_kolidujacego + 3);
			this->ustaw_czy_zyje(false);
			this->ustaw_polozenie_x(ZASWIATY);
			this->ustaw_polozenie_y(ZASWIATY);
			gotoxy(x_kolidujacego+1, y_kolidujacego+1);
			this->ref_swiat.organizmy[i]->rysowanie();
		}
	}
}