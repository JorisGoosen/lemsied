#include "lemming.h"
#include <algorithm>
#include "welt.h"


lemming::lemming(welt * umwelt) 
	: 	currentState(wacht), 
		nextState(wacht), 
		currentFrame(0), 
//		tileX(2), 
//		tileY(2),
		meinWelt(umwelt)
{
	tileX = rand()%20;
	tileY = rand()%20;
	myEvents = new eventList(meinWelt->mainEventList());
	fillTransitions();
	loadAnim();
	
	beweeg(RechtsBoven);	
}

transitieMap lemming::visualTransitions = transitieMap();

void addReverso(transitieMap & trans, lemVisualState keyA, lemVisualState keyB, lemAnim anim)
{
	lemAnim copy;
	
	for(int i = anim.size() - 1; i>= 0; i--)
		copy.push_back(anim[i]);
	
	trans[keyA][keyB] = anim;
	trans[keyB][keyA] = copy;
}

void combineAndAddReverso(transitieMap & trans, lemVisualState keyA, lemVisualState keyB, lemVisualState keyC)
{
	lemAnim A = trans[keyA][keyB];
	lemAnim B = trans[keyB][keyC];
	
	for(int i=0; i<B.size(); i++)
		A.push_back(B[i]);
		
	addReverso(trans, keyA, keyC, A);
}

void lemming::fillTransitions()
{
	if(visualTransitions.size() > 0)
		return;
		
	size_t wachtO[] = { 0, 1, 2};

	addReverso(visualTransitions, wacht, stilO, lemAnim(wachtO, wachtO + 3));
	
	size_t oRo[]  = { 2,  3,  4};
	size_t roRb[] = { 4,  5,  6};
	size_t rbB[]  = { 6,  7,  8,  9};
	size_t bLb[]  = { 9, 10, 11, 12};
	size_t lbLo[] = {12, 13, 14};
	size_t loO[]  = {14, 15,  2};
	
	addReverso(visualTransitions, stilO,  stilRO, lemAnim(oRo,  oRo  + 3));
	addReverso(visualTransitions, stilRO, stilRB, lemAnim(roRb, roRb + 3));
	addReverso(visualTransitions, stilRB, stilB,  lemAnim(rbB,  rbB  + 4));
	addReverso(visualTransitions, stilB,  stilLB, lemAnim(bLb,  bLb  + 4));
	addReverso(visualTransitions, stilLB, stilLO, lemAnim(lbLo, lbLo + 3));
	addReverso(visualTransitions, stilLO, stilO,  lemAnim(loO,  loO  + 3));
	
	combineAndAddReverso(visualTransitions, stilO,	stilRO, stilRB);
	combineAndAddReverso(visualTransitions, stilRO, stilRB, stilB);
	combineAndAddReverso(visualTransitions, stilRB, stilB,  stilLB);
	combineAndAddReverso(visualTransitions, stilB,  stilLB, stilLO);
	combineAndAddReverso(visualTransitions, stilLB, stilLO, stilO);
	combineAndAddReverso(visualTransitions, stilLO, stilO,  stilB);
	
	combineAndAddReverso(visualTransitions, stilO,  stilRB, stilB);
	combineAndAddReverso(visualTransitions, stilRO, stilB, stilLB);
	combineAndAddReverso(visualTransitions, stilRB, stilLB, stilLO);
	
	size_t loopO[]  = {2,  16, 17, 18, 17, 16, 2,  21, 20, 19, 20, 21, 2};
	size_t loopB[]  = {9,  22, 23, 24, 23, 22, 9,  27, 26, 25 ,26, 27, 9};
	size_t loopRB[] = {6,  48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 6};
	size_t loopRO[] = {4,  28, 29, 30, 31, 32, 33, 34, 35, 37, 4};
	size_t loopLO[] = {14, 47, 46, 45 ,44, 43, 42, 41, 40, 39, 38, 14};
	size_t loopLB[] = {12, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 12};
	
	visualTransitions[stilO ][stilO ] = lemAnim(loopO,  loopO  + 13);
	visualTransitions[stilB ][stilB ] = lemAnim(loopB,  loopB  + 13);
	visualTransitions[stilRB][stilRB] = lemAnim(loopRB, loopRB + 12);
	visualTransitions[stilRO][stilRO] = lemAnim(loopRO, loopRO + 11);
	visualTransitions[stilLO][stilLO] = lemAnim(loopLO, loopLO + 12);
	visualTransitions[stilLB][stilLB] = lemAnim(loopLB, loopLB + 12);	
}

int lemming::getWorldXOri() { return welt::xOri(tileX); }
int lemming::getWorldYOri() { return welt::yOri(tileX, tileY); }

void lemming::setCurrentFrame()
{
	if(currentAnim.size() == 0)
		currentFrame = 0;
	else
		currentFrame = currentAnim[currentAnimStep % currentAnim.size()];
}

void lemming::loadAnim()
{
	//printf("there are %d vistransmaps and the requested %d one has %d\n", visualTransitions.size(), currentState, visualTransitions[currentState].size());
	currentAnim = visualTransitions[currentState][nextState];
	//printf("loadad anim for lemming and its length= %d\n", currentAnim.size());
	currentAnimStep = 0;
	setCurrentFrame();
}

void lemming::stepFrame()
{
	currentAnimStep++;
	
	/*if(currentAnimStep >= currentAnim.size())
	{
		lemVisualState st = nextState;
		nextState = currentState;
		currentState = st;
		
		loadAnim();
	}*/

	setCurrentFrame();
	
}

void lemming::drawYourself()
{
	double relTime = myEvents->time() - moveTimeBegin;
	
	if(moveTimeDuration > 0 && relTime > 0 && relTime <= moveTimeDuration)
	{
		double ratio = relTime / moveTimeDuration;
		meinWelt->drawLemmingFrame(currentFrame,
			mix(oriActualX, newActualX, ratio),
			mix(oriActualY, newActualY, ratio));
	}
	else
		meinWelt->drawLemmingFrameInTile(currentFrame, tileX, tileY);
}

void lemming::stateChanged(lemVisualState newState)
{
	currentState 	= nextState;
	nextState 		= newState;
	
	loadAnim();
}

void lemming::posChanged(int newTileX, int newTileY)
{
	tileX = newTileX;
	tileY = newTileY;
	
	
	
	moveTimeBegin = 0;
	moveTimeDuration = 0;
}

bool lemming::beweeg(lemDir richting)
{
	printf("beweeg!\n");
	lemVisualState naDraaiVis;
	int newX = tileX, newY = tileY;
	bool downStag = welt::xStaggeredDown(tileX);
	
	switch(richting)
	{
	default:
	case Onder: 		naDraaiVis = stilO;								newY++;	break;
	case RechtsOnder: 	naDraaiVis = stilRO;	newX++;	if( downStag)	newY++;	break;
	case RechtsBoven: 	naDraaiVis = stilRB;	newX++;	if(!downStag)	newY--;	break;
	case Boven: 		naDraaiVis = stilB;								newY--;	break;
	case LinksBoven: 	naDraaiVis = stilLB;	newX--;	if(!downStag)	newY--;	break;
	case LinksOnder: 	naDraaiVis = stilLO;	newX--;	if( downStag)	newY++;	break;
	}
	
	newX = welt::validateX(newX);
	newY = welt::validateY(newY);
	
	bool mustTurn = currentState != naDraaiVis;
	
	double beginTijd = myEvents->time() + EPSILON;
	printf("lemming thinks time=%f\n", beginTijd);
	
	const double 	draaiTijd = 0.5, 
					loopTijd  = 1.0;

	if(mustTurn)
	{
		myEvents->addEvent(new stateChangedEvent(beginTijd, this, naDraaiVis));

		int frames = getFrameCountAnim(currentState, naDraaiVis);
		for(double t = 0; t < draaiTijd; t += draaiTijd / frames)
			myEvents->addEvent(new stepFrameEvent(beginTijd + t, this));
		
		beginTijd += draaiTijd;
	}
	
	myEvents->addEvent(new stateChangedEvent(beginTijd, this, naDraaiVis));
	
	int frames = 5 * getFrameCountAnim(naDraaiVis, naDraaiVis);
	for(double t = 0; t <= loopTijd; t += loopTijd / frames)
		myEvents->addEvent(new stepFrameEvent(beginTijd + t, this));
	
	moveTimeBegin 		= beginTijd;
	moveTimeDuration 	= loopTijd;
	oriActualX			= welt::xLem(tileX);
	oriActualY			= welt::yLem(tileX, tileY);
	newActualX			= welt::xLem(newX);
	newActualY			= welt::yLem(newX, newY);
	
	myEvents->addEvent(new positionChangedEvent(beginTijd + loopTijd, this, newX, newY));	
	myEvents->addEvent(new considerEvent(beginTijd + loopTijd + 0.1, this));	
}
