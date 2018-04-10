#include <iostream>
#include "zwierze.h"
using namespace std;

#ifndef ZOLW_H
#define ZOLW_H

class zolw : public zwierze
{
public:
	zolw(swiat &swiat, int wsp_x, int wsp_y);

protected:
	void akcja();
	void kolizja();
};

#endif