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

void eventListNode::setNext(eventListNode *newNext)
{
	eventListNode * oldNext = next;
	
	next = newNext;
	newNext->prev = this;
	
	if(oldNext != NULL)
	{
		newNext->next = oldNext;
		oldNext->prev = newNext;
	}
}

eventListNode * eventListNode::insertNode(eventListNode * other)
{
	if(prev != NULL)
	{
		printf("error insert prev = %s at %f\ncurlist=%s\n", prev->identifier().c_str(), prev->time(), allToString().c_str());
		throw exceptioneel("should only insert stuff at root of eventlist!");
	}
		
	if(other->time() < time())
	{
		other->next = this;
		prev = other;
		
		return other;
	}
		
	
	for(eventListNode * cur = this; cur != NULL; cur = cur->next)
		if(cur->next == NULL || cur->next->time() > other->time())
		{
			cur->setNext(other);
			break;
		}
	
	return this;
}

eventListNode::~eventListNode() 
{ 
	delete theEvent; 
	theEvent = NULL; 
	
	if(prev != NULL)
		prev->next = next;
	next = NULL;
		
	if(next != NULL)
		next->prev = prev;
	prev = NULL;
}

eventListNode * eventListNode::removeNode(event * thisEvent, bool deleteEvent)
{
	printf("removeNode %s from list: %s", toString().c_str(), allToString().c_str());

	if(prev != NULL)
		throw exceptioneel("should only remove stuff at root of eventlist!");
		
	if(thisEvent == theEvent)
	{		
		eventListNode * returnThis = next;
		
		if(!deleteEvent)
			theEvent = NULL;
		
		delete this;
		
		printf("just deleted myself and for listhead will return: %s\n", returnThis->toString().c_str());
			
		return returnThis;
	}
		
	
	for(eventListNode * cur = next; cur != NULL; cur = cur->next)
		if(cur->theEvent == thisEvent)
		{
			printf("will delete: %s\n", cur->toString().c_str());
			
			if(!deleteEvent)
				cur->theEvent = NULL;
				
			delete cur;
			break;
		}
		
	printf("will return as listhead me: %s\n", toString().c_str());
	
	return this;
}

void eventListNode::destroyPrevious()
{
	if(prev == NULL)
		return;
		
	delete prev;
	prev = NULL;
}

std::string eventListNode::toString()
{ 
	if(this == NULL)
		return "NULL";
	return theEvent->toString() + "-node"; 
}

std::string eventListNode::allToString()
{
	if(this == NULL)
		return "NULL";
		
	std::stringstream out;
	
	if(prev != NULL)
	{
		out << "not first node! rewinding.... start: " << toString() << "\n";	
		out << prev->allToString();
		return out.str();
	}
	
	for(eventListNode * n = this; n != NULL; n = n->next)
		out << n->toString() << " -> ";

	out << "\n--------------------------------------\n";	
	return out.str();
}

void eventList::addEvent(event * newEvent, eventList * actualParent)
{
	printf("addEvent %s on time %f and mainList is %s!\n", newEvent->identifier.c_str(), newEvent->time, mainList == NULL ? "NULL" : "not NULL");
	printf("pre list= %s \n", listHead->allToString().c_str());
	
	if(newEvent->time < time())
	{
		printf("cannot add events in past! Setting eventtime (%f) to curtime+epsilon(%f).\n", newEvent->time, time()+EPSILON);
		newEvent->time = time() + EPSILON;
	}
	
	eventListNode * node = new eventListNode(actualParent, newEvent);
	
	
	if(listHead == NULL)
	{
	 	printf("listHead == NULL\n");
		listHead = node;
		
		if(mainList != NULL)
			mainList->addEvent(newEvent, actualParent);
	}
	else
	{
		printf("listHead == %s at %f!\n", listHead->identifier().c_str(), listHead->time());
		
		eventListNode * oldHead = listHead;
				
		listHead = listHead->insertNode(node);
		
		if(mainList != NULL && listHead != oldHead)
		{
			//printf("if(mainList != NULL && listHead != oldHead)\n");
			mainList->removeNode(oldHead->theEvent);
			mainList->addEvent(listHead->theEvent);
		}
	}
	
	printf("post list= %s \n", listHead->allToString().c_str());
}

bool eventList::isEventFirst(event *thisEvent)
{
	return listHead != NULL && listHead->theEvent == thisEvent;
}

void eventList::increaseTimeBy(double timeStep)
{
	double endTime = curTime + timeStep;
	
	printf("(%f)", curTime);
	/*if(listHead == NULL)
		printf(" listhead == NULL\n");
	else
		printf(" listHead->time == %f\n", listHead->time());*/
	
	while(listHead != NULL && listHead->time() < endTime)
	{
		curTime 				= listHead->time();	
		event * curEvent 		= listHead->theEvent;
		event * addEventLater 	= NULL;
		eventList * lemmingList = listHead->parent;
		
		if(listHead->parent != NULL && listHead->parent != this)
		{
			printf("Getting next event from lemminglist!\n");
	
			if(!lemmingList->isEventFirst(curEvent))
				throw exceptioneel("event was not first event of lemming!");
			
			lemmingList->removeNode(curEvent);
			
			if(lemmingList->listHead != NULL)
			{
				addEventLater = lemmingList->listHead->theEvent;
				std::cout << "remembering event from lemming to add to mainlist later: " << addEventLater->toString() << "\n"<< std::flush;
			}
				
		}
			
		removeNode(curEvent);
		
		if(addEventLater != NULL)
		{
			printf("Gonna add next event %s for %f\n", addEventLater->identifier.c_str(), addEventLater->time);
			addEvent(addEventLater, lemmingList);
		}
			
		printf("executing event (%s) at %f\n", curEvent->identifier.c_str(), curTime);
		
		curEvent->activate();
		delete curEvent;
	}
	
	curTime = endTime;
}

void eventList::removeNode(event * thisEvent, bool deleteEvent) 
{ 
	printf("removeNode %s\n", thisEvent->toString().c_str());
	if(listHead) 
		listHead = listHead->removeNode(thisEvent, deleteEvent); 
}

double eventList::time() 
{ 
	double t = mainList == NULL ? curTime : mainList->time(); 
//	printf("time requested: %f\n", t);
	
	return t;	
}
