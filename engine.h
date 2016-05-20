// engine class

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

