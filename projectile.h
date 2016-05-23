// Projectile Class
#ifndef __PROJECTILE__
#define __PROJECTILE__
#include "s_object.h"

class projectile : public s_object
{
public:
	projectile();
	void setDamage(const double& damage);
	void setRange(const double& range);
	void update();
	void setTime(const double& info);
	bool isDone();
	double getDamage();
	void setDone();
	~projectile();
private:
	double potentialDamage;
	double Max_Range;
	double Remaining_Range;
	bool done;
	double timeChange;
	
	//Player owner;

};
#endif

