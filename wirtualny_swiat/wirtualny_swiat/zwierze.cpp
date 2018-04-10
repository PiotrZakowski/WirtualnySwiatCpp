#include <iostream>
#include "zwierze.h"
using namespace std;

zwierze::zwierze(swiat &swiat, int wsp_x, int wsp_y) : organizm(swiat, wsp_x, wsp_y){};

int zwierze::zwroc_pop_polozenie_x()
{
	return this->pop_polozenie_x;
}

void zwierze::ustaw_pop_polozenie_x(int wartosc)
{
	this->pop_polozenie_x = wartosc;
}

int zwierze::zwroc_pop_polozenie_y()
{
	return this->pop_polozenie_y;
}

void zwierze::ustaw_pop_polozenie_y(int wartosc)
{
	this->pop_polozenie_y = wartosc;
}

void zwierze::akcja()
{
	int polozenie_x, polozenie_y;
	polozenie_x = this->zwroc_polozenie_x();
	polozenie_y = this->zwroc_polozenie_y();
	this->ustaw_pop_polozenie_x(polozenie_x);
	this->ustaw_pop_polozenie_y(polozenie_y);
	gotoxy(polozenie_x + 1, polozenie_y + 1);
	cout << (char)PUSTY_PIKSEL;
	int losowa = rand() % 4;  // !!! Zdecydowac czy niedozwolony ruch poza plansze to ruch stracony czy tez zrobic petle...
	switch (losowa)
	{
		case 0: //Ruch w gore 
			if (polozenie_y > 0){ polozenie_y -= 1; this->ustaw_polozenie_y(polozenie_y); }; break;
		case 1: //Ruch w prawo
			if (polozenie_x < ROZMIAR_PLANSZY_POZIOM - 1){ polozenie_x += 1; this->ustaw_polozenie_x(polozenie_x); }; break;
		case 2: //Ruch w dol
			if (polozenie_y < ROZMIAR_PLANSZY_PION - 1){ polozenie_y += 1; this->ustaw_polozenie_y(polozenie_y); }; break;
		case 3: //Ruch w lewo
			if (polozenie_x > 0){ polozenie_x -= 1; this->ustaw_polozenie_x(polozenie_x); }; break;
	}
	gotoxy(polozenie_x+1, polozenie_y+1);
	this->rysowanie();
	this->kolizja();
}

void zwierze::kolizja()
{
	int liczba_organizmow, x_rozpatrywany, y_rozpatrywany, x_kolidujacego, y_kolidujacego;
	liczba_organizmow = ref_swiat.zwroc_liczbe_organizmow();
	x_rozpatrywany = this->zwroc_polozenie_x();
	y_rozpatrywany = this->zwroc_polozenie_y();
	for (int i = 0; i < liczba_organizmow; i++)
	{
		x_kolidujacego = ref_swiat.organizmy[i]->zwroc_polozenie_x();
		y_kolidujacego = ref_swiat.organizmy[i]->zwroc_polozenie_y();
		if (x_rozpatrywany == x_kolidujacego && y_rozpatrywany == y_kolidujacego && this!=this->ref_swiat.organizmy[i])
		{
			if (typeid(*this).name() == typeid(*ref_swiat.organizmy[i]).name())
			{
				this->rozmnazanie(this->ref_swiat, x_kolidujacego, y_kolidujacego);
			}
			else
			{
				if (this->ref_swiat.organizmy[i]->sprawdz_kolizja_specjalna() == true && this->sprawdz_kolizja_specjalna() == false) this->ref_swiat.organizmy[i]->kolizja();
				else this->walka(i, x_kolidujacego, y_kolidujacego);
			}
			break;
		}
	}
}

void zwierze::rysowanie()
{
	char znak = this->zwroc_znak();
	cout << znak;
}

void zwierze::ucieczka(int* opcje_ucieczki, int x_uciekajacego, int y_uciekajacego)
{
	int losowa, ucieczka = 0;
	while (ucieczka == 0) // dopoki nie wybierze wolnego miejsca do ucieczki (zawsze takie istnieje - poprzednia pozycja napastnika)
	{
		losowa = rand() % 4;
		if (opcje_ucieczki[losowa] == 0) continue;
		else
		{
			ucieczka = 1;
			switch (losowa)
			{
			case 0: //Ruch w gore 
				if (polozenie_y > 0){ y_uciekajacego -= 1; this->ustaw_polozenie_y(y_uciekajacego); }; break;
			case 1: //Ruch w prawo
				if (polozenie_x < ROZMIAR_PLANSZY_POZIOM - 1){ x_uciekajacego += 1; this->ustaw_polozenie_x(x_uciekajacego); }; break;
			case 2: //Ruch w dol
				if (polozenie_y < ROZMIAR_PLANSZY_PION - 1){ y_uciekajacego += 1; this->ustaw_polozenie_y(y_uciekajacego); }; break;
			case 3: //Ruch w lewo
				if (polozenie_x > 0){ x_uciekajacego -= 1; this->ustaw_polozenie_x(x_uciekajacego); }; break;
			}
		}
		gotoxy(x_uciekajacego + 1, y_uciekajacego + 1);
		this->rysowanie();
		int x_kolidujacego, y_kolidujacego;
		for (int i = 0; i < this->ref_swiat.zwroc_liczbe_organizmow(); i++)
		{
			x_kolidujacego = ref_swiat.organizmy[i]->zwroc_polozenie_x();
			y_kolidujacego = ref_swiat.organizmy[i]->zwroc_polozenie_y();
			if (x_uciekajacego == x_kolidujacego && y_uciekajacego == y_kolidujacego && this != this->ref_swiat.organizmy[i])
			{
				if (typeid(*this).name() == typeid(*ref_swiat.organizmy[i]).name())
				{
					this->rozmnazanie(this->ref_swiat, x_kolidujacego, y_kolidujacego);
				}
			}
		}
	}
}

void zwierze::zwiad(int* notatka, int x_zwiadowcy, int y_zwiadowcy, int promien)
{
	//w notatce jesli notatka[i] == 0 to nie mozna tam pojsc, jesli ==1 to mozna sie tam udac
	int liczba_organizmow = this->ref_swiat.zwroc_liczbe_organizmow();
	int sila_zwiadowcy = this->zwroc_sile();
	//GORA
	if (this->czy_zajete(x_zwiadowcy, y_zwiadowcy - promien))
	{
		for (int i = 0; i < liczba_organizmow; i++)
		{
			if (this->ref_swiat.organizmy[i]->zwroc_polozenie_x() == x_zwiadowcy && this->ref_swiat.organizmy[i]->zwroc_polozenie_y() == y_zwiadowcy - promien)
			{
				if (this->ref_swiat.organizmy[i]->zwroc_sile() > sila_zwiadowcy) notatka[0] = 0;
				break;
			}
		}
	}
	else
	{
		if (y_zwiadowcy == 0)notatka[0] = 0;
	}
	//PRAWO
	if (this->czy_zajete(x_zwiadowcy + promien, y_zwiadowcy))
	{
		for (int i = 0; i < liczba_organizmow; i++)
		{
			if (this->ref_swiat.organizmy[i]->zwroc_polozenie_x() == x_zwiadowcy + promien && this->ref_swiat.organizmy[i]->zwroc_polozenie_y() == y_zwiadowcy)
			{
				if (this->ref_swiat.organizmy[i]->zwroc_sile() > sila_zwiadowcy) notatka[1] = 0;
				break;
			}
		}
	}
	else
	{
		if (x_zwiadowcy == ROZMIAR_PLANSZY_POZIOM - promien) notatka[1] = 0;
	}
	//DOL
	if (this->czy_zajete(x_zwiadowcy, y_zwiadowcy + promien))
	{
		for (int i = 0; i < liczba_organizmow; i++)
		{
			if (this->ref_swiat.organizmy[i]->zwroc_polozenie_x() == x_zwiadowcy && this->ref_swiat.organizmy[i]->zwroc_polozenie_y() == y_zwiadowcy + promien)
			{
				if (this->ref_swiat.organizmy[i]->zwroc_sile() > sila_zwiadowcy) notatka[2] = 0;
				break;
			}
		}
	}
	else
	{
		if (y_zwiadowcy == ROZMIAR_PLANSZY_PION - promien) notatka[2] = 0;
	}
	//LEWO
	if (this->czy_zajete(x_zwiadowcy - promien, y_zwiadowcy))
	{
		for (int i = 0; i < liczba_organizmow; i++)
		{
			if (this->ref_swiat.organizmy[i]->zwroc_polozenie_x() == x_zwiadowcy - promien && this->ref_swiat.organizmy[i]->zwroc_polozenie_y() == y_zwiadowcy)
			{
				if (this->ref_swiat.organizmy[i]->zwroc_sile() > sila_zwiadowcy) notatka[3] = 0;
				break;
			}
		}
	}
	else
	{
		if (x_zwiadowcy == 0) notatka[3] = 0;
	}
}