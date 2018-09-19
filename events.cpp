#include "events.h"
#include "exceptioneel.h"

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
		throw exceptioneel("should only insert stuff at root of eventlist!");
		
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
	if(prev != NULL)
		throw exceptioneel("should only remove stuff at root of eventlist!");
		
	if(thisEvent == theEvent)
	{
		if(next != NULL)
			next->prev = NULL;
		
		eventListNode * returnThis = next;
		
		if(!deleteEvent)
			theEvent = NULL;
		
		delete this;
			
		return returnThis;
	}
		
	
	for(eventListNode * cur = next; cur != NULL; cur = cur->next)
		if(cur->theEvent == thisEvent)
		{
			if(!deleteEvent)
				cur->theEvent = NULL;
				
			delete cur;
			break;
		}
	
	return this;
}

void eventListNode::destroyPrevious()
{
	if(prev == NULL)
		return;
		
	delete prev;
	prev = NULL;
}

void eventList::addEvent(event * newEvent, eventList * actualParent)
{
	if(newEvent->time <= time())
	{
//		printf("cannot add events in past! Setting eventtime (%f) to curtime+epsilon(%f).\n", newEvent->time, time()+EPSILON);
		newEvent->time = time() + EPSILON;
	}
	eventListNode * node = new eventListNode(actualParent, newEvent);
	
	
	if(listHead == NULL)
	{
		listHead = node;
		
		if(mainList != NULL)
			mainList->addEvent(newEvent, actualParent);
	}
	else
	{
		eventListNode * oldHead = listHead;
		
		listHead = listHead->insertNode(node);
		
		if(mainList != NULL && listHead != oldHead)
		{
			mainList->removeNode(oldHead->theEvent);
			mainList->addEvent(listHead->theEvent);
		}
	}
	
	
}

bool eventList::isEventFirst(event *thisEvent)
{
	return listHead != NULL && listHead->theEvent == thisEvent;
}

void eventList::increaseTimeBy(double timeStep)
{
	double endTime = curTime + timeStep;
	
	printf(".");
	
	while(listHead != NULL && listHead->time() < endTime)
	{
		curTime 				= listHead->time();	
		event * curEvent 		= listHead->theEvent;
		event * addEventLater 	= NULL;
		eventList * lemmingList = listHead->parent;
		
		printf("executing event (%s) at %f\n", curEvent->identifier.c_str(), curTime);
		
		curEvent->activate();
		
		if(listHead->parent != NULL && listHead->parent != this)
		{
			//printf("Getting next event from lemminglist!\n");
	
			if(!lemmingList->isEventFirst(curEvent))
				throw exceptioneel("event was not first event of lemming!");
			
			lemmingList->removeNode(curEvent);
			
			if(lemmingList->listHead != NULL)
				addEventLater = lemmingList->listHead->theEvent;
		}
			
		eventListNode * deleteMe	= listHead;
		listHead					= listHead->next;
	
		delete deleteMe;	
		
		if(addEventLater != NULL)
			addEvent(addEventLater, lemmingList);
	}
	
	curTime = endTime;
}

void eventList::removeNode(event * thisEvent, bool deleteEvent) 
{ 
	if(listHead) 
		listHead = listHead->removeNode(thisEvent, deleteEvent); 
}

double eventList::time() 
{ 
	double t = mainList == NULL ? curTime : mainList->time(); 
//	printf("time requested: %f\n", t);
	
	return t;	
}
