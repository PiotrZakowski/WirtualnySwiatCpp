#include <iostream>
#include "zwierze.h"
using namespace std;
#define STRZALKA_GORA 72
#define STRZALKA_DOL 80
#define STRZALKA_LEWO 75
#define STRZALKA_PRAWO 77
#define SPACJA 32

#ifndef CZLOWIEK_H
#define CZLOWIEK_H

class czlowiek : public zwierze
{
public:
	czlowiek(swiat &swiat, int wsp_x, int wsp_y);
protected:
	int tury_umiejetnosc;
	
	int zwroc_ilosc_tur();
	void ustaw_ilosc_tur(int wartosc);
	void akcja();
	void kolizja();
};

#endif