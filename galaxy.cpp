#include "galaxy.h"

galaxy::galaxy(int gWidth,int gHeight,int gDepth, int gSectorSize,int gNumberOfPlanets,float gPercentPopulated,float gPercentResources,int gMinDistBetwnPlnts)
{
	width=gWidth;
	height=gHeight;
	depth=gDepth;
	sectorSize=gSectorSize;
	numberOfPlanets=gNumberOfPlanets;
	percentPopulated=gPercentPopulated;
	percentResources=gPercentResources;
	minDistBetwnPlnts=gMinDistBetwnPlnts;
}

galaxy::~galaxy()
{}

int galaxy::getWidth()
{
	return width;
}

int galaxy::getDepth()
{
	return depth;
}

int galaxy::getHeight()
{
	return height;
}

int galaxy::getSectorSize()
{
	return sectorSize;
}

int galaxy::getNumberOfPlanets()
{
	return numberOfPlanets;
}

