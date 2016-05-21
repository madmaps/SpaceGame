// shield class
#ifndef __SHIELD__
#define __SHIELD__
#include "shieldType.h"

class shield
{
public:
	shield(shieldType& info);
	~shield();
	void recieveDamage(const double& damage);
	void lowerShields();
	void raiseShields();
	void update(const double& elapsedTime);
	double getStatus();
	double getPowerDraw();
	bool areShieldsUp();
	void noEnergy();
private:
	shieldType* s_type;
	double strength;
	double restoreElapsed;
	bool shieldsDisabled;
	bool shieldsDown;
};

#endif
