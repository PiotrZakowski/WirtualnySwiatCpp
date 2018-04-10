#include <iostream>
#include "organizm.h"
using namespace std;
#define PUSTY_PIKSEL 255
#define DZIELNIK_RAND 10 // (100/DZIELNIK_RAND)*100%

#ifndef ROSLINA_H
#define ROSLINA_H

class roslina : public organizm
{
public:
	roslina(swiat &swiat, int wsp_x, int wsp_y);

protected:
	void akcja();
	void kolizja();
	void rysowanie();
};

#endif