#include <iostream>
#include "wilcze_jagody.h"
using namespace std;
#define ZASWIATY -1

wilcze_jagody::wilcze_jagody(swiat &swiat, int wsp_x, int wsp_y) : roslina(swiat, wsp_x, wsp_y)
{
	this->ustaw_znak('j');
	this->ustaw_sile(99);
	this->ustaw_inicjatywe(0);
	this->ustaw_kolizje_specjalna(true);
	this->ref_swiat.powiekszenie_swiata();
	//this->ref_swiat.organizmy[this->ref_swiat.zwroc_liczbe_organizmow() - 1] = this;
	this->ref_swiat.organizmy[this->ref_swiat.zwroc_odpowiedni_indeks(this->zwroc_inicjatywe())] = this;
}

void wilcze_jagody::kolizja()
{
	int liczba_organizmow, x_wilczej_jagody, y_wilczej_jagody, x_kolidujacego, y_kolidujacego;
	liczba_organizmow = ref_swiat.zwroc_liczbe_organizmow();
	x_wilczej_jagody = this->zwroc_polozenie_x();
	y_wilczej_jagody = this->zwroc_polozenie_y();
	for (int i = 0; i < liczba_organizmow; i++)
	{
		x_kolidujacego = ref_swiat.organizmy[i]->zwroc_polozenie_x();
		y_kolidujacego = ref_swiat.organizmy[i]->zwroc_polozenie_y();
		if (x_wilczej_jagody == x_kolidujacego && y_wilczej_jagody == y_kolidujacego && this != this->ref_swiat.organizmy[i])
		{
			this->ref_swiat.organizmy[i]->ustaw_czy_zyje(false);
			this->ref_swiat.organizmy[i]->ustaw_polozenie_x(ZASWIATY);
			this->ref_swiat.organizmy[i]->ustaw_polozenie_y(ZASWIATY);
			this->ustaw_czy_zyje(false); //Wilcza jagoda tez ginie
			this->ustaw_polozenie_x(ZASWIATY);
			this->ustaw_polozenie_y(ZASWIATY);
			gotoxy(x_wilczej_jagody+1, y_wilczej_jagody+1);
			cout << (char)PUSTY_PIKSEL;
			break;
		}
	}
}