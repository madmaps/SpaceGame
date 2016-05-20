// Matthew APplin
// planet class

class planet : public s_object
{
public:
	planet();
	~planet();
	void update();
	void investInGovernment(const double& amount);
	void investInEducation(const double& amount);
	void investInAgriculture(const double& amount);
	void investInMining(const double& amount);
	void investInHealthCare(const double& amount);
	void investInMilitary(const double& amount);
	void investInManufacturing(const double& amount);

	void addResource(resourceType& info,const double& quantity);
	void removeResource(resourceType* info,double amount);
	double getTaxes();

	void setTime(const double& info);

private:

	std::vector<resourceSlot> resSlot;
	double population;
	double loyalty;
	double size;
	double shields;//Will be actual type;
	double guns;//Will be actual type;
	double happyness;
	double government;
	double education;
	double agriculture;
	double mining;
	double manufacturing;
	double healthCare;
	double military;

	double timeChange;


};

planet::planet()
{
	population=0;
	loyalty=0;
	size=0;
	shields=0;
	guns=0;
	happyness=0;
	government=0;
	education=0;
	agriculture=0;
	mining=0;
	manufacturing=0;
	healthCare=0;
	military=0;
}
planet::~planet()
{
}



void planet::setTime(const double& info)
{
	timeChange=info;
}


void planet::investInManufacturing(const double& amount)
{
	manufacturing=amount;
}

void planet::addResource(resourceType& info,const double& quantity)
{
	resourceSlot* tempResource= new resourceSlot(info,quantity);
	resSlot.push_back(*tempResource);
	double a=3;
}

void planet::update()
{
	int i=0;
	int j=0;
	int k=0;
	double tempReq;
	double actAmount=0;
	double actAmount2=0;
	double manPer,agrPer,minPer;
	while(i<resSlot.size())
	{
		if(resSlot[i].getResource()->getResource()->maxManufacturingLevel<=manufacturing)
		{
			manPer=1;
		}
		else
		{
			if(resSlot[i].getResource()->getResource()->minManufacturingLevel>=manufacturing)
			{
				manPer=0;}
			else
			{
				manPer=(manufacturing-resSlot[i].getResource()->getResource()->minManufacturingLevel)/(resSlot[i].getResource()->getResource()->maxManufacturingLevel-resSlot[i].getResource()->getResource()->minManufacturingLevel);
			}
		}
		if(resSlot[i].getResource()->getResource()->maxAgricultureLevel<=agriculture)
		{
			agrPer=1;
		}
		else
		{
			if(resSlot[i].getResource()->getResource()->minAgricultureLevel>=agriculture)
			{
				agrPer=0;
			}
			else
			{
				agrPer=(agriculture-resSlot[i].getResource()->getResource()->minAgricultureLevel)/(resSlot[i].getResource()->getResource()->maxAgricultureLevel-resSlot[i].getResource()->getResource()->minAgricultureLevel);
			}
		}
		if(resSlot[i].getResource()->getResource()->maxMiningLevel<=mining)
		{
			minPer=1;
		}
		else
		{
			if(resSlot[i].getResource()->getResource()->minMiningLevel>=mining)
			{
				minPer=0;
			}
			else
			{
				minPer=(mining-resSlot[i].getResource()->getResource()->minMiningLevel)/(resSlot[i].getResource()->getResource()->maxMiningLevel-resSlot[i].getResource()->getResource()->minMiningLevel);
			}
		}
		
		j=0;
		tempReq=1;
		actAmount=0;
		actAmount=0;
		while(j<resSlot[i].getResource()->getResource()->MaterialRequirement.size())
		{
			double tempMin=resSlot[i].getResource()->getResource()->minMaterial[j];
			double tempMax=resSlot[i].getResource()->getResource()->maxMaterial[j];
			k=0;
			while(k<resSlot.size())
			{
				if(resSlot[k].getResource()->getResource()==&resSlot[i].getResource()->getResource()->MaterialRequirement[j])
				{
					actAmount=resSlot[k].getResource()->getAmount();
				}
				
				k++;
			}

			if(tempMin<actAmount)
			{
				tempReq*=0;
			}
			else
			{
				if(tempMax>actAmount)
				{
					tempReq*=1;
				}
				else
				{
					tempReq*=(actAmount-tempMin)/(tempMax-tempMin);
				}
			}
			j++;
		}
		k=0;
		while(k<resSlot.size())
		{
				
			if(resSlot[i].getResource()->getResource()->resourceMultiplyer==resSlot[k].getResource()->getResource())
			{
				actAmount2=resSlot[k].getResource()->getAmount();
			}
			k++;
		}
		
			resSlot[i].getResource()->setAmount(resSlot[i].getResource()->getAmount()+(actAmount2*manPer*agrPer*minPer*tempReq*resSlot[i].getProductionRate()));
		






		i++;
	}
}