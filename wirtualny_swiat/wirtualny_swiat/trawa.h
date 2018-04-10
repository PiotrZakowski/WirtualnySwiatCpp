#include <iostream>
#include "roslina.h"
using namespace std;

#ifndef TRAWA_H
#define TRAWA_H

class trawa : public roslina
{
public:
	trawa(swiat &swiat, int wsp_x, int wsp_y);
};

#endif