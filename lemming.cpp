#include "lemming.h"
#include <algorithm>
#include "welt.h"

std::map<lemVisualState, std::map<lemVisualState, lemAnim> > visualTransitions;

void addReverso(std::map<lemVisualState, std::map<lemVisualState, lemAnim> > & trans, lemVisualState keyA, lemVisualState keyB, lemAnim anim)
{
	lemAnim copy; // = trans[keyA][keyB];
	
	for(size_t i = anim.size() - 1; i>= 0; i--)
		copy.push_back(anim[i]);
	
	trans[keyA][keyB] = anim;
	trans[keyB][keyA] = copy;
}

void fillTransitions()
{
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
	
	size_t loopO[]  = {2,  16, 17, 18, 17, 16, 2,  21, 20, 16, 20, 21, 2};
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
