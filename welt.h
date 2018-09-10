#include "tiles.h"
#include <vector>

typedef std::vector<tiletype> tilecol;
typedef std::vector<tilecol> tileplane;

#define WELT_W 50
#define WELT_H 50
#define WELT_X_OFFSET ((TILEDIM / 4) * 3)
#define STAGGERED_Y_OFFSET (TILEDIM / 4)

class welt
{
public:
	welt(SDL_Surface * scherm);
	
	void draw(int offsetX=0, int offsetY=0);
		
private:
	tiles		_tegels;
	tileplane 	_veld;
};
