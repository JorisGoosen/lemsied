#include "welt.h"

welt::welt(SDL_Surface * scherm) : _tegels(scherm)//, _water(scherm, "WaterGrid.png") 
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
	
	//water= 16 rb 17 b 18 lb 19 lo 20 o 21 ro
	/*
	addOverlay(1,1, 16);
	addOverlay(1,1, 20);
	addOverlay(1,2, 17);
	addOverlay(1,2, 20);
	addOverlay(1,3, 17);
	addOverlay(1,3, 21);
	addOverlay(2,4, 18);
	addOverlay(2,4, 21);*/
}

void welt::addOverlay(int x, int y, tiletype tegel)
{
	if(_overlay[x][y] == NULL)
		_overlay[x][y] = new tilecol;
		
	_overlay[x][y]->push_back(tegel);
}

void welt::draw(int offsetX, int offsetY)
{
	for(int veldOverlay = 0; veldOverlay < 2; veldOverlay++)
	{
		for(int y=0; y < WELT_H; y++)
			for(int xstart=0; xstart<2; xstart++) // de niet gestaggerede moeten eerst!
				for(int x=xstart; x < WELT_W; x+=2)
				{
					bool staggered = x%2 == 1;
			
					int drawX = x * WELT_X_OFFSET;
					int drawY = (y * TILEDIM) / 2;
			
					if(staggered)
						drawY += STAGGERED_Y_OFFSET;
			
					if(veldOverlay == 0)
						_tegels.drawtile(_veld[x][y], drawX - offsetX, drawY - offsetY);
					else if(_overlay[x][y] != NULL)
						for(int overlay=0; overlay<_overlay[x][y]->size(); overlay++)
							_tegels.drawtile((*_overlay[x][y])[overlay], drawX - offsetX, drawY - offsetY);
				}			
	}
}
