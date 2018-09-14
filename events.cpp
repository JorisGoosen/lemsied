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

void eventList::addEvent(event * newEvent)
{
	eventListNode * node = new eventListNode(this, newEvent);
	
	listHead = listHead == NULL ? node : listHead->insertNode(node);
}

void eventList::increaseTimeBy(double timeStep)
{
	double endTime = curTime + timeStep;
	
	while(listHead != NULL && listHead->time() < endTime)
	{
		curTime = listHead->time();
		listHead->theEvent->activate();
		
		if(listHead->next == NULL)
		{
			delete listHead;
			listHead = NULL;
		}
		else
		{
			listHead = listHead->next;
			listHead->destroyPrevious();
		}
	}
	
	curTime = endTime;
}

void eventList::removeNode(event * thisEvent, bool deleteEvent = false) 
{ 
	if(listHead) 
		listHead = listHead->removeNode(thisEvent, deleteEvent); 
}
