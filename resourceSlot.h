// Matthew Applin
// resourceSlot class

class resourceSlot
{
public:
	resourceSlot(resourceType& info,const double& quantity);
	~resourceSlot();
	void increaseProduction();
	void decreaseProduction();
	void update(const double& elapsedTime);
	double getProductionRate();
	resource* getResource();
private:
	double currentProductionRate;
	resource currentResource;
};

resourceSlot::resourceSlot(resourceType& info,const double& quantity):currentResource(info,quantity)
{
	currentProductionRate=info.standardProductionRate;
}

resourceSlot::~resourceSlot()
{}



resource* resourceSlot::getResource()
{
	return &currentResource;
}

double resourceSlot::getProductionRate()
{
	return currentProductionRate;
}

