// Matthew Applin
// resourceSlot class
#ifndef __RESOURCESLOT__
#define __RESOURCESLOT__
#include "resourceType.h"
#include "resource.h"

class resourceSlot
{
public:
	resourceSlot(resourceType& info,const double& quantity);
	~resourceSlot();
	void increaseProduction();
	void decreaseProduction();
	void update(const double& elapsedTime);
	double getProductionRate();
	resource* getResource();
private:
	double currentProductionRate;
	resource currentResource;
};

#endif

