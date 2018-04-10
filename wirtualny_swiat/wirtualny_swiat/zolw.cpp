#include <iostream>
#include "zolw.h"
using namespace std;
#define ZASWIATY -1

zolw::zolw(swiat &swiat, int wsp_x, int wsp_y) : zwierze(swiat, wsp_x, wsp_y)
{
	this->ustaw_znak('Z');
	this->ustaw_sile(2);
	this->ustaw_inicjatywe(1);
	this->ustaw_kolizje_specjalna(true);
	this->ref_swiat.powiekszenie_swiata();
	//this->ref_swiat.organizmy[this->ref_swiat.zwroc_liczbe_organizmow() - 1] = this;
	this->ref_swiat.organizmy[this->ref_swiat.zwroc_odpowiedni_indeks(this->zwroc_inicjatywe())] = this;
}

void zolw::akcja()
{
	this->ustaw_kolizje_specjalna(false);
	int losowa = rand() % 4;
	if (losowa == 0)
	{
		this->ustaw_kolizje_specjalna(false); //zolw kiedy atakuje traci umiejetnosc specjalna
		zwierze::akcja();
		this->ustaw_kolizje_specjalna(true); //zolw po wykonanym ruchu znow odzyskuje umiejetnosc specjalna
	}
}

void zolw::kolizja()
{
	if (this->sprawdz_kolizja_specjalna())
	{
		int liczba_organizmow, x_zolwia, y_zolwia, x_kolidujacego, y_kolidujacego;
		liczba_organizmow = ref_swiat.zwroc_liczbe_organizmow();
		x_zolwia = this->zwroc_polozenie_x();
		y_zolwia = this->zwroc_polozenie_y();
		for (int i = 0; i < liczba_organizmow; i++)
		{
			x_kolidujacego = this->ref_swiat.organizmy[i]->zwroc_polozenie_x();
			y_kolidujacego = this->ref_swiat.organizmy[i]->zwroc_polozenie_y();
			if (x_zolwia == x_kolidujacego && y_zolwia == y_kolidujacego && this != this->ref_swiat.organizmy[i])
			{
				if (typeid(*this).name() == typeid(*ref_swiat.organizmy[i]).name())
				{
					this->rozmnazanie(this->ref_swiat, x_kolidujacego, y_kolidujacego);
				}
				else
				{
					int sila_zolwia = this->zwroc_sile();
					int sila_kolidujacego = this->ref_swiat.organizmy[i]->zwroc_sile();
					if (sila_kolidujacego <= sila_zolwia) //zolw zabija
					{
						this->ref_swiat.organizmy[i]->ustaw_czy_zyje(false);
						this->ref_swiat.organizmy[i]->ustaw_polozenie_x(ZASWIATY);
						this->ref_swiat.organizmy[i]->ustaw_polozenie_y(ZASWIATY);
						gotoxy(x_zolwia + 1, y_zolwia + 1);
						this->rysowanie();
					}
					else
					{
						if (sila_kolidujacego < 5) //zolw odgania
						{
							this->ref_swiat.organizmy[i]->ustaw_polozenie_x(this->zwroc_pop_polozenie_x());
							this->ref_swiat.organizmy[i]->ustaw_polozenie_y(this->zwroc_pop_polozenie_y());
						}
						else //zolw ginie
						{
							this->ustaw_czy_zyje(false);
							this->ustaw_polozenie_x(ZASWIATY);
							this->ustaw_polozenie_y(ZASWIATY);
							gotoxy(x_kolidujacego + 1, y_kolidujacego + 1);
							this->ref_swiat.organizmy[i]->rysowanie();
						}
					}
				}
			}
		}
	}
	else
	{
		zwierze::kolizja();
	}
}