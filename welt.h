#ifndef WELT_HEADER
#define WELT_HEADER

#include "tiles.h"
#include <vector>
#include "events.h"

typedef std::vector<tiletype> tilecol;
typedef std::vector<tilecol> tileplane;

typedef std::vector<std::vector<std::vector<tiletype> * > > tilestacks;
 class lemming;


#define WELT_W 50
#define WELT_H 50
#define WELT_X_OFFSET ((TILEDIM / 4) * 3)
#define STAGGERED_Y_OFFSET (TILEDIM / 4)

class welt
{
public:
	welt(SDL_Surface * scherm);
	
	void draw();
	
	void addOverlay(int x, int y, tiletype tegel);
	
	static int xOri(int tileX) 				{ return tileX * WELT_X_OFFSET; }
	static int yOri(int tileX, int tileY);
	static bool xStaggeredDown(int tileX) { return tileX % 2 == 1; }
	
	void drawLemmingFrame(int frame, int tileX, int tileY);
	
	void moveView(int X, int Y) { offsetX += X; offsetY += Y;}
	void stepTime(double timeStep = 0.2) { theEvents.increaseTimeBy(timeStep); }
	
	eventList * mainEventList() { return &theEvents; }
		
private:
	eventList	theEvents;
	tiles		_tegels;//, _water;
	tileplane 	_veld;
	tilestacks 	_overlay;
	lemming 	*hank;
	int 		offsetX, offsetY;
};
#endif
