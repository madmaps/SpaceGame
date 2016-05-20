// Matthew Applin
// frustum class


class planes
{
public:
	double A,B,C,D;
};

class frustum
{
public:
	void update();
	int frustumCheck(const double& x,const double& y,const double& z, const double& rad);
private:
	planes t_planes[6];
};

int frustum::frustumCheck(const double& x,const double& y,const double& z, const double& rad)
{
	double dist;
	for(int i=0;i<6;i++)
	{
		dist=t_planes[i].A*x+t_planes[i].B*y+t_planes[i].C*z+t_planes[i].D;
		if(dist<=-rad)
		{
			return 0;
		}
	}
	return 1;
}






void frustum::update()
{
	double modelView[16];
	double projectionView[16];

	
	glGetDoublev(GL_PROJECTION_MATRIX, projectionView);
	matrix projView(4,4,projectionView);
	glGetDoublev(GL_MODELVIEW_MATRIX,modelView);
	matrix modView(4,4,modelView);

	//modView=projView*modView;
	modView=modView*projView;

	//glPushMatrix();
	//glLoadMatrixd(projectionView);
	//glMultMatrixd(modelView);
	//glGetDoublev(GL_MODELVIEW_MATRIX,modelView);
	//glPopMatrix();
	

	int i=0;
	int scale=0;
	int row=0;
	int counter=0;
	while(i<6)
	{
		if(counter<=0)
		{
			counter=-counter;
			counter++;
			
		}
		else
		{
			counter=-counter;
			
		}
		scale=(counter<0)?-1:1;
		row=abs(counter)-1;

		t_planes[i].A=modView.getLocation(3)+scale*modView.getLocation(row);
		t_planes[i].B=modView.getLocation(7)+scale*modView.getLocation(row+4);
		t_planes[i].C=modView.getLocation(11)+scale*modView.getLocation(row+8);
		t_planes[i].D=modView.getLocation(15)+scale*modView.getLocation(row+12);

		double length=sqrt(t_planes[i].A*t_planes[i].A+t_planes[i].B*t_planes[i].B+t_planes[i].C*t_planes[i].C);
		t_planes[i].A/=length;
		t_planes[i].B/=length;
		t_planes[i].C/=length;
		t_planes[i].D/=length;
		
		i++;
	}


}
	
	
