#include <iostream>
#include "roslina.h"
using namespace std;

#ifndef GUARANA_H
#define GUARANA_H

class guarana : public roslina
{
public:
	guarana(swiat &swiat, int wsp_x, int wsp_y);

protected:
	void kolizja();
};

#endif