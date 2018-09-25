#include "welt.h"
#include "lemming.h"

welt::welt(SDL_Surface * scherm) : _tegels(scherm), offsetX(0), offsetY(0) 
{
	_veld.resize(WELT_W);
	_overlay.resize(WELT_W);
	
	for(int x=0; x<WELT_W; x++)
	{
		_veld[x].resize(WELT_H);
		_overlay[x].resize(WELT_H);

		for(int y=0; y<WELT_H; y++)
		{
			
			_veld[x][y] = rand()%3;
			
			if(rand()%5 == 0)
				_veld[x][y] = 3;
							
			_overlay[x][y] = NULL;
			
			if(_veld[x][y] < 3 && rand()%3 == 0)
			{
			// 5 lo 6 ro 7 rb 8 lb 9 o 10 b
				_overlay[x][y] = new tilecol;
				
				if(rand()%4==0)
					_overlay[x][y]->push_back(8);
				else
					_overlay[x][y]->push_back(4 + (rand()%4));
			}
			
		}
	}

	for(int i=0; i<2; i++)		
		hanks.push_back(new lemming(this));
}

void welt::addOverlay(int x, int y, tiletype tegel)
{
	if(_overlay[x][y] == NULL)
		_overlay[x][y] = new tilecol;
		
	_overlay[x][y]->push_back(tegel);
}



int welt::yOri(int tileX, int tileY)
{
	return (tileY * TILEDIM) / 2 + (xStaggeredDown(tileX) ? STAGGERED_Y_OFFSET : 0 );
}

void welt::draw()
{
	for(int veldOverlay = 0; veldOverlay < 2; veldOverlay++)
	{
		for(int y=0; y < WELT_H; y++)
			for(int xstart=0; xstart<2; xstart++) // de niet gestaggerede moeten eerst!
				for(int x=xstart; x < WELT_W; x+=2)
				{			
					int drawX = xOri(x);
					int drawY = yOri(x, y);
			
					if(veldOverlay == 0)
						_tegels.drawtile(_veld[x][y], drawX - offsetX, drawY - offsetY);
					else if(_overlay[x][y] != NULL)
						for(int overlay=0; overlay<_overlay[x][y]->size(); overlay++)
							_tegels.drawtile((*_overlay[x][y])[overlay], drawX - offsetX, drawY - offsetY);
				}			
	}
	
	for(int i=0; i<hanks.size(); i++)
		hanks[i]->drawYourself();

}

void welt::drawLemmingFrameInTile(int frame, int tileX, int tileY)
{
	drawLemmingFrame(frame, xLem(tileX), yLem(tileX, tileY));
}

void welt::drawLemmingFrame(int frame, int actualX, int actualY)
{
	_tegels.drawLemmingFrame(frame, 
		actualX - offsetX, 
		actualY - offsetY);
}
