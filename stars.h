#ifndef __STARS__
#define __STARS__
#include "matrix.h"

class stars
{
public:
	stars();
	stars(const matrix& info,const int& bright,const int& tnt);
	void setStar(const matrix& info,const int& bright,const int& tnt);
	void getLocation(double info[]);
	~stars();
private:
	matrix m_star;
	int brightness;
	int tint;
};

#endif

