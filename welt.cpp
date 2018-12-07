#include "welt.h"
#include "lemming.h"
#include <iostream>

#define RANDOM_DOUBLE_RES 1234567890


size_t SCREEN_WIDTH_PIX		= 0;
size_t SCREEN_HEIGHT_PIX 	= 0;

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
	
	for(int x=0; x<WELT_W; x++)
	{
		_veld[x].resize(WELT_H);
		
		for(int y=0; y<WELT_H; y++)
			_veld[x][y] = new weltVeld();
	}

	for(int i=0; i<90; i++)		
		_lemmings.push_back(new lemming(this));
}

int welt::yOri(lemPos p)
{
	return (p.y * TILEDIM) / 2 + (xStaggeredDown(p.x) ? STAGGERED_Y_OFFSET : 0 );
}

void welt::draw()
{
	lemPos minBB(1 + (offsetX / WELT_X_OFFSET), 1 + (offsetY / TILEDIM)), maxBB(minBB.x + SCREEN_WIDTH - 2, minBB.y + SCREEN_HEIGHT - 2);
	//lemPos minBB(3, 3), maxBB(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	for(int veldOverlay = 0; veldOverlay < 2; veldOverlay++)	
		for(int y=std::max(0, minBB.y); y < std::min(WELT_H, maxBB.y); y++)
			for(int xstart=0; xstart<2; xstart++) // de niet gestaggerede moeten eerst!
				for(int x=std::max(0, minBB.x) + xstart; x < std::min(WELT_W, maxBB.x); x+=2)
				{
					lemPos p(x, y);
					
					/*bool 	invalidated = !_veld[x][y]->valid || !_valid,
							lemAbove 	= false,
							lemBelow 	= false,
							lemHiero	= _veld[x][y]->lem != NULL;

					

					if(!invalidated)
						for(int xp = -1; xp < 2; xp++)
							for(int yp = -1; yp < 2; yp++)
								if(_veld[validateX(xp + p.x)][validateY(yp + p.y)]->lem != NULL)
								{
									if(yp < 0)	lemAbove = true;
									if(yp > 0)	lemBelow = true;
								}

					invalidated = invalidated || lemHiero;

					if(invalidated || lemAbove || lemBelow)*/
					{			
						int drawX = xOri(p) - offsetX;
						int drawY = yOri(p) - offsetY;
				
						switch(veldOverlay)
						{
						case 0:
							//if(!(invalidated || lemBelow))
							//	break;

							_tegels.drawtile(_veld[x][y]->veld, drawX, drawY);
							break;
						
						case 1:
						{
							if(_veld[x][y]->domus != NULL)
							{
								std::vector<int> achter = _veld[x][y]->domus->achtergrond();
								
								for(int i=0; i<achter.size(); i++)
									_tegels.drawWall(achter[i], drawX, drawY);
							}
							
							if(_veld[x][y]->overlay != LEEG)
								_tegels.drawtile(_veld[x][y]->overlay, drawX, drawY);
								
							lemming * lem = _veld[x][y]->lem;
							if(lem != NULL && lem->isPos(p))
								lem->drawYourself();
								
							if(_veld[x][y]->domus != NULL)
							{
								std::vector<int> voor = _veld[x][y]->domus->voorgrond();
								
								for(int i=0; i<voor.size(); i++)
									_tegels.drawWall(voor[i], drawX, drawY);
									
								_tegels.drawtile(_veld[x][y]->domus->dak, drawX, drawY - DAKOFFSET);
							}	
							
							break;
						}
							
						}
							
					}	
					
					if(veldOverlay == 1)
						_veld[x][y]->valid = true;

				}		
	
	
	//for(int i=0; i<_lemmings.size(); i++)
	//	_lemmings[i]->drawYourself();

	_valid = true;
}

void welt::drawLemmingFrameInTile(int frame, lemPos p)
{
	drawLemmingFrame(frame, xLem(p), yLem(p));
}

void welt::drawLemmingFrame(int frame, int actualX, int actualY)
{
	_tegels.drawLemmingFrame(frame, 
		actualX - offsetX, 
		actualY - offsetY);
}

void welt::registerLemPos(lemming * lem, lemPos p)
{
	if(_veld[p.x][p.y]->lem != NULL && lem != NULL)
	{
		if(lem != _veld[p.x][p.y]->lem)
			throw exceptioneel("lemming tries to register itself where somebody is already registered..");
	}

	_veld[p.x][p.y]->lem 	= lem;
	_veld[p.x][p.y]->valid 	= false;
	
}

lemming * welt::lemAt(lemPos p)
{
	return _veld[p.x][p.y]->lem;
}

bool welt::overlayIsOnly(lemPos p, int typeOverlay)
{		
	return _veld[p.x][p.y]->overlay == typeOverlay;
}

bool welt::landFree(lemPos p)
{
	return _veld[p.x][p.y]->free();
}

bool welt::canWalk(lemPos a, lemPos b)
{
	if(a == b) return true;
	
	huis *ha = cel(a)->domus, *hb = cel(b)->domus;
	
	if(ha == NULL && hb == NULL)
		return cel(b)->free();

	int xMove = b.x - a.x;
	int yMove = b.y - a.y;	
	
	if(xMove != 0)
	{
		if(xStaggeredDown(a.x))
		{
			if(yMove == 0)
				yMove = -1;
		}	
		else 
		{
			if(yMove == 0)
				yMove = 1;
		}
	}
	
	lemDir toB, fromA;
	
	if(xMove == 0)
	{
		if(yMove > 0)
		{
			toB 	= Onder;
			fromA 	= Boven;
		}
		else 
		{
			toB 	= Boven;
			fromA 	= Onder;
		}
	} 
	else if(xMove > 0)
	{
		if(yMove > 0)
		{
			toB 	= RechtsOnder;
			fromA 	= RechtsBoven;
		}
		else
		{
			toB 	= RechtsBoven;
			fromA 	= RechtsOnder;
		}
	}
	else
	{
		if(yMove > 0)
		{
			toB 	= LinksOnder;
			fromA 	= LinksBoven;
		}
		else
		{
			toB 	= LinksBoven;
			fromA 	= LinksOnder;
		}
	}
	
	//std::cout << "can walk from " << a.toString() << " to " <<  b.toString() << " in dir "<<xMove<<", "<<yMove<<"? ";
	
	bool free = cel(b)->free();
	
	if(ha != NULL && !ha->isDirOpen(toB))
		free = false;
		
	if(hb != NULL && !hb->isDirOpen(fromA))
		free = false;
		
	//std::cout << (free?"yes!":"no!")<< std::endl;
	
	
	return free;
}

lemPos welt::getPosInDir(lemPos p, lemDir d, lemVisualState * naDraaiVisP)
{
	bool downStag = welt::xStaggeredDown(p.x);
	
	int newX = p.x, newY = p.y;
	
	lemVisualState naDraaiVis;
	
	switch(d)
	{
	default:
	case Onder: 		naDraaiVis = stilO;								newY++;	break;
	case RechtsOnder: 	naDraaiVis = stilRO;	newX++;	if( downStag)	newY++;	break;
	case RechtsBoven: 	naDraaiVis = stilRB;	newX++;	if(!downStag)	newY--;	break;
	case Boven: 		naDraaiVis = stilB;								newY--;	break;
	case LinksBoven: 	naDraaiVis = stilLB;	newX--;	if(!downStag)	newY--;	break;
	case LinksOnder: 	naDraaiVis = stilLO;	newX--;	if( downStag)	newY++;	break;
	}
	
	newX = welt::validateX(newX);
	newY = welt::validateY(newY);
	
	if(naDraaiVisP != NULL)
		(*naDraaiVisP) = naDraaiVis;
	
	return lemPos(newX, newY);
}
