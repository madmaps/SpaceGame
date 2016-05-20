#include "s_object.h"
#include <GL/gl.h>
#include "math.h"

s_object::s_object()
{
	double info[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
	Orientation.setMatrix(4,4,info);
	WorldOrientation.setMatrix(4,4,info);
	double loc[4]={0,0,0,0};
	Location.setMatrix(4,1,loc);
	PrevLocation.setMatrix(4,1,loc);
	double dir[4]={0,0,-1,1};
	Direction.setMatrix(4,1,dir);
	double acc[4]={0};
	Acceleration.setMatrix(1,1,acc);
	Speed.setRowsCols(4,1);
	t_model=0;
	sectorX=sectorY=sectorZ=0;
	maxX=maxY=maxZ=2;
	sectorSize=200;
}

void s_object::setSector(const int& x,const int& y,const int& z)
{
	sectorX=x;
	sectorY=y;
	sectorZ=z;
}

void s_object::setMaxSectors(const int& x,const int& y,const int& z,const int& size)
{
	maxX=x;
	maxY=y;
	maxZ=z;
	sectorSize=size;
}

int s_object::getSectorX()
{
	return sectorX;
}

int s_object::getSectorY()
{
	return sectorY;
}

int s_object::getSectorZ()
{
	return sectorZ;
}


s_object::~s_object()
{
};

void s_object::addModel(model& info)
{
	t_model=&info;
}

void s_object::addTextures(unsigned int info[],int size)
{
	int i=0;
	while(i<size)
	{
		t_textures[i]=info[i];
		i++;
	}

}

void s_object::draw()
{
	double tempArrOrient[16];
	double tempArrLoc[4];
	glPushMatrix();
		this->getWorldOrientation(tempArrOrient);
		this->getLocation(tempArrLoc);
		glTranslatef(tempArrLoc[0],tempArrLoc[1],tempArrLoc[2]);
		glMultMatrixd(tempArrOrient);
		t_model->draw(t_textures,10);
	glPopMatrix();
}

	
void s_object::Rotate(RotationType Rtype,float Degrees)
{
	Degrees=(Degrees/360)*2*3.14159265;
	double pitchInfo[16]={1,0,0,0,0,cos(Degrees),-sin(Degrees),0,0,sin(Degrees),cos(Degrees),0,0,0,0,1};
	double rollInfo[16]={cos(Degrees),-sin(Degrees),0,0,sin(Degrees),cos(Degrees),0,0,0,0,1,0,0,0,0,1};
	double yawInfo[16]={cos(Degrees),0,sin(Degrees),0,0,1,0,0,-sin(Degrees),0,cos(Degrees),0,0,0,0,1};
	matrix tempMatrix(1,1);
	switch(Rtype)
	{
	case PITCH:
		tempMatrix.setMatrix(4,4,pitchInfo);
		break;
	case ROLL:
		tempMatrix.setMatrix(4,4,rollInfo);
		break;
	case YAW:
		tempMatrix.setMatrix(4,4,yawInfo);
		break;
	}
	Orientation=Orientation*tempMatrix;
	Degrees=-Degrees;
	double pitchInfo2[16]={1,0,0,0,0,cos(Degrees),-sin(Degrees),0,0,sin(Degrees),cos(Degrees),0,0,0,0,1};
	double rollInfo2[16]={cos(Degrees),-sin(Degrees),0,0,sin(Degrees),cos(Degrees),0,0,0,0,1,0,0,0,0,1};
	double yawInfo2[16]={cos(Degrees),0,sin(Degrees),0,0,1,0,0,-sin(Degrees),0,cos(Degrees),0,0,0,0,1};
	switch(Rtype)
	{
	case PITCH:
		tempMatrix.setMatrix(4,4,pitchInfo2);
		break;
	case ROLL:
		tempMatrix.setMatrix(4,4,rollInfo2);
		break;
	case YAW:
		tempMatrix.setMatrix(4,4,yawInfo2);
		break;
	}
	
	WorldOrientation=tempMatrix*WorldOrientation;

	
}
	

void s_object::update()
{
	matrix tempMatrix = Orientation*Direction*Acceleration;
	Speed=Speed+tempMatrix;
	Location=Location+Speed;
	if(Location.getLocation(0)>sectorSize)
	{
		sectorX++;
		if(sectorX>maxX)
		{
			sectorX=0;
		}
	}
	if(Location.getLocation(0)<0)
	{
		sectorX--;
		if(sectorX<0)
		{
			sectorX=maxX;
		}
	}
	if(Location.getLocation(1)>sectorSize)
	{
		sectorY++;
		if(sectorY>maxY)
		{
			sectorY=0;
		}
	}
	if(Location.getLocation(1)<0)
	{
		sectorY--;
		if(sectorY<0)
		{
			sectorY=maxY;
		}
	}
	if(Location.getLocation(2)>sectorSize)
	{
		sectorZ++;
		if(sectorZ>maxZ)
		{
			sectorZ=0;
		}
	}
	if(Location.getLocation(2)<0)
	{
		sectorZ--;
		if(sectorZ<0)
		{
			sectorZ=maxZ;
		}
	}
	
}

void s_object::setAcceleration(const double& acc)
{
	Acceleration.setLocation(0,acc);
}

void s_object::setSpeedDirection(matrix orient,const double& spd)
{
	double startDir[4]={0,0,-1,1};
	double startSpd[1]={spd};
	matrix dir(4,1,startDir);
	matrix newSpd(1,1,startSpd);
	Direction=orient*dir;
	Speed=Direction*newSpd;

}

void s_object::setSpeed(const double& spd)
{
	double speed[1]={spd};
	Speed.setMatrix(1,1,speed);
}
	

void s_object::setSpeedDirection(double info[],const double& spd)
{
	matrix orient;
	orient.setMatrix(4,4,info);
	double startDir[4]={0,0,-1,1};
	double startSpd[1]={spd};
	matrix dir(4,1,startDir);
	matrix newSpd(1,1,startSpd);
	Direction=orient*dir;
	Speed=Direction*newSpd;

}

void s_object::setLocation(const double& x,const double& y,const double& z)
{
	double temp[4]={x,y,z,0};
	Location.setMatrix(4,1,temp);
}

void s_object::setPrevLocation(const double& x,const double& y,const double& z)
{
	double temp[4]={x,y,z,0};
	PrevLocation.setMatrix(4,1,temp);
}

void s_object::setPrevLocation(double info[])
{
	Location.setMatrix(4,1,info);
}

void s_object::setLocation(double info[])
{
	Location.setMatrix(4,1,info);
}

void s_object::setLocation(const matrix& loc)
{
	Location=loc;
}

void s_object::getLocation(double info[])
{
	for(int i=0;i<=3;i++)
	{
		info[i]=Location.getLocation(i);
	}
}

void s_object::getPrevLocation(double info[])
{
	for(int i=0;i<=3;i++)
	{
		info[i]=PrevLocation.getLocation(i);
	}
}

void s_object::getOrientation(double info[])
{
	for(int i=0;i<=15;i++)
	{
		info[i]=Orientation.getLocation(i);
	}
}

void s_object::getWorldOrientation(double info[])
{
	for(int i=0;i<=15;i++)
	{
		info[i]=WorldOrientation.getLocation(i);
	}
}
