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
		
	hank = new lemming(this);
	
	theEvents.addEvent(new positionChangedEvent(1, hank, 2, 3));
	
	for(double tijd = 2; tijd<30; tijd+=3)
	{
		theEvents.addEvent(new stateChangedEvent(tijd, 			hank, stilLO));
		theEvents.addEvent(new stateChangedEvent(tijd + 0.5, 	hank, stilLB));
		theEvents.addEvent(new stateChangedEvent(tijd + 1.0, 	hank, stilB));
		theEvents.addEvent(new stateChangedEvent(tijd + 1.5, 	hank, stilRB));
		theEvents.addEvent(new stateChangedEvent(tijd + 2.0, 	hank, stilRO));
		theEvents.addEvent(new stateChangedEvent(tijd + 2.5, 	hank, stilO));
	}
	
	for(double tijd = 32; tijd<60; tijd+=3)
	{
		theEvents.addEvent(new stateChangedEvent(tijd, 			hank, stilRO));
//		theEvents.addEvent(new stateChangedEvent(tijd + 0.5, 	hank, stilRB));
//		theEvents.addEvent(new stateChangedEvent(tijd + 1.0, 	hank, stilB));
		theEvents.addEvent(new stateChangedEvent(tijd + 1.5, 	hank, stilLB));
		theEvents.addEvent(new stateChangedEvent(tijd + 2.0, 	hank, stilLO));
		theEvents.addEvent(new stateChangedEvent(tijd + 2.5, 	hank, stilO));
	}
	
	theEvents.addEvent(new stateChangedEvent(63, 	hank, stilO));
	
	theEvents.addEvent(new positionChangedEvent(2, hank, 2, 4));
	
	theEvents.addEvent(new positionChangedEvent(3, hank, 3, 4));
	theEvents.addEvent(new positionChangedEvent(4, hank, 3, 5));
	
	printf("events done\n");
}

void welt::addOverlay(int x, int y, tiletype tegel)
{
	if(_overlay[x][y] == NULL)
		_overlay[x][y] = new tilecol;
		
	_overlay[x][y]->push_back(tegel);
}

int welt::yOri(int tileX, int tileY)
{
	bool staggered = tileX%2 == 1;

	int drawY = (tileY * TILEDIM) / 2;

	if(staggered)
		drawY += STAGGERED_Y_OFFSET;
		
	return drawY;
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
	
//	lemming hank(this);
	hank->drawYourself();
	hank->stepFrame();
}

void welt::drawLemmingFrame(int frame, int tileX, int tileY)
{
	_tegels.drawLemmingFrame(frame, 
		xOri(tileX) + ((TILEDIM - LEMW) / 2) - offsetX, 
		yOri(tileX, tileY) + ((TILEDIM - LEMH) / 2) - offsetY);
}
