// Matthew Applin
// galaxy class
#ifndef __GALAXY__
#define __GALAXY__
#include <vector>
#include "planet.h"
class galaxy
{
public:
	galaxy(int gWidth,int gHeight,int gDepth, int gSectorSize,int gNumberOfPlanets,float gPercentPopulated,float gPercentResources,int gMinDistBetwnPlnts);
	~galaxy();
	int getWidth();
	int getHeight();
	int getDepth();
	int getSectorSize();
	int getNumberOfPlanets();
	std::vector<planet*> t_planets;
private:
	int width;
	int height;
	int depth;
	int sectorSize;
	int numberOfPlanets;
	float percentPopulated;
	float percentResources;
	int minDistBetwnPlnts;
};

#endif





