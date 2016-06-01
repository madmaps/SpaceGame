// engine class
#ifndef __ENGINE__
#define __ENGINE__
#include "engineType.h"
#include "matrix.h"

class engine
{
public:
	engine(engineType& type):e_type(&type),currentPercentage(1,1),desiredPercentage(0){}
	~engine(){}
	void Accelerate(const double& percentage);
	void update(const double& elapsedTime);
	matrix getCurrentPercentage();
	double getEnergyDraw();
private:
	engineType* e_type;
	matrix currentPercentage;
	double desiredPercentage;

};

#endif

