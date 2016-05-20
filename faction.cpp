#include "faction.h"

void faction::setName(char* info)
{
	name=info;
}

void faction::setColor(unsigned char* info)
{
	for(int i=0;i<=2;i++)
	{
		color[i]=info[i];
	}
}

char* faction::getName()
{
	return name;
}

unsigned char* faction::getColor()
{
	return &color[0];
}
