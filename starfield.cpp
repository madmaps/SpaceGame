#include "starfield.h"
#include <random>

starfield::starfield(const int& count)
{
	starCount=count;
	std::mt19937 eng(static_cast<unsigned long>(time(nullptr)));
	std::uniform_int_distribution<int> dist(0,1000);
	double Degrees=360/(dist(eng));
	
	double pitchInfo[16]={1,0,0,0,0,cos(Degrees),-sin(Degrees),0,0,sin(Degrees),cos(Degrees),0,0,0,0,1};
	double rollInfo[16]={cos(Degrees),-sin(Degrees),0,0,sin(Degrees),cos(Degrees),0,0,0,0,1,0,0,0,0,1};

	stars tempStar;
	double tempArr[4]={0,0,-1000,0};
	
	matrix tempMatrix;
	matrix rotation;
	//s_field.resize(count);
	for(int i=0;i<=count;i++)
	{
		Degrees=(3.14159265358979*2*dist(eng))/1000;
		pitchInfo[5]=cos(Degrees);
		pitchInfo[6]=-sin(Degrees);
		pitchInfo[9]=sin(Degrees);
		pitchInfo[10]=cos(Degrees);

		rotation.setMatrix(4,4,pitchInfo);

		tempMatrix.setMatrix(4,1,tempArr);
		tempMatrix=rotation*tempMatrix;

		Degrees=(3.14159265358979*2*dist(eng))/1000;
		rollInfo[0]=cos(Degrees);
		rollInfo[1]=-sin(Degrees);
		rollInfo[4]=sin(Degrees);
		rollInfo[5]=cos(Degrees);

		rotation.setMatrix(4,4,rollInfo);
		tempMatrix=rotation*tempMatrix;
		tempStar.setStar(tempMatrix,255,255);

		s_field.push_back(tempStar);
	}
}

void starfield::getLocation(const int& star,double loc[])
{
	//double temp[4];
	s_field[star].getLocation(loc);

	//for(int i=0;i<=3;i++)
	//{
	//	s_field[star].getLocation(temp);
	//	loc[0]=temp[0];
	//	loc[1]=temp[1];
	//	loc[2]=temp[2];
	//	loc[3]=temp[3];
	//}
}
