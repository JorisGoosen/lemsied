#include <SDL/SDL.h>
#include "exceptioneel.h"

typedef int tiletype;

#define TILEDIM 64
#define LEMW 16
#define LEMH 32

class tiles {
public:
	tiles(SDL_Surface * scherm);
	~tiles();
	
	SDL_Surface * surf() { return _tiles; }
	
	void drawtile(tiletype tile, int x, int y, int w = TILEDIM, int h = TILEDIM);
	void drawLemmingFrame(int frame, int x, int y);
	
private:
	SDL_Surface *_tiles,
				*_lemming,
				*_scherm;
};
