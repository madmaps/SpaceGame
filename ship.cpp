#include "ship.h"
#include "math.h"

ship::ship():s_ship(0),numberOfShields(0),numberOfGuns(0),numberOfEngines(0),
			 amountInCargo(0),numberOfTypesInCargo(0),passengers(0),hull(0),
			 docked(0),s_distributer(0),s_recharger(0),s_thrusters(0),shipSpeed(0),maxSpeed(0),timeChange(0)
{}

ship::ship(shipType& info):s_ship(&info),numberOfShields(0),numberOfGuns(0),numberOfEngines(0),
			 amountInCargo(0),numberOfTypesInCargo(0),passengers(0),hull(0),
			 docked(0),s_distributer(0),s_recharger(0),s_thrusters(0),shipSpeed(0),maxSpeed(0),timeChange(0)
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
	if(s_thrusters!=0)
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
	if(s_recharger!=0 && s_distributer!=0)
	{
		if(s_recharger->getCharge()*timeChange+s_distributer->checkEnergyLevel()<s_distributer->getMaxEnergy())
		{
			s_distributer->addEnergy(s_recharger->getCharge()*timeChange);
		}
	}
	if(s_distributer!=0)
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
	if(s_distributer!=0)
	{
		if(s_thrusters!=0 && s_distributer->removeEnergy(s_thrusters->getEnergyDraw()*fabs(percentage)*timeChange*10))
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
	if(s_distributer!=0)
	{
		int i=0;
		while(i<numberOfEngines)
		{
			if(s_distributer->removeEnergy(s_engines[i].getEnergyDraw()*fabs(percentage)*timeChange*10))
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
	if(s_distributer!=0)
	{
		projectile temp;
		int i=0;
		while(i<numberOfGuns)
		{
			if(s_guns[i].fire(temp) && s_distributer->removeEnergy(s_guns[i].getEnergyDraw()))
			{
				//matrix tempMatrix0 =Orientation*s_guns[i].getLocation();
				//temp.setLocation(tempMatrix0);
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
	if(s_distributer!=0)
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
	if(s_distributer!=0)
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
	if(s_distributer!=0)
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
	s_thrusters=0;
}

void ship::removeSolarRecharger()
{
	delete s_recharger;
	s_recharger=0;
}

void ship::removeEnergyDistributer()
{
	delete s_distributer;
	s_distributer=0;
}
