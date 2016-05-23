#include "thruster.h"

turnThruster::turnThruster(turnThrusterType& info):yawDesiredPercentage(0),yawCurrentPercentage(0),pitchDesiredPercentage(0),pitchCurrentPercentage(0),rollDesiredPercentage(0),rollCurrentPercentage(0)
{
	t_thruster=&info;
}

void turnThruster::turn(RotationType r_type,const double& percentage)
{
	switch(r_type)
	{
	case YAW:
		yawDesiredPercentage=percentage;
		break;
	case PITCH:
		pitchDesiredPercentage=percentage;
		break;
	case ROLL:
		rollDesiredPercentage=percentage;
		break;
	default:
		break;
	}
}

void turnThruster::update(const double& timeLapse)
{
	
		yawCurrentPercentage=yawCurrentPercentage+(timeLapse*((t_thruster->yawRateOfTurn*yawDesiredPercentage)-yawCurrentPercentage)/t_thruster->responseTime);
		pitchCurrentPercentage=pitchCurrentPercentage+(timeLapse*((t_thruster->pitchRateOfTurn*pitchDesiredPercentage)-pitchCurrentPercentage)/t_thruster->responseTime);
		rollCurrentPercentage=rollCurrentPercentage+(timeLapse*((t_thruster->rollRateOfTurn*rollDesiredPercentage)-rollCurrentPercentage)/t_thruster->responseTime);
	
}

double turnThruster::getEnergyDraw()
{
	return t_thruster->energyDraw;
}
