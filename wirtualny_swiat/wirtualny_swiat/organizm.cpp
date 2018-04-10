#include <iostream>
#include "organizm.h"
using namespace std;
#define ZASWIATY -1

organizm::organizm(swiat &swiat, int wsp_x, int wsp_y) : ref_swiat(swiat)
{
	this->czy_zyje = true;
	this->wiek = 1;
	this->polozenie_x = wsp_x;
	this->polozenie_y = wsp_y;
}

int organizm::zwroc_inicjatywe()
{
	return this->inicjatywa;
}

void organizm::ustaw_inicjatywe(int wartosc)
{
	this->inicjatywa = wartosc;
}

int organizm::zwroc_sile()
{
	return this->sila;
}

void organizm::ustaw_sile(int wartosc)
{
	this->sila = wartosc;
}

char organizm::zwroc_znak()
{
	return this->znak;
}

void organizm::ustaw_znak(char wartosc)
{
	this->znak = wartosc;
}

int organizm::zwroc_wiek()
{
	return this->wiek;
}

void organizm::ustaw_wiek(int wartosc)
{
	this->wiek = wartosc;
}

int organizm::zwroc_polozenie_x()
{
	return this->polozenie_x;
}

void organizm::ustaw_polozenie_x(int wartosc)
{
	this->polozenie_x = wartosc;
}

int organizm::zwroc_polozenie_y()
{
	return this->polozenie_y;
}

void organizm::ustaw_polozenie_y(int wartosc)
{
	this->polozenie_y = wartosc;
}

void organizm::ustaw_czy_zyje(bool wartosc)
{
	this->czy_zyje = wartosc;
}

bool organizm::sprawdz_czy_zyje()
{
	return this->czy_zyje;
}

void organizm::ustaw_kolizje_specjalna(bool wartosc)
{
	this->kolizja_specjalna = wartosc;
}

bool organizm::sprawdz_kolizja_specjalna()
{
	return this->kolizja_specjalna;
}

bool organizm::czy_zajete(int wsp_x, int wsp_y)
{
	int wsp_organizmy_x, wsp_organizmy_y, liczba_organizmow = this->ref_swiat.zwroc_liczbe_organizmow();
	for (int i = 0; i < liczba_organizmow; i++)
	{
		wsp_organizmy_x = this->ref_swiat.organizmy[i]->zwroc_polozenie_x();
		wsp_organizmy_y = this->ref_swiat.organizmy[i]->zwroc_polozenie_y();
		if (wsp_x == wsp_organizmy_x && wsp_y == wsp_organizmy_y) return true;
	}
	return false;
}

void organizm::rozmnazanie(swiat &swiat, int x_rodzicow, int y_rodzicow)
{
	int opcje_rozmnazania[4] = { 1, 1, 1, 1 };
	this->znajdz_miejsce_dla_potomnego(opcje_rozmnazania, x_rodzicow, y_rodzicow);
	if (opcje_rozmnazania[0] == 1 || opcje_rozmnazania[1] == 1 || opcje_rozmnazania[2] == 1 || opcje_rozmnazania[3] == 1) //Jesli istnieje choc jedno miejsce dla potomka
	{	
		//this->ref_swiat.powiekszenie_swiata();
		int x_potomka, y_potomka, losowa, spr = 0;
		while (spr == 0)
		{
			losowa = rand()%4;
			if (opcje_rozmnazania[losowa] != 0)
			{
				spr = 1;
				x_potomka = x_rodzicow;
				y_potomka = y_rodzicow;
				switch (losowa)
				{
				case 0: //Ruch w gore 
					if (y_rodzicow > 0){ y_potomka -= 1; }; break;
				case 1: //Ruch w prawo
					if (x_rodzicow < ROZMIAR_PLANSZY_POZIOM - 1){ x_potomka += 1; }; break;
				case 2: //Ruch w dol
					if (y_rodzicow < ROZMIAR_PLANSZY_PION - 1){ y_potomka += 1; }; break;
				case 3: //Ruch w lewo
					if (x_rodzicow > 0){ x_potomka -= 1; }; break;
				}
				this->ref_swiat.dodaj_potomka(typeid(*this).name(), swiat, x_potomka, y_potomka);
				gotoxy(x_potomka + 1, y_potomka + 1);
				this->rysowanie();
			}
		}
	}
}

void organizm::walka(const int indeks_defensora, int x_oponentow, int y_oponentow)
{
	int sila_agresora, sila_defensora;
	sila_agresora = this->zwroc_sile();
	sila_defensora = this->ref_swiat.organizmy[indeks_defensora]->zwroc_sile();
	gotoxy(x_oponentow + 1, y_oponentow + 1);
	if (sila_agresora == sila_defensora)
	{
		this->ref_swiat.organizmy[indeks_defensora]->ustaw_czy_zyje(false);
		this->ref_swiat.organizmy[indeks_defensora]->ustaw_polozenie_x(ZASWIATY);
		this->ref_swiat.organizmy[indeks_defensora]->ustaw_polozenie_y(ZASWIATY);
		this->rysowanie();
	}
	else
	{
		if (sila_agresora > sila_defensora)
		{
			this->ref_swiat.organizmy[indeks_defensora]->ustaw_czy_zyje(false);
			this->ref_swiat.organizmy[indeks_defensora]->ustaw_polozenie_x(ZASWIATY);
			this->ref_swiat.organizmy[indeks_defensora]->ustaw_polozenie_y(ZASWIATY);
			this->rysowanie();
		}
		else
		{
			this->ustaw_czy_zyje(false);
			this->ustaw_polozenie_x(ZASWIATY);
			this->ustaw_polozenie_y(ZASWIATY);
			this->ref_swiat.organizmy[indeks_defensora]->rysowanie();
		}
	}
}

void organizm::znajdz_miejsce_dla_potomnego(int* notatka, int x_zwiadowcy, int y_zwiadowcy)
{
	int liczba_organizmow = this->ref_swiat.zwroc_liczbe_organizmow();
	int sila_zwiadowcy = this->zwroc_sile();
	//GORA
	if (this->czy_zajete(x_zwiadowcy, y_zwiadowcy - 1) || y_zwiadowcy == 0)
	{
		 notatka[0] = 0;
	}
	//PRAWO
	if (this->czy_zajete(x_zwiadowcy + 1, y_zwiadowcy) || x_zwiadowcy == ROZMIAR_PLANSZY_POZIOM - 1)
	{
		notatka[1] = 0;
	}
	//DOL
	if (this->czy_zajete(x_zwiadowcy, y_zwiadowcy + 1) || y_zwiadowcy == ROZMIAR_PLANSZY_PION - 1)
	{
		notatka[2] = 0;
	}
	//LEWO
	if (this->czy_zajete(x_zwiadowcy - 1, y_zwiadowcy) || x_zwiadowcy == 0)
	{
		notatka[3] = 0;
	}
}