#include "weltveld.h"
#include "lemming.h"

weltVeld::weltVeld(glm::vec3 p)
{
	lem 	= NULL;
	overlay = LEEG;
	domus	= NULL;
	veld	= GRAS0;
	pos	 	= p;

	if(true)
	{
		int maxim = 6;
		int deze = std::min(std::max(int(Perlin::thePerlin()->GetIniqoQuilesNoise(p * glm::vec3(0.012f, 0.01f, 1.0f))  * maxim), 0), maxim);
		
		veld = deze + 16;
		if(deze >= 2 && deze < 5 && Perlin::thePerlin()->GetIniqoQuilesNoise(p * glm::vec3(0.00333f, 0.0056f, 0.1230f)) > 0.85f)
			veld = WATER;
		else if(deze < 3 && rand()%4 == 0)
			overlay = 4 + rand()%4;
		else if(deze > 5 && rand()%6 == 0)
			domus = new huis();
		


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

