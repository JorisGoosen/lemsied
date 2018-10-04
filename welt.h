#ifndef WELT_HEADER
#define WELT_HEADER

#include <vector>
#include "events.h"
#include "weltveld.h"


typedef std::vector<weltVeld*> veldcol;
typedef std::vector<veldcol> veldplane;

class lemming;
 
double randomDouble(double min, double max);

#define WELT_W 16
#define WELT_H 12
#define WELT_X_OFFSET ((TILEDIM / 4) * 3)
#define STAGGERED_Y_OFFSET (TILEDIM / 4)


class welt
{
public:
	welt(SDL_Surface * scherm);
	
	void draw();
	
	void drawLemmingFrameInTile(int frame, lemPos p);
	void drawLemmingFrame(int frame, int pixelX, int pixelY);
	
	void moveView(int X, int Y) { offsetX += X; offsetY += Y;}
	void stepTime(double timeStep = 0.2) { theEvents.increaseTimeBy(timeStep); }
	
	eventList * mainEventList() { return &theEvents; }
	
	static int validateX(int x) { return std::max(0, std::min(WELT_W - 1, x)); }
	static int validateY(int y) { return std::max(0, std::min(WELT_H - 1, y)); }
	
	static int xLem(lemPos p)	{ return xOri(p) + ((TILEDIM - LEMW) / 2); }
	static int yLem(lemPos p)  	{ return yOri(p) + ((TILEDIM - LEMH) / 2); }
	
	void 		registerLemPos(lemming * lem, lemPos p);
	lemming * 	lemAt(lemPos p); 
	bool 		landFree(lemPos p);
	bool		canWalk(lemPos a, lemDir d);
	lemPos		getPosInDir(lemPos p, lemDir d, lemVisualState * naDraaiVis = NULL);
	bool 		overlayIsOnly(lemPos p, int typeOverlay);
	weltVeld*	cel(lemPos p) { return _veld[p.x][p.y]; }
	
	static int xOri(lemPos p) 	{ return p.x * WELT_X_OFFSET; }
	static int yOri(lemPos p);
		
private:

	static bool xStaggeredDown(int tileX) { return tileX % 2 == 1; }
	eventList	theEvents;
	tiles		_tegels;//, _water;
	veldplane	_veld;
	
	std::vector<lemming*> _lemmings; 
	
	
	int 		offsetX, offsetY;
};
#endif
