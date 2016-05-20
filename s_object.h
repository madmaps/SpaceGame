// matthew applin
// SpaceObjectClass 2.0
#ifndef __S_OBJECT__
#define __S_OBJECT__
#include "matrix.h"
#include "model.h"

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

#endif
