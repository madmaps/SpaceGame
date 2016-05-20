#ifndef __STARFIELD__
#define __STARFIELD__
#include <vector>
#include "stars.h"

class starfield
{
public:
	starfield();
	starfield(const int& count);
	void getLocation(const int& star,double loc[]);
	int getCount(){return starCount;}
	~starfield(){}
private:
	int starCount;
	
	std::vector<stars> s_field;
};

#endif
