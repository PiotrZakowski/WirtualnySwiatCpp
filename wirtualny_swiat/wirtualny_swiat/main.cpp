#include <iostream>
#include <ctime>

//------ZOO-------//
#include "swiat.h"
#include "organizm.h"
//---Zwierzeta---//
#include "zwierze.h"
#include "czlowiek.h"
#include "wilk.h"
#include "owca.h"
#include "lis.h"
#include "zolw.h"
#include "antylopa.h"
//----Rosliny----//
#include "roslina.h"
#include "trawa.h"
#include "mlecz.h"
#include "guarana.h"
#include "wilcze_jagody.h"
//----------------//

using namespace std;
#define ESCAPE 27

int main()
{
	srand((unsigned int)time(NULL));
	swiat wirtualny_swiat;
	
	czlowiek Piotrek(wirtualny_swiat, 10, 10);
	wilk Kiel(wirtualny_swiat, 1, 1);
	wilk Stark(wirtualny_swiat, 3, 2);
	owca Dolly(wirtualny_swiat, 8, 9);
	owca Sheepe(wirtualny_swiat, 9, 8);
	lis Chytrusek(wirtualny_swiat, 6, 6);
	lis Ruda(wirtualny_swiat, 7, 7);
	zolw Czereplacha(wirtualny_swiat, 18, 0);
	zolw Turtie(wirtualny_swiat, 0, 18);
	antylopa Gizella(wirtualny_swiat, 19, 15);
	antylopa Asior(wirtualny_swiat, 19, 19);
	trawa Marichuanen(wirtualny_swiat, 4, 2);
	trawa Samosiejka(wirtualny_swiat, 16, 16);
	mlecz Mleczyk(wirtualny_swiat, 11, 11);
	mlecz Chwast(wirtualny_swiat, 18, 9);
	guarana Eatme(wirtualny_swiat, 10, 9);
	guarana Energizer(wirtualny_swiat, 0, 16);
	wilcze_jagody Donteatme(wirtualny_swiat, 0, 19);
	wilcze_jagody Instadeath(wirtualny_swiat, 15, 15);

	wirtualny_swiat.rysujSwiat();
	unsigned char klawisz = getch();
	while (klawisz != ESCAPE)
	{
		wirtualny_swiat.wykonajTure();
		klawisz = getch();
	}
}

//!!! SORT
//!!! REDUKCJA