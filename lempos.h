#ifndef LEMPOS_HEADER
#define LEMPOS_HEADER

enum lemDir 		{ Onder, RechtsOnder, RechtsBoven, Boven, LinksBoven, LinksOnder };
enum lemVisualState { wacht, stilO, stilRO, stilRB, stilB, stilLB, stilLO};
enum lemState		{ neutraal, loop, draai };

struct lemPos
{
	lemPos(int x = 0, int y = 0) : x(x), y(y) {}
	int x, y;
	
	bool operator==(lemPos & a) { return a.x == x && a.y == y; } 
};

#endif
