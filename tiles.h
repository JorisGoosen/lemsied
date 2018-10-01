#ifndef TILES_HEADER
#define TILES_HEADER

#include <SDL/SDL.h>
#include "exceptioneel.h"

typedef int tiletype;

#define TILEDIM 64
#define LEMW 16
#define LEMH 32
#define WALLH 80
#define WALLW TILEDIM

enum  TileNum { GRAS0=0, GRAS1, GRAS2, WATER, BOMEN0, BOMEN1, BOSJE0, BOOM0, DAK_GRIJS, DAK_ROOD};
	
enum WallNum { 	MUUR_LO, MUUR_O, MUUR_RO, MUUR_LB, MUUR_B, MUUR_RB,
				RAAM_LO, RAAM_O, RAAM_RO, RAAM_LB, RAAM_B, RAAM_RB,
				DEUR_LO, DEUR_O, DEUR_RO, DEUR_LB, DEUR_B, DEUR_RB};

class tiles {
public:
	tiles(SDL_Surface * scherm);
	~tiles();
	
	SDL_Surface * surf() { return _tiles; }
	
	void drawtile(tiletype tile, int x, int y, int w = TILEDIM, int h = TILEDIM);
	void drawWall(tiletype tile, int x, int y);
	void drawLemmingFrame(int frame, int x, int y);
	
	
private:
	SDL_Surface *_tiles,
				*_lemming,
				*_muren,
				*_scherm;
};

#endif
