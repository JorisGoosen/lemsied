#ifndef EVENTS_H
#define EVENTS_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string>

#define EPSILON 0.00000000001

struct event
{
	event(double time, std::string identifier) : time(time), identifier(identifier) {}

	double time;
	std::string identifier;
	
	virtual void activate() = 0;
	static const char * classIdentifier() { return "undifferentiated"; }
	
	std::string toString();
};

class eventList;

class eventListNode 
{
public:
	eventListNode(eventList * parent, event *theEvent) 
	: theEvent(theEvent), parent(parent), prev(NULL), next(NULL) {}
	~eventListNode();
	
	eventListNode * insertNode(eventListNode * other); // returns new headnode
	eventListNode * removeNode(event * thisEvent, bool deleteEvent); // returns new headnode
	
	void setNext(eventListNode *newNext);
	void destroyPrevious();

	
	event * theEvent;
	eventList * parent; // per lemming list!
	struct eventListNode *prev, *next;
	
	double time() 				{ return theEvent->time; }
	std::string identifier() 	{ return theEvent->identifier; }
	
	std::string toString();
	std::string allToString();
};

class eventList 
{
public:
	eventList(eventList * mainList = NULL) : curTime(0), listHead(NULL), mainList(mainList) {}
	
	
	void addEvent(event * newEvent, eventList * parent);
	void addEvent(event * newEvent) { addEvent(newEvent, this);	}
	void increaseTimeBy(double timeStep);
	void removeNode(event * thisEvent, bool deleteEvent = false);
	bool isEventFirst(event *thisEvent);
	
	double time();
	
private:
	double 			curTime;
	eventListNode 	*listHead;
	eventList 		*mainList;
};
#endif
