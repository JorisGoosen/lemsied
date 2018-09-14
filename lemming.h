#ifndef LEMMING_H
#define LEMMING_H
#include "events.h"
#include <map>
#include <vector>

class welt;
typedef size_t lemFrame;
typedef std::vector<lemFrame> lemAnim;
enum lemVisualState { wacht, stilO, stilRO, stilRB, stilB, stilLB, stilLO};

typedef std::map<lemVisualState, std::map<lemVisualState, lemAnim> > transitieMap;



class lemming 
{
public:
	lemming(welt * umwelt);
	int getTileX() { return tileX; }
	int getTileY() { return tileY; }
	int getWorldXOri();
	int getWorldYOri();
	
	void stepFrame();
	void setCurrentFrame();
	void loadAnim();
	void fillTransitions();
	
	lemFrame getFrame() { return currentFrame; }
	
	void drawYourself();
	
	void stateChanged(lemVisualState newState);
	void posChanged(int newTileX, int newTileY);
	
private:
	static transitieMap visualTransitions;
	lemVisualState 	currentState, 
					nextState;
	lemFrame 		currentFrame;
	int 			tileX, 
					tileY;
	welt 			*meinWelt;
	lemAnim 		currentAnim;
	size_t 			currentAnimStep;
	eventList 		*myEvents;
};


struct stateChangedEvent : public event
{
	stateChangedEvent(double time, lemming * thisGuy, lemVisualState newState) 
	: event(time, classIdentifier()), actor(thisGuy), state(newState) {}
	
	lemming 		*actor;
	lemVisualState 	state;
	
	virtual void activate();
	static const char * classIdentifier() { return "stateChangedEvent"; }
};

struct positionChangedEvent : public event
{
	positionChangedEvent(double time, lemming * thisGuy, int newX, int newY) 
	: event(time, classIdentifier()), actor(thisGuy), tileX(newX), tileY(newY) {}
	
	lemming 		*actor;
	int 			tileX, 
					tileY;
	
	virtual void activate();
	static const char * classIdentifier() { return "positionChangedEvent"; }
};


#endif
