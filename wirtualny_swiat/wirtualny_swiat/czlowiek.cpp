#include <iostream>
#include "czlowiek.h"
using namespace std;
//wyjasnienie tury_umiejetnosc
//0 -> umiejetnosc gotowa do uzycia
//1,2,3,4,5 -> umiejetnosc w uzyciu
//6,7,8,9,10 -> cooldown
//10+1 => 0 -> znow gotowy do uzycia

czlowiek::czlowiek(swiat &swiat, int wsp_x, int wsp_y) : zwierze(swiat, wsp_x, wsp_y)
{
	this->ustaw_znak('C');
	this->ustaw_sile(5);
	this->ustaw_inicjatywe(4);
	this->ustaw_ilosc_tur(0);
	this->ustaw_kolizje_specjalna(false);
	this->ref_swiat.powiekszenie_swiata();
	//this->ref_swiat.organizmy[this->ref_swiat.zwroc_liczbe_organizmow()-1] = this;
	this->ref_swiat.organizmy[this->ref_swiat.zwroc_odpowiedni_indeks(this->zwroc_inicjatywe())] = this;
}

int czlowiek::zwroc_ilosc_tur()
{
	return this->tury_umiejetnosc;
}

void czlowiek::ustaw_ilosc_tur(int wartosc)
{
	this->tury_umiejetnosc = wartosc;
}

void czlowiek::akcja()
{
	int ilosc_tur_umiejetnosci = this->zwroc_ilosc_tur();
	if (ilosc_tur_umiejetnosci > 0)
	{
		ilosc_tur_umiejetnosci+=1;
		if (ilosc_tur_umiejetnosci == 11)
		{
			this->ustaw_ilosc_tur(0);
			this->ustaw_kolizje_specjalna(false);
			ilosc_tur_umiejetnosci = 0;
		}
		else this->ustaw_ilosc_tur(ilosc_tur_umiejetnosci);
	}
	int polozenie_x=this->zwroc_polozenie_x();
	int polozenie_y=this->zwroc_polozenie_y();
	this->ustaw_pop_polozenie_x(polozenie_x);
	this->ustaw_pop_polozenie_y(polozenie_y);
	//cin.ignore();
	unsigned char klawisz = getch();
	if (klawisz == SPACJA)
	{
		if (ilosc_tur_umiejetnosci == 0)
		{
			this->ustaw_kolizje_specjalna(true);
			this->ustaw_ilosc_tur(1);
		} 
		klawisz = getch();
		klawisz = getch();
	}
	gotoxy(polozenie_x + 1, polozenie_y + 1);
	cout << (char)PUSTY_PIKSEL;
	switch (klawisz) // !!! Zdecydowac czy niedozwolony ruch poza plansze to ruch stracony czy tez zrobic petle...
	{
	case STRZALKA_GORA:
		if (polozenie_y > 0)
		{
			this->ustaw_polozenie_y(polozenie_y - 1);
			polozenie_y -= 1;
		}; break;
	case STRZALKA_DOL:
		if (polozenie_y < ROZMIAR_PLANSZY_PION - 1)
		{
			this->ustaw_polozenie_y(polozenie_y + 1);
			polozenie_y += 1;
		}; break;
	case STRZALKA_LEWO:
		if (polozenie_x > 0)
		{
			this->ustaw_polozenie_x(polozenie_x - 1);
			polozenie_x -= 1;
		}; break;
	case STRZALKA_PRAWO:
		if (polozenie_x < ROZMIAR_PLANSZY_POZIOM - 1)
		{
			this->ustaw_polozenie_x(polozenie_x + 1);
			polozenie_x += 1;
		}; break;
	}
	gotoxy(polozenie_x + 1, polozenie_y + 1);
	this->rysowanie();
	this->kolizja();
}

void czlowiek::kolizja() //specjalna kolizja czlowieka
{
	if (this->sprawdz_kolizja_specjalna()) // umiejetnosc wlaczona -> kolizja specjalna
	{
		int liczba_organizmow, x_czlowieka, y_czlowieka, x_kolidujacego, y_kolidujacego;
		liczba_organizmow = this->ref_swiat.zwroc_liczbe_organizmow();
		x_czlowieka = this->zwroc_polozenie_x();
		y_czlowieka = this->zwroc_polozenie_y();
		for (int i = 0; i < liczba_organizmow; i++)
		{
			x_kolidujacego = this->ref_swiat.organizmy[i]->zwroc_polozenie_x();
			y_kolidujacego = this->ref_swiat.organizmy[i]->zwroc_polozenie_y();
			if (x_czlowieka == x_kolidujacego && y_czlowieka == y_kolidujacego && this != this->ref_swiat.organizmy[i])
			{
				int sila_czlowieka = this->zwroc_sile();
				int sila_kolidujacego = this->ref_swiat.organizmy[i]->zwroc_sile();
				if(sila_kolidujacego > sila_czlowieka) // organizm silniejszy -> ucieczka czlowieka
				{
					int spr = 0;
					gotoxy(x_czlowieka + 1, y_czlowieka + 1);
					this->ref_swiat.organizmy[i]->rysowanie(); // na miejscu kolizji wypisz znak organizmu silniejszego
					int opcje_ruchu[4] = { 1, 1, 1, 1 }; //1 - mozna przejsc, 0 - nie mozna przejsc
					this->zwiad(opcje_ruchu, x_czlowieka, y_czlowieka, 1);
					this->ucieczka(opcje_ruchu, x_czlowieka, y_czlowieka);
					gotoxy(this->zwroc_polozenie_x() + 1, this->zwroc_polozenie_y() + 1);
					this->rysowanie(); // w miejscu gdzie uciekl czlowiek, wypisz znaczek czlowieka
				}
				else // organizm slabszy -> kolizja zwyczajna
				{
					zwierze::kolizja();
				}
			}
		}
	}
	else // umiejetnosc wylaczona -> kolizja zwyczajna
	{
		zwierze::kolizja();
	}
}
