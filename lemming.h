#ifndef LEMMING_H
#define LEMMING_H
#include "events.h"
#include <map>
#include <vector>

class welt;
typedef size_t lemFrame;
typedef std::vector<lemFrame> lemAnim;
enum lemDir 		{ Onder, RechtsOnder, RechtsBoven, Boven, LinksBoven, LinksOnder };
enum lemVisualState { wacht, stilO, stilRO, stilRB, stilB, stilLB, stilLO};
enum lemState		{ neutraal, loop, draai };
typedef std::map<lemVisualState, std::map<lemVisualState, lemAnim> > transitieMap;

inline double mix(double A, double B, double ratio)
{
	return (A * (1.0 - ratio)) + (B * ratio);
}

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
	void consider();
	
	bool beweeg(lemDir richting);
	int	 getFrameCountAnim(lemVisualState A, lemVisualState B) { return visualTransitions[A][B].size(); }
	
	eventList* myList() { return myEvents; }
	
	bool isPos(int x, int y) { return tileX == x && y == tileY; }
	
private:
	static transitieMap visualTransitions;
	eventList 		*myEvents;
	lemVisualState 	currentState, 
					nextState;
	lemFrame 		currentFrame;
	int 			tileX, 
					tileY;
	welt 			*meinWelt;
	lemAnim 		currentAnim;
	size_t 			currentAnimStep;
	
	double			moveTimeBegin, 	moveTimeDuration, 
					oriActualX, 	oriActualY,
					newActualX,		newActualY;
	lemState		toestand;
	
};

struct lemmingEvent : public event
{
	lemmingEvent(double time, std::string eventType, lemming * thisGuy) 
	: event(time, eventType, thisGuy->myList()), actor(thisGuy){}
	
	lemming 		*actor;
};


struct stateChangedEvent : public lemmingEvent
{
	stateChangedEvent(double time, lemming * thisGuy, lemVisualState newState) 
	: lemmingEvent(time, classIdentifier(), thisGuy), state(newState) {}
	
	lemVisualState 	state;
	
	virtual void activate() 				{ actor->stateChanged(state); }
	static const char * classIdentifier() 	{ return "stateChangedEvent"; }
};

struct positionChangedEvent : public lemmingEvent
{
	positionChangedEvent(double time, lemming * thisGuy, int newX, int newY) 
	: lemmingEvent(time, classIdentifier(), thisGuy), tileX(newX), tileY(newY) {}
	
	int 			tileX, 
					tileY;
	
	virtual void activate() 				{ actor->posChanged(tileX, tileY); }
	static const char * classIdentifier() 	{ return "positionChangedEvent"; }
};

struct stepFrameEvent : public lemmingEvent
{
	stepFrameEvent(double time, lemming * thisGuy) 
	: lemmingEvent(time, classIdentifier(), thisGuy) {}
	
	virtual void activate() 				{ actor->stepFrame(); }
	static const char * classIdentifier()	{ return "stepFrameEvent"; }
};

struct considerEvent : public lemmingEvent
{
	considerEvent(double time, lemming * thisGuy) 
	: lemmingEvent(time, classIdentifier(), thisGuy) {}
	
	virtual void activate() 				{ actor->consider(); }
	static const char * classIdentifier()	{ return "considerEvent"; }
};

#endif
