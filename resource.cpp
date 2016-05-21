#include "resource.h"

resource::resource(resourceType& info,const double& quantity)
{
	r_type=&info;
	amount=quantity;
}

resource::~resource()
{}

resourceType* resource::getResource()
{
	return r_type;
}

double resource::getAmount()
{
	return amount;
}

void resource::setAmount(const double& info)
{
	amount=info;
}
