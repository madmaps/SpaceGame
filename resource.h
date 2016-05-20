// Matthew Applin
// resource

class resource
{
public:
	resource(resourceType& info,const double& quantity);
	~resource();
	resourceType* getResource();
	double getAmount();
	void setAmount(const double& info);
private:
	resourceType* r_type;
	double amount;
};

resource::resource(resourceType& info,const double& quantity)
{
	r_type=&info;
	amount=quantity;
}

resource::~resource()
{}

resourceType* resource::getResource()
{
	return r_type;
}

double resource::getAmount()
{
	return amount;
}

void resource::setAmount(const double& info)
{
	amount=info;
}