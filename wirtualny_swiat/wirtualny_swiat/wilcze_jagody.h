#include <iostream>
#include "roslina.h"
using namespace std;

#ifndef WILCZE_JAGODY_H
#define WILCZE_JAGODY_H

class wilcze_jagody : public roslina
{
public:
	wilcze_jagody(swiat &swiat, int wsp_x, int wsp_y);
protected:
	void kolizja();
};

#endif