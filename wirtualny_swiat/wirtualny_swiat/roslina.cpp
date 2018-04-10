#include <iostream>
#include "roslina.h"
using namespace std;

roslina::roslina(swiat &swiat, int wsp_x, int wsp_y) : organizm(swiat, wsp_x, wsp_y){};

void roslina::akcja()
{
	int losowa = rand() % DZIELNIK_RAND;
	if (losowa == 0)
	{
		int x_rosliny, y_rosliny;
		x_rosliny = this->zwroc_polozenie_x();
		y_rosliny = this->zwroc_polozenie_y();
		this->rozmnazanie(this->ref_swiat, x_rosliny, y_rosliny);
	}
}

void roslina::kolizja()
{
}

void roslina::rysowanie()
{
	char znak = this->zwroc_znak();
	cout << znak;
}