#include "welt.h"
#include "lemming.h"

#define RANDOM_DOUBLE_RES 1234567890

double randomDouble(double min, double max)
{
	double randomInt = rand()%RANDOM_DOUBLE_RES;
	randomInt /= RANDOM_DOUBLE_RES;
	randomInt *= max - min;
	
	return min + randomInt;
}

welt::welt(SDL_Surface * scherm) : _tegels(scherm), offsetX(0), offsetY(0) 
{
	_veld.resize(WELT_W);
	_overlay.resize(WELT_W);
	_lemVeld.resize(WELT_W);
	
	for(int x=0; x<WELT_W; x++)
	{
		_veld[x].resize(WELT_H);
		_overlay[x].resize(WELT_H);
		_lemVeld[x].resize(WELT_H);
		

		for(int y=0; y<WELT_H; y++)
		{
			_lemVeld[x][y] = NULL;
			
			_veld[x][y] = rand()%3;
			
			if(rand()%5 == 0)
				_veld[x][y] = 3; // 3 is water
							
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

	for(int i=0; i<12; i++)		
		_lemmings.push_back(new lemming(this));
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
				
					if(veldOverlay == 1)
					{
						lemming * lem = _lemVeld[x][y];
						if(lem != NULL && lem->isPos(x, y))
							lem->drawYourself();
						
					}
				
					int drawX = xOri(x);
					int drawY = yOri(x, y);
			
					if(veldOverlay == 0)
						_tegels.drawtile(_veld[x][y], drawX - offsetX, drawY - offsetY);
					else if(_overlay[x][y] != NULL)
						for(int overlay=0; overlay<_overlay[x][y]->size(); overlay++)
							_tegels.drawtile((*_overlay[x][y])[overlay], drawX - offsetX, drawY - offsetY);
				}			
	}
	
	//for(int i=0; i<_lemmings.size(); i++)
	//	_lemmings[i]->drawYourself();

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

void welt::registerLemPos(lemming * lem, int x, int y)
{
	if(_lemVeld[x][y] != NULL && lem != NULL)
	{
		if(lem != _lemVeld[x][y])
			throw exceptioneel("lemming tries to register itself where somebody is already registered..");
	}

	_lemVeld[x][y] = lem;
	
	
}

lemming * welt::lemAt(int x, int y)
{
	return _lemVeld[x][y];
}

bool welt::landFree(int x, int y)
{
	return _overlay[x][y] == NULL && _veld[x][y] != 3;
}
