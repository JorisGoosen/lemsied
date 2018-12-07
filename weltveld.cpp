#include "weltveld.h"
#include "lemming.h"

weltVeld::weltVeld()
{
	lem 	= NULL;
	overlay = LEEG;
	domus	= NULL;
	veld	= GRAS0;

	if(true)
	{
		veld = 16 + rand()%6;
		
	/*	if(rand()%6 == 0)			veld = WATER;
		else if(rand()%7 == 0)		overlay = 4 + (rand()%4);
		else 
		if(rand()%7 == 0)		
		domus = new huis();*/
	}
}

bool weltVeld::free()
{
	return overlay == LEEG && veld != WATER;
}

bool weltVeld::canGo(lemDir d)
{
	return free() && (domus == NULL || domus->isDirOpen(d));
}

