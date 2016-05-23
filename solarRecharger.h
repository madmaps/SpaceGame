// Matthew Applin
// solarRechargerClass
#ifndef __SOLARRECHARGER__
#define __SOLARRECHARGER__
#include "solarRechargerType.h"

class solarRecharger
{
public:
	solarRecharger(solarRechargerType& info);
	double getCharge();
	~solarRecharger();
private:
	solarRechargerType* s_type;
};
#endif
