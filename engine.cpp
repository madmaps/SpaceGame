#include "engine.h"

engine::engine(engineType& type):e_type(&type),currentPercentage(1,1)
{
	desiredPercentage=0;
}

void engine::update(const double& elapsedTime)
{
	double temp=currentPercentage.getLocation(0);
	currentPercentage.setLocation(0,temp+(elapsedTime*((e_type->accerationRate*desiredPercentage)-temp)/e_type->responseTime));
}

void engine::Accelerate(const double& percentage)
{
	desiredPercentage=percentage;
}

matrix engine::getCurrentPercentage()
{
	return currentPercentage;
}

double engine::getEnergyDraw()
{
	return e_type->energyDraw;
}

