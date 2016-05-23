// gun class
#ifndef __GUN__
#define __GUN__
#include "projectile.h"

class gun
{
public:
	gun(gunType& info);
	~gun();
	void update(const double& elapsedTime);
	void disable();
	void enable();
	bool fire(projectile& proj);
	bool isItEnabled();
	matrix getLocation();
	double getSpeed();
	double getEnergyDraw();
private:
	bool isEnabled;
	gunType* g_type;
	double timeUntilNextFire;
};

#endif


