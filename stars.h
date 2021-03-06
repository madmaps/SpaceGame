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

stars::stars()
{
}
stars::~stars(){}

stars::stars(const matrix& info,const int& bright,const int& tnt)
{
	m_star=info;
	brightness=bright;
	tint=tnt;
}

void stars::setStar(const matrix& info,const int& bright,const int& tnt)
{
	m_star=info;
	brightness=bright;
	tint=tnt;
}

void stars::getLocation(double info[])
{
	for(int i=0;i<=3;i++)
	{
		info[i]=m_star.getLocation(i);
	}
}
