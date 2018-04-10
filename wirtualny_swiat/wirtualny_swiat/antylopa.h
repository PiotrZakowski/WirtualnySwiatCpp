#include <iostream>
#include "zwierze.h"
using namespace std;

#ifndef ANTYLOPA_H
#define ANTYLOPA_H

class antylopa : public zwierze
{
public:
	antylopa(swiat &swiat, int wsp_x, int wsp_y);

protected:
	void akcja();
	void kolizja();
};

#endif