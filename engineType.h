// engineType Class
#ifndef __ENGINETYPE__
#define __ENGINETYPE__

class engineType
{
public:
	engineType();
	~engineType();
	char* name;
	int price;
	int engineClass;
	double accerationRate;
	double topSpeed;
	double energyDraw;
	double responseTime;
};
#endif
