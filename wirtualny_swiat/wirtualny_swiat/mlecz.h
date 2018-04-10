#include <iostream>
#include "roslina.h"
using namespace std;

#ifndef MLECZ_H
#define MLECZ_H

class mlecz : public roslina
{
public:
	mlecz(swiat &swiat, int wsp_x, int wsp_y);

protected:
	void akcja();
};

#endif