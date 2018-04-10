#include <iostream>
#include "zwierze.h"
using namespace std;

#ifndef WILK_H
#define WILK_H

class wilk : public zwierze
{
public:
	wilk(swiat &swiat, int wsp_x, int wsp_y);
};

#endif