// Matthew Applin
// model class

class model
{
public:
	model();
	~model();
	void draw(unsigned int textArray[],int size);

	void getPointArray(float info[],int size);
	void getTextArray(float info[],int size);
	void getNormalArray(float info[],int size);
	void getObjectArray(int info[],int size);
private:
	float* pointArray;
	int pointSize;
	float* textArray;
	int textSize;
	float* normalArray;
	int normalSize;
	int* objectArray;
	int objectSize;
	
};

void model::draw(unsigned int texture[],int size)
{
	int theCounter=0;
	int tempCountKeep=0;
	float work;
	int please;
	

	int m=0;
	int i=0;

	while(m<=objectSize)
	{
		glBindTexture(GL_TEXTURE_2D,texture[m]);
		glBegin(GL_TRIANGLES);
		
		i=theCounter;
		while(i<=objectArray[m]*9+tempCountKeep+tempCountKeep)
		{
									
			work=i/1.5;
			please=work;
			
			glNormal3f(normalArray[i],normalArray[i+1],normalArray[i+2]);
			glTexCoord2f(textArray[please+0],textArray[please+1]);
			glVertex3f(pointArray[i],pointArray[i+1],pointArray[i+2]);
			theCounter=i;
			i+=3;
		}
		tempCountKeep=theCounter;
		glEnd();
		m++;
	}

}

model::model()
{
	pointArray=NULL;
	textArray=NULL;
	normalArray=NULL;
	objectArray=NULL;
	pointSize=0;
	textSize=0;
	normalSize=0;
	objectSize=0;
}

model::~model()
{
	delete pointArray;
	pointArray=NULL;
	delete textArray;
	textArray=NULL;
	delete normalArray;
	normalArray=NULL;
	delete objectArray;
	objectArray=NULL;
}




void model::getPointArray(float info[],int size)
{
	pointSize=size;
	if(pointArray!=NULL)
	{
		delete pointArray;
		pointArray=NULL;
	}
	pointArray=new float[size];
	int i=0;
	while(i<=size-1)
	{
		pointArray[i]=info[i];
		i++;
	}
}

void model::getTextArray(float info[],int size)
{
	textSize=size;
	if(textArray!=NULL)
	{
		delete textArray;
		textArray=NULL;
	}
	textArray=new float[size];
	int i=0;
	while(i<=size-1)
	{
		textArray[i]=info[i];
		i++;
	}
}

void model::getNormalArray(float info[],int size)
{
	normalSize=size;
	if(normalArray!=NULL)
	{
		delete normalArray;
		normalArray=NULL;
	}
	normalArray=new float[size];
	int i=0;
	while(i<=size-1)
	{
		normalArray[i]=info[i];
		i++;
	}
}

void model::getObjectArray(int info[],int size)
{
	objectSize=size;
	if(objectArray!=NULL)
	{
		delete objectArray;
		objectArray=NULL;
	}
	objectArray=new int[size];
	int i=0;
	while(i<=size-1)
	{
		objectArray[i]=info[i];
		i++;
	}
}