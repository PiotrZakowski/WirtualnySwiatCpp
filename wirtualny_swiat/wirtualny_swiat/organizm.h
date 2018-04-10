#include <iostream>
#include "swiat.h"
using namespace std;

#ifndef ORGANIZM_H
#define ORGANIZM_H

class swiat;
class organizm
{
public:
	organizm(swiat &swiat, int wsp_x, int wsp_y);
	int zwroc_inicjatywe();
	void ustaw_inicjatywe(int wartosc);
	int zwroc_sile();
	void ustaw_sile(int wartosc);
	char zwroc_znak();
	void ustaw_znak(char wartosc);
	int zwroc_wiek();
	void ustaw_wiek(int wartosc);
	int zwroc_polozenie_x();
	void ustaw_polozenie_x(int wartosc);
	int zwroc_polozenie_y();
	void ustaw_polozenie_y(int wartosc);
	void ustaw_czy_zyje(bool wartosc);
	bool sprawdz_czy_zyje();
	void ustaw_kolizje_specjalna(bool wartosc);
	bool sprawdz_kolizja_specjalna();
	bool czy_zajete(int wsp_x,int wsp_y);
	
	virtual void kolizja() = 0;
	virtual void akcja() = 0;
	virtual void rysowanie() = 0;

protected:
	bool czy_zyje;
	int inicjatywa;
	int sila;
	char znak;
	int wiek;
	int polozenie_x;
	int polozenie_y;
	swiat& ref_swiat;
	bool kolizja_specjalna;

	void znajdz_miejsce_dla_potomnego(int* notatka, int x_zwiadowcy, int y_zwiadowcy);
	void rozmnazanie(swiat &swiat, int x_rodzicow, int y_rodzicow);
	void walka(int indeks_defensora, int x_oponentow, int y_oponentow);
};

#endif