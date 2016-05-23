// gunType Class
#ifndef __GUNTYPE__
#define __GUNTYPE__
#include "matrix.h"

class gunType
{
public:
	char* name;
	int price;
	int gunClass;
	int damagePotential;
	double rateOfFire;
	double energyDraw;
	double projectileSpeed;
	int projectileRange;
	int model;
	int numberOfTextures;
	int* textures;
	matrix location;
};
#endif
