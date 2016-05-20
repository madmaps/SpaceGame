// Matthew Applin
// solarRechargerClass

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