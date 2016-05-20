// Matthew Applin
// Faction

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