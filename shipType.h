// shipType class
#ifndef __SHIPTYPE__
#define __SHIPTYPE__

class shipType
{
public:
	char* name;
	int shipClass;
	int engineCapability;
	int weaponCapablity;
	int turnThrusterCapability;
	int shieldCapability;
	int energyCapability;
	int solarRechargeCapability;
	int numberOfEngineMounts;
	int numberOfGunMounts;
	int numberOfShields;
	int passengerQuarterSize;
	int cargoSize;
	int hullStrength;
	int price;
	double shipMass;
	int shipRadius;
	int model;
	int numberOfTextures;
	unsigned int* textures;
	std::vector<matrix> gunMountLocation;
	std::vector<matrix> gunMountUpDirection;
};

#endif
