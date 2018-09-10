#include <stdlib.h>
#include <SDL/SDL.h>
#include "welt.h"

int main(int argnum, const char ** args)
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Surface * scherm = SDL_SetVideoMode(800, 480, 32, SDL_FULLSCREEN); // | SDL_DOUBLEBUF | SDL_HWSURFACE);
	if(scherm == NULL ) //|| (scherm->flags & SDL_DOUBLEBUF) == 0 || (scherm->flags & SDL_HWSURFACE) == 0) 
	{
		printf("no scherm //or doublebuf or hwsurf\n");
		return 1;
	}
	
	//tiles tegels(scherm);
	welt wereld(scherm);
	
	
	SDL_EventState(SDL_KEYDOWN, SDL_ENABLE);
	SDL_Event *event = NULL;
	
/*	tegels.drawtile(2, 0, 0);
	tegels.drawtile(1, 48, 16);
	tegels.drawtile(0, 0, 32);
	tegels.drawtile(1, 96, 0);*/
	
	wereld.draw();

	SDL_UpdateRect(scherm, 0, 0, 0, 0);
	
	while(SDL_WaitEvent(event))
	{
		if(event == NULL || event->type == SDL_KEYDOWN)
			break;
	}

	SDL_Quit();	
	return 0;
}
