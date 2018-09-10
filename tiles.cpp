#include <stdlib.h>
#include <SDL/SDL_image.h>
#include "tiles.h"

tiles::tiles(SDL_Surface * scherm) : _scherm(scherm)
{
	if(IMG_Init(IMG_INIT_PNG) == 0)
		throw exceptioneel("img init failed\n");	
	
	_tiles = IMG_Load("GridTiles.png");
	
	if(_tiles == NULL)
		throw exceptioneel("tiles init failed\n");
	
}

void tiles::drawtile(tiletype tile, int x, int y, int w, int h)
{
	int hierX = tile * TILEDIM;
	int hierY = ((hierX - (hierX % _tiles->w)) / _tiles->w) * TILEDIM;
	
	SDL_Rect hier = {hierX, hierY, TILEDIM, TILEDIM};
	SDL_Rect daar = {x, y, w, h};
	
	if(0 != SDL_BlitSurface(_tiles, &hier, _scherm, &daar))
		throw exceptioneel("blit failed\n");
}

tiles::~tiles()
{
	IMG_Quit();
}
