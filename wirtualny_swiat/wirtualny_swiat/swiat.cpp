#include <iostream>
#include "swiat.h"
using namespace std;

//---Zwierzeta---//
#include "zwierze.h"
#include "czlowiek.h"
#include "wilk.h"
#include "owca.h"
#include "lis.h"
#include "zolw.h"
#include "antylopa.h"
//----Rosliny----//
#include "roslina.h"
#include "trawa.h"
#include "mlecz.h"
#include "guarana.h"
#include "wilcze_jagody.h"
//----------------//

swiat::swiat()
{
	this->liczba_organizmow = 0;
	organizmy = new organizm*[this->liczba_organizmow];
}

void swiat::wykonajTure()
{
	this->zwieksz_wiek();
	int liczba_petli = this->liczba_organizmow;
	for (int i = 0; i < liczba_petli; i++)
	{
		if(this->organizmy[i]->sprawdz_czy_zyje()) this->organizmy[i]->akcja();
	}
	this->zredukuj_tablice_organizmow();
}

void swiat::rysujSwiat()
{
	for (int i = 1; i < ROZMIAR_PLANSZY_POZIOM + 2; i++)
	{
		//gotoxy(i, 1);
		//cout << (char)PELNY_PIKSEL;
		gotoxy(i, ROZMIAR_PLANSZY_PION + 1);
		cout << (char)PELNY_PIKSEL;
	}
	for (int j = 1; j < ROZMIAR_PLANSZY_PION + 1; j++)
	{
		//gotoxy(1, j);
		//cout << (char)PELNY_PIKSEL;
		gotoxy(ROZMIAR_PLANSZY_POZIOM + 1, j);
		cout << (char)PELNY_PIKSEL;
	}
	int x, y;
	for (int k = 0; k < liczba_organizmow; k++)
	{
		x = this->organizmy[k]->zwroc_polozenie_x();
		y = this->organizmy[k]->zwroc_polozenie_y();
		gotoxy(x + 1, y + 1);
		this->organizmy[k]->rysowanie();
	}
}

int swiat::zwroc_liczbe_organizmow()
{
	return this->liczba_organizmow;
}

void swiat::ustaw_liczbe_organizmow(int wartosc)
{
	this->liczba_organizmow = wartosc;
}

void swiat::powiekszenie_swiata()
{
	organizm** organizmy_nowa = new organizm*[this->liczba_organizmow + 1];
	for (int i = 0; i < this->liczba_organizmow; i++)
	{
		organizmy_nowa[i] = this->organizmy[i];
	}
	this->liczba_organizmow += 1;
	delete[] this->organizmy;
	this->organizmy = organizmy_nowa;
}

void swiat::dodaj_potomka(const char* klasa, swiat &swiat, int x_potomka, int y_potomka)
{
	if (strcmp(klasa, "class wilk")==0)
	{
		/*this->organizmy[this->zwroc_odpowiedni_indeks(5)] =*/wilk* potomek = new wilk(swiat,x_potomka,y_potomka);
		return;
	}
	if (strcmp(klasa, "class owca") == 0)
	{
		/*this->organizmy[this->zwroc_odpowiedni_indeks(4)] =*/owca* potomek = new owca(swiat, x_potomka, y_potomka);
		return;
	}
	if (strcmp(klasa, "class lis") == 0)
	{
		/*this->organizmy[this->zwroc_odpowiedni_indeks(7)] =*/lis* potomek = new lis(swiat, x_potomka, y_potomka);
		return;
	}
	if (strcmp(klasa, "class zolw") == 0)
	{
		/*this->organizmy[this->zwroc_odpowiedni_indeks(1)] =*/zolw* potomek = new zolw(swiat, x_potomka, y_potomka);
		return;
	}
	if (strcmp(klasa, "class antylopa") == 0)
	{
		/*this->organizmy[this->zwroc_odpowiedni_indeks(4)] =*/antylopa* potomek = new antylopa(swiat, x_potomka, y_potomka);
		return;
	}
	if (strcmp(klasa, "class trawa") == 0)
	{
		/*this->organizmy[this->zwroc_odpowiedni_indeks(0)] =*/trawa* potomek = new trawa(swiat, x_potomka, y_potomka);
		return;
	}
	if (strcmp(klasa, "class mlecz") == 0)
	{
		/*this->organizmy[this->zwroc_odpowiedni_indeks(0)] =*/mlecz* potomek = new mlecz(swiat, x_potomka, y_potomka);
		return;
	}
	if (strcmp(klasa, "class guarana") == 0)
	{
		/*this->organizmy[this->zwroc_odpowiedni_indeks(0)] =*/guarana* potomek = new guarana(swiat, x_potomka, y_potomka);
		return;
	}
	if (strcmp(klasa, "class wilcze_jagody") == 0)
	{
		/*this->organizmy[this->zwroc_odpowiedni_indeks(0)] =*/wilcze_jagody* potomek = new wilcze_jagody(swiat, x_potomka, y_potomka);
		return;
	}
}

int swiat::zwroc_odpowiedni_indeks(int inicjatywa_nowego)
{
	int i=0, liczba_wszystkich_organizmow = this->zwroc_liczbe_organizmow();
	while (i<liczba_wszystkich_organizmow-1 && this->organizmy[i]->zwroc_inicjatywe() >= inicjatywa_nowego) i++;
	organizm* mem1;
	organizm* mem2 = this->organizmy[i];
	int l = i;
	while (l < liczba_wszystkich_organizmow-1)
	{
		mem1 = this->organizmy[l + 1];
		this->organizmy[l + 1] = mem2;
		mem2 = mem1;
		l++;
	}
	return i;
}

void swiat::zredukuj_tablice_organizmow()
{
	int liczba_zywych = 0;
	int liczba_wszystkich_organizmow = this->zwroc_liczbe_organizmow();
	for (int i = 0; i < liczba_wszystkich_organizmow; i++)
	{
		if (this->organizmy[i]->sprawdz_czy_zyje()) liczba_zywych++;
	}
	organizm** nowa_tablica_organizmow = new organizm*[liczba_zywych];
	for (int p = 0; p < liczba_zywych; p++)
	{
		nowa_tablica_organizmow[p] = NULL;
	}
	int j = 0;
	for (int k = 0; k < liczba_wszystkich_organizmow; k++)
	{
		if (this->organizmy[k]->sprawdz_czy_zyje())
		{
			nowa_tablica_organizmow[j] = this->organizmy[k];
			j++;
		}
	}
	delete[] this->organizmy;
	this->organizmy = nowa_tablica_organizmow;
	this->ustaw_liczbe_organizmow(liczba_zywych);
}

void swiat::zwieksz_wiek()
{
	int aktualny_wiek;
	for (int i = 0; i < this->liczba_organizmow; i++)
	{
		aktualny_wiek=this->organizmy[i]->zwroc_wiek();
		this->organizmy[i]->ustaw_wiek(aktualny_wiek + 1);
	}
}