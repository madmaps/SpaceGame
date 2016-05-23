#ifndef __SHIP__
#define __SHIP__
#include "gunType.h"
#include "shieldType.h"
#include "engineType.h"
#include "turnThrusterType.h"
#include "energyDistributerType.h"
#include "energyDistributer.h"
#include "solarRecharger.h"
#include "gun.h"
#include "shield.h"
#include "engine.h"
#include "thruster.h"
#include "shipType.h"


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

#endif

	



