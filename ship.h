#ifndef __SHIP__
#define __SHIP__
#include "gunType.h"
#include "shieldType.h"
#include "engineType.h"
#include "turnThrusterType.h"
class energyDistributerType
{
public:
	energyDistributerType();
	~energyDistributerType();
	char* name;
	int price;
	int energyDistributerClass;
	int capacity;
};

energyDistributerType::energyDistributerType()
{}

energyDistributerType::~energyDistributerType()
{}

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

energyDistributer::energyDistributer(energyDistributerType& info)
{
	e_type=&info;
	energy=info.capacity;
}

energyDistributer::~energyDistributer()
{}

double energyDistributer::checkEnergyLevel()
{
	return energy;
}

bool energyDistributer::removeEnergy(const double& info)
{
	if(energy-info<0)
	{
		return 0;
	}
	energy-=info;
	return 1;
}

void energyDistributer::addEnergy(const double& info)
{
	energy+=info;
}

int energyDistributer::getMaxEnergy()
{
	return e_type->capacity;
}




class solarRechargerType
{
public:
	char* name;
	int solarRechargerClass;
	int price;
	double rechargeRate;
};

class solarRecharger
{
public:
	solarRecharger(solarRechargerType& info);
	double getCharge();
	~solarRecharger();
private:
	solarRechargerType* s_type;
};

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

bool gun::isItEnabled()
{
	return isEnabled;
}

gun::gun(gunType& info)
{
	g_type=&info;
	isEnabled=1;
	timeUntilNextFire=0;
}

void gun::update(const double& elapsedTime)
{

	if(timeUntilNextFire>0)
	{
		timeUntilNextFire-=elapsedTime;
	}
}

bool gun::fire(projectile& proj)
{
	if(isEnabled)
	{
		if(timeUntilNextFire<=0)
		{
			
			timeUntilNextFire=g_type->rateOfFire;
			proj.setDamage(g_type->damagePotential);
			proj.setRange(g_type->projectileRange/g_type->projectileSpeed);
			return true;
			
		}
	}
	return false;
			

}
matrix gun::getLocation()
{
	return g_type->location;
}

double gun::getSpeed()
{
	return g_type->projectileSpeed;
}

double gun::getEnergyDraw()
{
	return g_type->energyDraw;
}

gun::~gun(){}


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


class engine
{
public:
	engine(engineType& type):currentPercentage(1,1),desiredPercentage(0),e_type(&type){}
	~engine(){}
	void Accelerate(const double& percentage);
	void update(const double& elapsedTime);
	matrix getCurrentPercentage();
	double getEnergyDraw();
private:
	engineType* e_type;
	matrix currentPercentage;
	double desiredPercentage;

};

void engine::update(const double& elapsedTime)
{
	double temp=currentPercentage.getLocation(0);
	currentPercentage.setLocation(0,temp+(elapsedTime*((e_type->accerationRate*desiredPercentage)-temp)/e_type->responseTime));
}

void engine::Accelerate(const double& percentage)
{
	desiredPercentage=percentage;
}

matrix engine::getCurrentPercentage()
{
	return currentPercentage;
}

double engine::getEnergyDraw()
{
	return e_type->energyDraw;
}



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

class ship : public s_object
{
public:
	ship();
	ship(shipType& info);
	~ship();
	void recieveDamage(const double& amount);
	int hasFired(std::vector<projectile>& info);
	void update();
	void setTime(const double& info);
	void setShipSpeed(const double& spd);
	void setHullStrength(const double& info);
	double getHullStrength();

	//controls
	void turn(RotationType r_type,const double& percentage);
	void Accelerate(const double& percentage);
	void fire();
	//void loadCargo(const resource& rec,const int amount);
	//void unloadCargo(const resource&,const int amount);
	void raiseShields(const int& info);
	void lowerShields(const int& info);
	void loadPassengers(const int& amount);
	void unloadPassengers(const int& amount);
	void selfDestruct();
	void dock();
	void undock();
	
	//Adding/removing ship items
	void addShipType(shipType& info);
	void removeShipType();
	void addGun(gunType& gtype);
	void removeGun(const int& slot);
	void addShield(shieldType& stype);
	void removeShield(const int& slot);
	void addEngine(engineType& etype);
	void removeEngine(const int& slot);
	void addTurnThruster(turnThrusterType& ttype);
	void removeTurnThruster();
	void addEnergyDistributer(energyDistributerType& etype);
	void removeEnergyDistributer();
	void addSolarRecharger(solarRechargerType& stype);
	void removeSolarRecharger();
	double getEnergyLevel();
	double getEnergyCapability();
	shipType* getShipType();
	//Getting ship Information

private:
	shipType* s_ship;
	int numberOfShields;
	int numberOfGuns;
	int numberOfEngines;
	int numberOfProjectiles;
	std::vector<shield> s_shields;
	std::vector<gun> s_guns;
	std::vector<engine> s_engines;
	std::vector<projectile> s_proj;
	//double energy;
	int amountInCargo;
	int numberOfTypesInCargo;
	//std::vector<resource> s_cargo;
	int passengers;
	double hull;
	bool docked;
	energyDistributer* s_distributer;
	solarRecharger* s_recharger;
	turnThruster* s_thrusters;
	double shipSpeed;
	double maxSpeed;
	double timeChange;
	
};

	




ship::ship():numberOfShields(0),numberOfGuns(0),numberOfEngines(0),
			 amountInCargo(0),numberOfTypesInCargo(0),passengers(0),hull(0),
			 docked(0),s_distributer(NULL),s_recharger(NULL),s_thrusters(NULL),s_ship(NULL),maxSpeed(0),timeChange(0),shipSpeed(0)
{}

ship::ship(shipType& info):numberOfShields(0),numberOfGuns(0),numberOfEngines(0),
			 amountInCargo(0),numberOfTypesInCargo(0),passengers(0),hull(0),
			 docked(0),s_distributer(NULL),s_recharger(NULL),s_thrusters(NULL),s_ship(&info),maxSpeed(0),timeChange(0)
{}

void ship::addShipType(shipType& info)
{
	s_ship=&info;
	hull=s_ship->hullStrength;
}


ship::~ship()
{}

shipType* ship::getShipType()
{
	return s_ship;
}

double ship::getHullStrength()
{
	return hull;
}

void ship::setHullStrength(const double& info)
{
	hull=info;
}

void ship::setShipSpeed(const double& info)
{
	shipSpeed=info;
}

void ship::update()
{
	matrix tempMatrix(1,1);
	double temp[1]={0};
	double energyTemp=0;
	int i=0;
	
	while(i<numberOfEngines)
	{
		s_engines[i].update(timeChange);
		temp[0]=temp[0]+s_engines[i].getCurrentPercentage().getLocation(0)*timeChange*(1000/s_ship->shipMass);
		i++;
	}
	if((shipSpeed<maxSpeed && temp[0]>0) || (shipSpeed>-maxSpeed && temp[0]<0))
	{
		shipSpeed=shipSpeed+temp[0];
	}
	tempMatrix.setLocation(0,shipSpeed*timeChange);
	Speed=Orientation*Direction*tempMatrix;
	PrevLocation=Location;
	Location=Location+Speed;
	if(Location.getLocation(0)>sectorSize)
	{
		sectorX++;
		Location.setLocation(0,Location.getLocation(0)-sectorSize);
		if(sectorX>maxX-1)
		{
			sectorX=0;
		}
	}
	if(Location.getLocation(0)<0)
	{
		Location.setLocation(0,Location.getLocation(0)+sectorSize);
		sectorX--;
		if(sectorX<0)
		{
			sectorX=maxX-1;
		}
	}
	if(Location.getLocation(1)>sectorSize)
	{
		Location.setLocation(1,Location.getLocation(1)-sectorSize);
		sectorY++;
		if(sectorY>maxY-1)
		{
			sectorY=0;
		}
	}
	if(Location.getLocation(1)<0)
	{
		Location.setLocation(1,Location.getLocation(1)+sectorSize);
		sectorY--;
		if(sectorY<0)
		{
			sectorY=maxY-1;
		}
	}
	if(Location.getLocation(2)>sectorSize)
	{
		Location.setLocation(2,Location.getLocation(2)-sectorSize);
		sectorZ++;
		if(sectorZ>maxZ-1)
		{
			sectorZ=0;
		}
	}
	if(Location.getLocation(2)<0)
	{
		Location.setLocation(2,Location.getLocation(2)+sectorSize);
		sectorZ--;
		if(sectorZ<0)
		{
			sectorZ=maxZ-1;
		}
	}
	if(s_thrusters!=NULL)
	{
		s_thrusters->update(timeChange);
		Rotate(YAW,s_thrusters->getYAW()*timeChange*(1000/s_ship->shipMass));
		Rotate(PITCH,s_thrusters->getPITCH()*timeChange*(1000/s_ship->shipMass));
		Rotate(ROLL,s_thrusters->getROLL()*timeChange*(1000/s_ship->shipMass));

	}
	
	i=0;
	
	while(i<numberOfGuns)
	{
		s_guns[i].update(timeChange);
		i++;
	}
	if(s_recharger!=NULL && s_distributer!=NULL)
	{
		if(s_recharger->getCharge()*timeChange+s_distributer->checkEnergyLevel()<s_distributer->getMaxEnergy())
		{
			s_distributer->addEnergy(s_recharger->getCharge()*timeChange);
		}
	}
	if(s_distributer!=NULL)
	{
		i=0;
		while(i<numberOfShields)
		{
			s_shields[i].update(timeChange);
			if(s_shields[i].areShieldsUp())
			{
				if(!s_distributer->removeEnergy(s_shields[i].getPowerDraw()*timeChange))
				{
					s_shields[i].noEnergy();
				}
			}
			i++;
		}
	}


}

void ship::turn(RotationType r_type,const double& percentage)
{
	if(s_distributer!=NULL)
	{
		if(s_thrusters!=NULL && s_distributer->removeEnergy(s_thrusters->getEnergyDraw()*abs(percentage)*timeChange*10))
		{
			s_thrusters->turn(r_type,percentage);
		}
	}

}

void ship::addTurnThruster(turnThrusterType& info)
{
	s_thrusters=new turnThruster(info);
}

void ship::addEngine(engineType& info)
{

	if(numberOfEngines<s_ship->numberOfEngineMounts)
	{
		engine tempEngine(info);
		
		s_engines.push_back(tempEngine);
		if(info.topSpeed>maxSpeed)
		{
			maxSpeed=info.topSpeed;
		}
		numberOfEngines++;
	}

}

void ship::Accelerate(const double& percentage)
{
	if(s_distributer!=NULL)
	{
		int i=0;
		while(i<numberOfEngines)
		{
			if(s_distributer->removeEnergy(s_engines[i].getEnergyDraw()*abs(percentage)*timeChange*10))
			{
				s_engines[i].Accelerate(percentage);
			}
			i++;
		}
	}
}

void ship::addGun(gunType& gtype)
{
	if(numberOfGuns<s_ship->numberOfGunMounts)
	{
		gun tempGun(gtype);
		
		s_guns.push_back(tempGun);
		
		numberOfGuns++;
	}
}

void ship::fire()
{
	if(s_distributer!=NULL)
	{
		projectile temp;
		int i=0;
		while(i<numberOfGuns)
		{
			if(s_guns[i].fire(temp) && s_distributer->removeEnergy(s_guns[i].getEnergyDraw()))
			{
				temp.setLocation(Location+(Orientation*s_ship->gunMountLocation[i])+(Orientation*s_guns[i].getLocation()));
				temp.setSpeedDirection(Orientation,s_guns[i].getSpeed()+shipSpeed);
				temp.setSector(sectorX,sectorY,sectorZ);
				temp.setMaxSectors(maxX,maxY,maxZ,sectorSize);
				s_proj.push_back(temp);
				numberOfProjectiles++;
			}
			i++;
		}
	}
		
}

int ship::hasFired(std::vector<projectile>& proj)
{
	int i=0;
	while(i<numberOfProjectiles)
	{
		proj.push_back(s_proj[i]);
		i++;
	}
	s_proj.clear();
	numberOfProjectiles=0;
	return i;
}

void ship::addEnergyDistributer(energyDistributerType& info)
{
	s_distributer=new energyDistributer(info);
}

void ship::addSolarRecharger(solarRechargerType& info)
{
	s_recharger=new solarRecharger(info);
}

double ship::getEnergyLevel()
{
	if(s_distributer!=NULL)
	{
		return s_distributer->checkEnergyLevel();
	}
	else
	{
		return 0;
	}
}

double ship::getEnergyCapability()
{
	if(s_distributer!=NULL)
	{
		return s_distributer->getMaxEnergy();
	}
	else
	{
		return 0;
	}
}

void ship::setTime(const double& info)
{
	timeChange=info;
}

void ship::addShield(shieldType& info)
{
	if(numberOfShields<s_ship->numberOfShields)
	{
		shield tempShield(info);
		
		s_shields.push_back(tempShield);
		
		numberOfShields++;
	}

}

void ship::recieveDamage(const double& info)
{
	double amount=info;
	if(s_distributer!=NULL)
	{
		int i=0;
		while(i<numberOfShields)
		{
			if(s_shields[i].areShieldsUp())
			{
				if(s_shields[i].getStatus()<amount)
				{
					amount-=s_shields[i].getStatus();
					s_shields[i].recieveDamage(s_shields[i].getStatus());
				}
				else
				{
					s_shields[i].recieveDamage(amount);
					amount=0;
				}
			}
			i++;
		}
	}
	hull-=amount;

			
}

void ship::raiseShields(const int& info)
{
	if(info>0 && info<=numberOfShields)
	{
		s_shields[info-1].lowerShields();
	}
}

void ship::lowerShields(const int& info)
{
	if(info>0 && info<=numberOfShields)
	{
		s_shields[info-1].raiseShields();
	}
}

void ship::removeGun(const int& info)
{
	if(info>0 && info<=numberOfGuns)
	{
		int i=info-1;
		while(i<numberOfGuns-2)
		{
			s_guns[i]=s_guns[i+1];
			i++;
		}
		numberOfGuns--;
		s_guns.pop_back();
	}
}

void ship::removeShield(const int& info)
{
	if(info>0 && info<=numberOfShields)
	{
		int i=info-1;
		while(i<numberOfShields-2)
		{
			s_shields[i]=s_shields[i+1];
			i++;
		}
		numberOfShields--;
		s_shields.pop_back();
	}
}


void ship::removeEngine(const int& info)
{
	if(info>0 && info<=numberOfEngines)
	{
		int i=info-1;
		while(i<numberOfEngines-2)
		{
			s_engines[i]=s_engines[i+1];
			i++;
		}
		numberOfEngines--;
		s_engines.pop_back();
	}
}

void ship::removeTurnThruster()
{
	delete s_thrusters;
	s_thrusters=NULL;
}

void ship::removeSolarRecharger()
{
	delete s_recharger;
	s_recharger=NULL;
}

void ship::removeEnergyDistributer()
{
	delete s_distributer;
	s_distributer=NULL;
}
