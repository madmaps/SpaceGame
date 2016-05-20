// Matthew Applin
// model class
#ifndef __MODEL__
#define __MODEL__

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

#endif

