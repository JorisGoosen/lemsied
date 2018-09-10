#include <stdlib.h>
#include <SDL/SDL.h>

int main(int argnum, const char ** args)
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Surface * surface = SDL_SetVideoMode(800, 480, 0, SDL_FULLSCREEN | SDL_DOUBLEBUF);
	
	if(surface == NULL) 
		return 1;
	
	SDL_EventState(SDL_KEYDOWN, SDL_ENABLE);
	SDL_Event *event = NULL;
	
	while(SDL_WaitEvent(event))
	{
		if(event == NULL || event->type == SDL_KEYDOWN)
			break;
	}

	
	SDL_Quit();	
	return 0;
}
