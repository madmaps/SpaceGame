// Matthew Applin
// player class

class player
{
public:
	player();
	~player();
	void setName(char* info);
	void setFaction(faction& info);
	faction* getFaction();
	void addMoney(double info);
	void removeMoney(double info);
	double getMoney();
	ship t_ship;
private:
	char* name;
	faction* t_faction;
	double money;
	
	float lookingX;
	float lookingY;
	float lookingZ;
};

player::player()
{
	name=NULL;
	t_faction=NULL;
	money=0;
	lookingX=0;
	lookingY=0;
	lookingZ=0;
}
player::~player()
{}

void player::setFaction(faction& info)
{
	t_faction=&info;
}

faction* player::getFaction()
{
	return t_faction;
}

void player::setName(char* info)
{
	name=info;
}

void player::addMoney(double info)
{
	money+=info;
}

void player::removeMoney(double info)
{
	money-=info;
}

double player::getMoney()
{
	return money;
}

