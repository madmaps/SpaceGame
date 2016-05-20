// Matthew Applin
// collision class

class collision
{
public:
	bool detect(const double& prevX,const double& prevY,const double& prevZ,
				const double& prevX2,const double& prevY2,const double& prevZ2,
				const double& newX,const double& newY,const double& newZ,const double& newRadius,
				const double& newX2,const double& newY2,const double& newZ2,const double& newRadius2,
				double& collisionPointX,double& collisionPointY,double& collisionPointZ);
};



bool collision::detect(const double& prevX,const double& prevY,const double& prevZ,
				const double& prevX2,const double& prevY2,const double& prevZ2,
				const double& newX,const double& newY,const double& newZ,const double& newRadius,
				const double& newX2,const double& newY2,const double& newZ2,const double& newRadius2,
				double& collisionPointX,double& collisionPointY,double& collisionPointZ)
{
	double firstDistance,middleDistance,lastDistance;
	double middleX,middleY,middleZ,middleRadius;
	double middleX2,middleY2,middleZ2,middleRadius2;
	double larger;


	firstDistance=sqrt(pow(prevX-prevX2,2)+pow(prevY-prevY2,2)+pow(prevZ-prevZ2,2));
	if(firstDistance<=newRadius+newRadius2)
	{
		collisionPointX=prevX;
		collisionPointY=prevY;
		collisionPointZ=prevZ;
		return 1;
	}
	lastDistance=sqrt(pow(newX-newX2,2)+pow(newY-newY2,2)+pow(newZ-newZ2,2));
	if(lastDistance<=newRadius+newRadius2)
	{
		collisionPointX=newX;
		collisionPointY=newY;
		collisionPointZ=newZ;
		return 1;
	}
	middleX=prevX+((newX-prevX)/2);
	middleY=prevY+((newY-prevY)/2);
	middleZ=prevZ+((newZ-prevZ)/2);

	middleX2=prevX2+((newX2-prevX2)/2);
	middleY2=prevY2+((newY2-prevY2)/2);
	middleZ2=prevZ2+((newZ2-prevZ2)/2);

	middleDistance=sqrt(pow(middleX-middleX2,2)+pow(middleY-middleY2,2)+pow(middleZ-middleZ2,2));
	if(middleDistance<=newRadius+newRadius2)
	{
		collisionPointX=middleX;
		collisionPointY=middleY;
		collisionPointZ=middleZ;
		return 1;
	}
	larger=(firstDistance>=lastDistance)?firstDistance:lastDistance;
	if(!(larger-middleDistance*2>=0))
	{
		return 0;
	}
	if(firstDistance>=lastDistance)
	{
		if(this->detect(middleX,middleY,middleZ,middleX2,middleY2,middleZ2,newX,newY,newZ,newRadius,newX2,newY2,newZ2,newRadius2,collisionPointX,collisionPointY,collisionPointZ))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		if(this->detect(prevX,prevY,prevZ,prevX2,prevY2,prevZ2,middleX,middleY,middleZ,newRadius,middleX2,middleY2,middleZ2,newRadius2,collisionPointX,collisionPointY,collisionPointZ))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}