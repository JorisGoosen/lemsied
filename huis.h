#ifndef HUIS_HEADER
#define HUIS_HEADER

#include "tiles.h"
#include <vector>
#include "lempos.h"

enum WallType { MUUR, RAAM, DEUR};

class huis
{
public:
	huis();

	int LO, O, RO, RB, B, LB;
	int	dak;
	
	std::vector<int> voorgrond();
	std::vector<int> achtergrond();
	
	bool isDirOpen(lemDir d);
	
	static int offsetWallType(int t);
};

#endif
