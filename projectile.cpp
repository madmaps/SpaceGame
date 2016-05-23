#include "projectile.h"

void projectile::setDone()
{
	done=1;
}

double projectile::getDamage()
{
	return potentialDamage;
}

projectile::projectile()
{
	done=0;
	potentialDamage=0;
	Max_Range=0;
	Remaining_Range=0;
}

void projectile::setTime(const double& info)
{
	timeChange=info;
}

void projectile::setRange(const double& range)
{
	Max_Range=range;
}

void projectile::setDamage(const double& damage)
{
	potentialDamage=damage;
}

bool projectile::isDone()
{
	return done;
}

void projectile::update()
{
	if(!done)
	{
		Remaining_Range+=timeChange;
		double info[1]={timeChange};
		matrix elapsed(1,1,info);
		Speed=Speed+Orientation*Direction*Acceleration;
		PrevLocation=Location;
		Location=Location+(Speed*elapsed);
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
		if(Remaining_Range>=Max_Range)
		{
			done=1;
		}
	}
}
projectile::~projectile(){}
