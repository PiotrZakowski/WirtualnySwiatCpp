#include <iostream>
#include "zwierze.h"
using namespace std;

#ifndef OWCA_H
#define OWCA_H

class owca : public zwierze
{
public:
	owca(swiat &swiat, int wsp_x, int wsp_y);
};

#endif