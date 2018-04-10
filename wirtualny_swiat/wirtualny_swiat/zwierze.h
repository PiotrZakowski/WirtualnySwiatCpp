#include <iostream>
#include "organizm.h"
using namespace std;
#define PUSTY_PIKSEL 255

#ifndef ZWIERZE_H
#define ZWIERZE_H

class zwierze : public organizm
{
public:
	zwierze(swiat &swiat, int wsp_x, int wsp_y);
protected:
	int pop_polozenie_x;
	int pop_polozenie_y;

	void akcja();
	void kolizja();
	void rysowanie();
	int zwroc_pop_polozenie_x();
	void ustaw_pop_polozenie_x(int wartosc);
	int zwroc_pop_polozenie_y();
	void ustaw_pop_polozenie_y(int wartosc);
	void ucieczka(int* opcje_ucieczki, int x_uciekajacego, int y_uciekajacego);
	void zwiad(int* notatka, int x_zwiadowcy, int y_zwiadowcy, int promien);
};

#endif