#include <iostream>
#include "owca.h"
using namespace std;

owca::owca(swiat &swiat, int wsp_x, int wsp_y) : zwierze(swiat, wsp_x, wsp_y)
{
	this->ustaw_znak('O');
	this->ustaw_sile(4);
	this->ustaw_inicjatywe(4);
	this->ustaw_kolizje_specjalna(false);
	this->ref_swiat.powiekszenie_swiata();
	//this->ref_swiat.organizmy[this->ref_swiat.zwroc_liczbe_organizmow() - 1] = this;
	this->ref_swiat.organizmy[this->ref_swiat.zwroc_odpowiedni_indeks(this->zwroc_inicjatywe())] = this;
}