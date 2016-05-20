// Matthew Applin
// turnThruster class
#ifndef __TURNTHRUSTER__
#define __TURNTHRUSTER__
#include "turnThrusterType.h"
#include "s_object.h"

class turnThruster
{
public:
	turnThruster(turnThrusterType& info);
	~turnThruster(){}
	void update(const double& timeLapse);
	void turn(RotationType r_type,const double& precentage);
	double getYAW(){return yawCurrentPercentage;}
	double getPITCH(){return pitchCurrentPercentage;}
	double getROLL(){return rollCurrentPercentage;}
	double getEnergyDraw();
private:
	turnThrusterType* t_thruster;
	double yawDesiredPercentage;
	double yawCurrentPercentage;
	double pitchDesiredPercentage;
	double pitchCurrentPercentage;
	double rollDesiredPercentage;
	double rollCurrentPercentage;
};

#endif
