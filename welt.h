#ifndef WELT_HEADER
#define WELT_HEADER

#include "tiles.h"
#include <vector>
#include "events.h"

typedef std::vector<tiletype> tilecol;
typedef std::vector<tilecol> tileplane;

typedef std::vector<std::vector<std::vector<tiletype> * > > tilestacks;
 class lemming;
 
typedef std::vector<lemming*> lemcol;
typedef std::vector<lemcol> lemplane;

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
	
	void addOverlay(int x, int y, tiletype tegel);
	
	static int xOri(int tileX) 				{ return tileX * WELT_X_OFFSET; }
	static int yOri(int tileX, int tileY);
	static bool xStaggeredDown(int tileX) { return tileX % 2 == 1; }
	
	void drawLemmingFrameInTile(int frame, int tileX, int tileY);
	void drawLemmingFrame(int frame, int pixelX, int pixelY);
	
	void moveView(int X, int Y) { offsetX += X; offsetY += Y;}
	void stepTime(double timeStep = 0.2) { theEvents.increaseTimeBy(timeStep); }
	
	eventList * mainEventList() { return &theEvents; }
	
	static int validateX(int x) { return std::max(0, std::min(WELT_W - 1, x)); }
	static int validateY(int y) { return std::max(0, std::min(WELT_H - 1, y)); }
	
	static int xLem(int tileX) 				{ return xOri(tileX) + ((TILEDIM - LEMW) / 2); }
	static int yLem(int tileX, int tileY)  	{ return yOri(tileX, tileY) + ((TILEDIM - LEMH) / 2); }
	
	void registerLemPos(lemming * lem, int x, int y);
	lemming * lemAt(int x, int y); 
	bool landFree(int x, int y);
		
private:
	eventList	theEvents;
	tiles		_tegels;//, _water;
	tileplane 	_veld;
	tilestacks 	_overlay;
	lemplane	_lemVeld;
	
	std::vector<lemming*> _lemmings; 
	
	
	int 		offsetX, offsetY;
};
#endif
