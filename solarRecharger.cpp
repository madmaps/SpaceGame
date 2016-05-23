#include "solarRecharger.h"

solarRecharger::solarRecharger(solarRechargerType& info)
{
	s_type=&info;
}

double solarRecharger::getCharge()
{
	return s_type->rechargeRate;
}

solarRecharger::~solarRecharger()
{}
