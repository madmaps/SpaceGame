//turnThrusterTypeClass
#ifndef __TURNTHRUSTERTYPE__
#define __TURNTHRUSTERTYPE__
class turnThrusterType
{
public:
	char* name;
	int thrusterClass;
	int price;
	double yawRateOfTurn;
	double pitchRateOfTurn;
	double rollRateOfTurn;
	double responseTime;
	double energyDraw;
};
#endif
