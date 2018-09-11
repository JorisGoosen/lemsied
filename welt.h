#ifndef WELT_H
#define WELT_H

#include "tiles.h"
#include <vector>

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
	
	void draw(int offsetX=0, int offsetY=0);
	
	void addOverlay(int x, int y, tiletype tegel);
	
	static int xOri(int tileX) 				{ return tileX * WELT_X_OFFSET; }
	static int yOri(int tileX, int tileY);
		
private:
	tiles		_tegels;//, _water;
	tileplane 	_veld;
	tilestacks _overlay;
	lemming * hank;
};
#endif
