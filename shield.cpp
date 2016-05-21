#include "shield.h"

shield::shield(shieldType& info)
{
	s_type=&info;
	strength=info.strength;
	restoreElapsed=0;
	shieldsDisabled=0;
	shieldsDown=0;
}

shield::~shield()
{}

void shield::recieveDamage(const double& damage)
{
	strength-=damage;
	if(strength<=0 && restoreElapsed==0)
	{
		shieldsDisabled=1;
		strength=0;
		restoreElapsed=s_type->restoreTime;
	}
}

void shield::lowerShields()
{
	shieldsDown=1;
}

void shield::raiseShields()
{
	shieldsDown=0;
}

void shield::update(const double& elapsedTime)
{
	if(shieldsDisabled)
	{
		restoreElapsed=restoreElapsed-elapsedTime;
		if(restoreElapsed<=0)
		{
			restoreElapsed=0;
			shieldsDisabled=0;
		}
	}
	else
	{
		if(strength<s_type->strength)
		{
			strength=strength+s_type->regeneratetionRate*elapsedTime;
			if(strength>s_type->strength)
			{
				strength=s_type->strength;
			}
		}
	}
}
		
double shield::getStatus()
{
	return strength;
}

double shield::getPowerDraw()
{
	return s_type->energyDraw;
}

bool shield::areShieldsUp()
{
	return !shieldsDown;
}

void shield::noEnergy()
{
	shieldsDisabled=1;
	strength=0;
	restoreElapsed=s_type->restoreTime;
}
