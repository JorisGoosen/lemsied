#include <SDL/SDL.h>
#include "exceptioneel.h"

typedef int tiletype;

#define TILEDIM 64

class tiles {
public:
	tiles(SDL_Surface * scherm, const char * naam);
	~tiles();
	
	SDL_Surface * surf() { return _tiles; }
	
	void drawtile(tiletype tile, int x, int y, int w = TILEDIM, int h = TILEDIM);
	
private:
	SDL_Surface *_tiles,
				*_scherm;
};
