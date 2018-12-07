#ifndef WELTVELD_HEADER
#define WELTVELD_HEADER

#include "tiles.h"
#include "lempos.h"
#include "huis.h"

class lemming;

class weltVeld
{
public:
	weltVeld();
	
	bool free();
	bool canGo(lemDir d);
	
	lemming * 	lem;
	tiletype 	veld;
	tiletype 	overlay;
	huis * 		domus;
	bool 		valid = false;
};


#endif
