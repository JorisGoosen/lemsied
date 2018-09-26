#ifndef EVENTS_H
#define EVENTS_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string>
#include <list>
#include <algorithm>

#define EPSILON 0.00000000001

class eventList;

struct event
{
	event(double time, std::string identifier, eventList * parent = NULL) : time(time), identifier(identifier), parent(parent) {}

	double time;
	std::string identifier;
	
	virtual void activate() = 0;
	static const char * classIdentifier() { return "undifferentiated"; }
	
	std::string toString();
	
	eventList * parent;
};

class eventList 
{
public:
	eventList(eventList * mainList = NULL) : curTime(0), mainList(mainList) {}
	
	void 	addEvent(event * newEvent);
	void 	increaseTimeBy(double timeStep);
	void 	removeEvent(event * thisEvent);
	bool 	isEventFirst(event *thisEvent)	{ return firstEvent() == thisEvent; }
	event*	firstEvent()					{ return events.size()>0 ? events.begin()->second : NULL; }
	size_t	size()							{ return events.size(); }
	
	double time();
	
private:
	double 			curTime;
	eventList 		*mainList;
	
	std::list<std::pair<double, event *> > events;
};
#endif
