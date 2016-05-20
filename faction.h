// Matthew Applin
// Faction
#ifndef __FACTION__
#define __FACTION__

class faction
{
public:
	void setName(char* info);
	void setColor(unsigned char* info);
	char* getName();
	unsigned char* getColor();

private:
	char* name;
	unsigned char color[3];
};

#endif
