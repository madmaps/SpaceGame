// Matthew Applin
// galaxy class

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






