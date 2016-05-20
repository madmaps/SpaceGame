// Matthew Applin
// energyDistributer class

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


