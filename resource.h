// Matthew Applin
// resource
#ifndef __RESOURCE__
#define __RESOURCE__
#include "resourceType.h"

class resource
{
public:
	resource(resourceType& info,const double& quantity);
	~resource();
	resourceType* getResource();
	double getAmount();
	void setAmount(const double& info);
private:
	resourceType* r_type;
	double amount;
};
#endif
