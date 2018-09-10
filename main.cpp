#include <stdlib.h>
#include <SDL/SDL.h>
#include "welt.h"

welt * wereld;
SDL_Surface * scherm;

int offsetX = 0, offsetY = 0;

void drawwelt()
{
	SDL_FillRect(scherm, NULL, SDL_MapRGBA(scherm->format, 0, 0, 0, 255));
	wereld->draw(offsetX, offsetY);

	SDL_UpdateRect(scherm, 0, 0, 0, 0);
}

int main(int argnum, const char ** args)
{
	SDL_Init(SDL_INIT_VIDEO);

//	scherm = SDL_SetVideoMode(800, 480, 32, SDL_FULLSCREEN); // | SDL_DOUBLEBUF | SDL_HWSURFACE);,
	scherm = SDL_SetVideoMode(800, 432, 32, 0); // | SDL_DOUBLEBUF | SDL_HWSURFACE);,
	if(scherm == NULL ) //|| (scherm->flags & SDL_DOUBLEBUF) == 0 || (scherm->flags & SDL_HWSURFACE) == 0) 
	{
		printf("no scherm //or doublebuf or hwsurf\n");
		return 1;
	}
	
	SDL_EnableKeyRepeat(100, 100);
	
	wereld = new welt(scherm);
	
	SDL_EventState(SDL_KEYDOWN, SDL_ENABLE);
	SDL_EventState(SDL_KEYDOWN, SDL_ENABLE);
	SDL_Event event;
	
	drawwelt();
	bool continueForever = true;
	
	while(continueForever)
	{
		//printf("gonna wait for event\n");
		int waitEvent = SDL_WaitEvent(&event);
		
		//printf("found event! result was %d\n", waitEvent);
		
		if(waitEvent < 1)
		{
			printf("there was some kind of error waiting for event...\n");
			continueForever = false;
		}
		else
		{
			//printf("eventtype  = %d\n", event.type);
			
			if(event.type == SDL_KEYDOWN)
			{
				SDL_KeyboardEvent key = event.key;
			
				int xmov = 10, ymov = xmov;
				bool redraw = true;
				
				//printf("keypressed: %d\n", key.keysym.sym);
			
				switch(key.keysym.sym)
				{
				case SDLK_UP:		offsetY -= ymov;	break;
				case SDLK_DOWN:		offsetY += ymov;	break;
				case SDLK_LEFT:		offsetX -= xmov;	break;
				case SDLK_RIGHT:	offsetX += xmov;	break;
				default:
					redraw = false;
					continueForever = false;
					break;
				
				}
			
				if(redraw)
					drawwelt();
			}
		}
	}

	SDL_Quit();	
	return 0;
}
