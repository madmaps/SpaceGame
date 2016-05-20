// matthew applin
// SpaceObjectClass 2.0

enum RotationType{YAW,PITCH,ROLL};
enum CoordType{WORLD,LOCAL};


class s_object
{
public:
	s_object();
	~s_object();
	void Rotate(RotationType Rtype,float Degrees);
	//Setters
	void setAcceleration(const double& acc);
	void setSpeedDirection(matrix orient,const double& spd);
	void setSpeedDirection(double orient[],const double& spd);
	void setSpeed(double const& spd);
	void setLocation(const double& x, const double& y, const double& z);
	void setLocation(double loc[]);
	void setLocation(const matrix& loc);
	void setPrevLocation(const double& x,const double& y, const double& z);
	void setPrevLocation(double info[]);
	void setSector(const int& x,const int& y,const int& z);
	void setMaxSectors(const int& x,const int& y,const int& z,const int& size);
	//Getters
	void getLocation(double info[]);
	void getPrevLocation(double info[]);
	void getOrientation(double info[]);
	void getWorldOrientation(double info[]);
	int getSectorX();
	int getSectorY();
	int getSectorZ();
	//void setRotationalSpeed(const double& r_spd);
	//void setRotationalDirection(const matrix& dir);
	//void setRotationalAcceleration(const matrix& r_acc);
	//void Turn(RotationType RType,bool PosNeg,float Degrees);
	//void Accelerate(bool PosNeg);
	//float* GetOrientation();
	//float* GetWorldOrientation();
	//float* GetLocation();

	//void SetOrientation(float* Orient);
	//void SetWorldOrientation(float* WorldOrient);
	//void SetLocation(float* Loc);

	void addModel(model& info);
	void addTextures(unsigned int info[],int size);
	void draw();


	void update();
	
		
protected:
	matrix Orientation;//4x4
	matrix WorldOrientation;//4x4
	matrix Location;//4x1
	matrix PrevLocation;
	matrix Direction;//4x1
	matrix Acceleration;//1x1
	matrix Speed;//4x1
	model* t_model;
	unsigned int t_textures[10];

	int sectorSize;
	int sectorX;
	int sectorY;
	int sectorZ;
	int maxX;
	int maxY;
	int maxZ;

	

	//void Rotate(CoordType Ctype,RotationType Rtype,float Degrees,float *Matrix);
	//void MultiplyMatrix(float *Matrix1,int XRows,int XColsYRows,int YCols, float *Matrix2,float *ResultMatrix);
	//void AddMatrix(float *Matrix1,int XRows,int XCols,float *Matrix2,float *ResultMatrix);
};
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
	t_model=NULL;
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
	Speed=Speed+Orientation*Direction*Acceleration;
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
