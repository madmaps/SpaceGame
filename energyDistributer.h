// Matthew Applin
// energyDistributer class
#ifndef __ENERGYDISTRIBUTER__
#define __ENERGYDISTRIBUTER__
#include "energyDistributerType.h"

class energyDistributer
{
public:
	//void update();
	energyDistributer(energyDistributerType& info);
	~energyDistributer();
	double checkEnergyLevel();
	bool removeEnergy(const double& info);
	void addEnergy(const double& info);
	int getMaxEnergy();
private:
	energyDistributerType* e_type;
	double energy;
};

#endif

