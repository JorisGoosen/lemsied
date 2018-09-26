#include <stdlib.h>
#include <SDL/SDL.h>
#include "welt.h"
#include <bits/time.h>

welt * wereld;
SDL_Surface * scherm;

#define TIMESTEP 0.025

void drawwelt()
{
	SDL_FillRect(scherm, NULL, SDL_MapRGBA(scherm->format, 0, 0, 0, 255));
	wereld->draw();

	SDL_UpdateRect(scherm, 0, 0, 0, 0);
}

int main(int argnum, const char ** args)
{
	try
	{
		srand(time(NULL));
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
			int pollEvent = SDL_PollEvent(&event);
		
			if(pollEvent == 1)
			{	
				if(event.type == SDL_KEYDOWN)
				{
					SDL_KeyboardEvent key = event.key;
			
					int xmov = 10, ymov = xmov;
				
					switch(key.keysym.sym)
					{
					case SDLK_UP:		wereld->moveView(0,	-ymov);	break;
					case SDLK_DOWN:		wereld->moveView(0,	 ymov);	break;
					case SDLK_LEFT:		wereld->moveView(-xmov, 0);	break;
					case SDLK_RIGHT:	wereld->moveView( xmov, 0);	break;
				
					default:			continueForever = false;	break;
					}
				}
			}
		
			//usleep(1000000 * TIMESTEP);
			wereld->stepTime(TIMESTEP);
			drawwelt();

		}

		SDL_Quit();	
		return 0;
	}
	catch(exceptioneel e)
	{
		printf("exceptionele situatie: %s", e.what());
	}
	catch(...)
	{
		printf("onbekende afwijking...");
	}
}
