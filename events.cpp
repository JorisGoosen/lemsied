#include "events.h"
#include "exceptioneel.h"
#include <iostream>
#include <sstream>

std::string event::toString() 
{ 
	std::stringstream out;

	if(this == NULL)
		out << "NULL";
	else
		out << "event "<< identifier << " at t " << time << "("<<this<<")";
	return out.str();
	
}

bool compPair(std::pair<double, event*> a, std::pair<double, event*> b)
{
	return a.first < b. first;
}

void eventList::addEvent(event * newEvent)
{	
	if(newEvent->time < time())
	{
		printf("cannot add events in past! Setting eventtime (%f) to curtime+epsilon(%f).\n", newEvent->time, time()+EPSILON);
		newEvent->time = time() + EPSILON;
	}
	
	event * oudeEersteEvent = events.size() > 0 ? events.begin()->second : NULL;
	
	events.push_back(std::make_pair<double, event*>(newEvent->time, newEvent));
	events.sort(compPair);
	
	if(mainList != NULL) //we zitten in een lemminglist
	{		
		event * huidigeEersteEvent = events.begin()->second;
		
		if(huidigeEersteEvent != oudeEersteEvent)
		{
			if(oudeEersteEvent != NULL)
				mainList->removeEvent(oudeEersteEvent);
				
			mainList->addEvent(huidigeEersteEvent);
		}
	}
}

void eventList::increaseTimeBy(double timeStep)
{
	double endTime = curTime + timeStep;

	
	while(events.size() > 0 && events.begin()->first <= endTime)
	{
		curTime 			= events.begin()->first;	
		event * curEvent 	= events.begin()->second;
		eventList * lemList = curEvent->parent;
		
		removeEvent(curEvent);

		if(lemList != this)
		{
			if(!lemList->isEventFirst(curEvent))
				throw exceptioneel("Event "+curEvent->toString()+" is executed but wasnt first on lemList!");
				
			lemList->removeEvent(curEvent);
			if(lemList->size() > 0)
				addEvent(lemList->firstEvent());
		}
		
		//printf("executing event (%s) at %f\n", curEvent->identifier.c_str(), curTime);
		curEvent->activate();
		delete curEvent;
	}
	
	curTime = endTime;
}

void eventList::removeEvent(event * thisEvent) 
{ 
	for(std::list<std::pair<double, event*> >::iterator it=events.begin(); it != events.end(); it++)
		if(it->second == thisEvent)
		{
			events.erase(it);
			return;
		}
}

double eventList::time() 
{ 
	double t = mainList == NULL ? curTime : mainList->time(); 
	
	return t;	
}
