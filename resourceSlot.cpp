#include "resourceSlot.h"

resourceSlot::resourceSlot(resourceType& info,const double& quantity):currentResource(info,quantity)
{
	currentProductionRate=info.standardProductionRate;
}

resourceSlot::~resourceSlot()
{}



resource* resourceSlot::getResource()
{
	return &currentResource;
}

double resourceSlot::getProductionRate()
{
	return currentProductionRate;
}

