// gun class

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
