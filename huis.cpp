#include "huis.h"

huis::huis()
{
	const int numTypes = 3;
	LO = rand()%numTypes;
	O  = rand()%numTypes;
	RO = rand()%numTypes;
	RB = rand()%numTypes;
	B  = rand()%numTypes;
	LB = rand()%numTypes;
	
	dak = DAK_GRIJS + (rand()%2);
}
	
int huis::offsetWallType(int t)
{
	if(t == RAAM) return 6;
	if(t == DEUR) return 12;
	return 0;
}
	
std::vector<int> huis::voorgrond()
{
	std::vector<int> uit;
	
	uit.push_back((int)(MUUR_LO) + offsetWallType(LO));
	uit.push_back((int)(MUUR_O)  + offsetWallType(O));
	uit.push_back((int)(MUUR_RO) + offsetWallType(RO));
	
	return uit;
}

std::vector<int> huis::achtergrond()
{
	std::vector<int> uit;
	
	uit.push_back((int)MUUR_LB + offsetWallType(LB));
	uit.push_back((int)MUUR_B  + offsetWallType(B));
	uit.push_back((int)MUUR_RB + offsetWallType(RB));
	
	return uit;
}
	
bool huis::isDirOpen(lemDir d)
{
	switch(d)
	{
	case Onder:			return O  == DEUR;
	case RechtsOnder:	return RO == DEUR;
	case RechtsBoven:	return RB == DEUR;
	case Boven:			return B  == DEUR;
	case LinksBoven:	return LB == DEUR;
	case LinksOnder:	return LO == DEUR;
	}
}

