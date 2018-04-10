#include <iostream>
#include "zwierze.h"
using namespace std;

#ifndef LIS_H
#define LIS_H

class lis : public zwierze
{
public:
	lis(swiat &swiat, int wsp_x, int wsp_y);
protected:
	void akcja();
};

#endif