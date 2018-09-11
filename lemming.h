#ifndef LEMMING_H
#define LEMMING_H

#include <map>
#include <vector>

class welt;
typedef size_t lemFrame;
typedef std::vector<lemFrame> lemAnim;

enum lemVisualState { wacht, stilO, stilRO, stilRB, stilB, stilLB, stilLO};

void fillTransitions();

class lemming 
{
public:
	lemming(welt * umwelt) : currentState(wacht), nextState(wacht), currentFrame(0), tileX(2), tileY(2),
		meinWelt(umwelt) {}

	int getTileX() { return tileX; }
	int getTileY() { return tileY; }
	int getWorldXOri();
	int getWorldYOri();
	
	lemFrame getFrame() { return currentFrame; }
private:
	lemVisualState currentState, nextState;
	lemFrame currentFrame;
	int tileX, tileY;
	welt * meinWelt;
};

#endif
