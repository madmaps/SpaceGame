// Matthew APplin
// planet class
#ifndef __PLANET__
#define __PLANET__
#include <vector>
#include "s_object.h"
#include "resourceType.h"
#include "resourceSlot.h"
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

#endif
