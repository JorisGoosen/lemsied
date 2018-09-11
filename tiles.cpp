#include <stdlib.h>
#include <SDL/SDL_image.h>
#include "tiles.h"

bool mustInitIMG = true;

tiles::tiles(SDL_Surface * scherm) : _scherm(scherm)
{
	if(mustInitIMG)
		if(IMG_Init(IMG_INIT_PNG) == 0)
			throw exceptioneel("img init failed\n");	
			
	mustInitIMG = false;
	
	_tiles 		= IMG_Load("GridTiles.png");
	_lemming	= IMG_Load("Lemming.png");
	
	if(_tiles == NULL)
		throw exceptioneel("tiles init failed\n");
		
	if(_lemming == NULL)
		throw exceptioneel("lemming init failed\n");
	
}

void tiles::drawtile(tiletype tile, int x, int y, int w, int h)
{
	if(x > _scherm->w || y > _scherm->h || x + w < 0 || y + h < 0)
		return;
		
	int hierX = tile * TILEDIM;
	int rij = ((hierX - (hierX % _tiles->w)) / _tiles->w);
	int hierY =  rij * TILEDIM;
	hierX = hierX % _tiles->w;

	  
	
	SDL_Rect hier = {hierX, hierY, TILEDIM, TILEDIM};
	SDL_Rect daar = {x, y, w, h};
	
	if(0 != SDL_BlitSurface(_tiles, &hier, _scherm, &daar))
		throw exceptioneel("tiles blit failed\n");
}

void tiles::drawLemmingFrame(int frame, int x, int y)
{	
	SDL_Rect hier = {frame * LEMW, 0, LEMW, LEMH};
	SDL_Rect daar = {x, y, LEMW, LEMH};
	
	if(0 != SDL_BlitSurface(_lemming, &hier, _scherm, &daar))
		throw exceptioneel("lemming blit failed\n");
}

tiles::~tiles()
{
	IMG_Quit();
}
