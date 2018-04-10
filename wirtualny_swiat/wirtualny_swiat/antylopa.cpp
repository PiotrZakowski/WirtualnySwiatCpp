#include <iostream>
#include "antylopa.h"
using namespace std;

antylopa::antylopa(swiat &swiat, int wsp_x, int wsp_y) : zwierze(swiat, wsp_x, wsp_y)
{
	this->ustaw_znak('A');
	this->ustaw_sile(4);
	this->ustaw_inicjatywe(4);
	this->ustaw_kolizje_specjalna(true);
	this->ref_swiat.powiekszenie_swiata();
	//this->ref_swiat.organizmy[this->ref_swiat.zwroc_liczbe_organizmow() - 1] = this;
	this->ref_swiat.organizmy[this->ref_swiat.zwroc_odpowiedni_indeks(this->zwroc_inicjatywe())] = this;
}

void antylopa::akcja()
{
	int x_antylopy, y_antylopy;
	x_antylopy = this->zwroc_polozenie_x();
	y_antylopy = this->zwroc_polozenie_y();
	this->ustaw_pop_polozenie_x(x_antylopy);
	this->ustaw_pop_polozenie_y(y_antylopy);
	gotoxy(x_antylopy + 1, y_antylopy + 1);
	cout << (char)PUSTY_PIKSEL;
	int losowa = rand() % 4;  // !!! Zdecydowac czy niedozwolony ruch poza plansze to ruch stracony czy tez zrobic petle...
	switch (losowa)
	{
	case 0: //Ruch w gore 
		if (y_antylopy > 1){ y_antylopy -= 2; this->ustaw_polozenie_y(y_antylopy); }; break;
	case 1: //Ruch w prawo
		if (x_antylopy < ROZMIAR_PLANSZY_POZIOM - 2){ x_antylopy += 2; this->ustaw_polozenie_x(x_antylopy); }; break;
	case 2: //Ruch w dol
		if (y_antylopy < ROZMIAR_PLANSZY_PION - 2){ y_antylopy += 2; this->ustaw_polozenie_y(y_antylopy); }; break;
	case 3: //Ruch w lewo
		if (x_antylopy > 1){ x_antylopy -= 2; this->ustaw_polozenie_x(x_antylopy); }; break;
	}
	gotoxy(x_antylopy + 1, y_antylopy + 1);
	this->rysowanie();
	this->ustaw_kolizje_specjalna(false);
	this->kolizja();
	this->ustaw_kolizje_specjalna(true);
}

void antylopa::kolizja()
{
	int liczba_organizmow, x_antylopy, y_antylopy, x_kolidujacego, y_kolidujacego;
	liczba_organizmow = ref_swiat.zwroc_liczbe_organizmow();
	x_antylopy = this->zwroc_polozenie_x();
	y_antylopy = this->zwroc_polozenie_y();
	for (int i = 0; i < liczba_organizmow; i++)
	{
		x_kolidujacego = ref_swiat.organizmy[i]->zwroc_polozenie_x();
		y_kolidujacego = ref_swiat.organizmy[i]->zwroc_polozenie_y();
		if (x_antylopy == x_kolidujacego && y_antylopy == y_kolidujacego && this != this->ref_swiat.organizmy[i])
		{
			if (typeid(*this).name() == typeid(*ref_swiat.organizmy[i]).name())
			{
				this->rozmnazanie(this->ref_swiat, x_kolidujacego, y_kolidujacego);
			}
			else
			{
				int losowa = rand() % 2;
				int opcje_ruchu[4] = { 1, 1, 1, 1 }; //1 - mozna przejsc, 0 - nie mozna przejsc
				if (losowa == 0)
				{
					this->zwiad(opcje_ruchu, x_antylopy, y_antylopy, 1);
					if (opcje_ruchu[0] == 0 && opcje_ruchu[1] == 0 && opcje_ruchu[2] == 0 && opcje_ruchu[3] == 0) losowa = 1; //Nie ma mozliwosci do ucieczki
				}
				if (losowa == 0)
				{
					this->ucieczka(opcje_ruchu, x_antylopy, y_antylopy);
					gotoxy(x_kolidujacego + 1, y_kolidujacego + 1);
					this->ref_swiat.organizmy[i]->rysowanie();
				}
				else
				{
					this->ustaw_kolizje_specjalna(false);
					zwierze::kolizja();
					this->ustaw_kolizje_specjalna(true);
				}
			}
		}
	}
}

