#ifndef WELTVELD_HEADER
#define WELTVELD_HEADER

#include "tiles.h"
#include "lempos.h"
#include "huis.h"
#include "perlin.h"

class lemming;

class weltVeld
{
public:
	weltVeld(glm::vec3 p);
	
	bool free();
	bool canGo(lemDir d);
	
	lemming * 	lem;
	tiletype 	veld;
	tiletype 	overlay;
	huis * 		domus;
	bool 		valid = false;
	glm::vec3 	pos;
};


#endif
