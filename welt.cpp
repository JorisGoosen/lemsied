#include "welt.h"

welt::welt(SDL_Surface * scherm) : _tegels(scherm) 
{
	_veld.resize(WELT_W);
	
	for(int x=0; x<WELT_W; x++)
	{
		_veld[x].resize(WELT_H);

		for(int y=0; y<WELT_H; y++)
			_veld[x][y] = rand()%3;
	}
}

void welt::draw(int offsetX, int offsetY)
{
	for(int x=0; x < WELT_W; x++)
		for(int y=0; y < WELT_H; y++)
		{
			bool staggered = x%2 == 1;
			
			int drawX = x * WELT_X_OFFSET;
			int drawY = (y * TILEDIM) / 2;
			
			if(staggered)
				drawY += STAGGERED_Y_OFFSET;
			
			_tegels.drawtile(_veld[x][y], drawX, drawY);
		}
}
