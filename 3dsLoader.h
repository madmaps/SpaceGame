// Matthew Applin
// 3dsLoader class

// Matthew Applin
// 3dsLoader class
#include <fstream>
#include <vector>

class header
{
public:
	header (char* inputBuffer,int length, int* startPosition, int* endPosition);
	~header();
	unsigned short id;
	long length;
};


header::header(char* inputBuffer,int size,int* sPosition, int* ePosition)
{
	char temp[2];
	char temp2[4];
	temp[0]=inputBuffer[*sPosition+0];
	temp[1]=inputBuffer[*sPosition+1];
	id=reinterpret_cast<short&>(temp);

	temp2[0]=inputBuffer[*sPosition+2];
	temp2[1]=inputBuffer[*sPosition+3];
	temp2[2]=inputBuffer[*sPosition+4];
	temp2[3]=inputBuffer[*sPosition+5];

	length=reinterpret_cast<long&>(temp2);
	*ePosition=*sPosition+6;
}

header::~header()
{
}

class unknown
{
public:
	unknown(char* inputBuffer,int size,int* sPosition,int *ePosition);
	~unknown();
	header* t_header;
};

unknown::unknown(char* inputBuffer,int size,int* sPosition,int *ePosition)
{
	t_header=new header(inputBuffer,size,sPosition,ePosition);
	*sPosition=*ePosition;
	*ePosition=t_header->length+*sPosition-6;
	//header tempHeader(inputBuffer,size,sPosition,ePosition);
	//*sPosition=*ePosition;
	//*ePosition=t_header->length+*sPosition;
	
}

unknown::~unknown()
{
	if(t_header!=NULL)
	{
		delete t_header;
		t_header=NULL;
	}
}

class matName
{
public:
	matName(char* inputBuffer,int size,int* sPosition,int* ePosition);
	~matName();
	header* t_header;
	char* name;
};

matName::~matName()
{
	if(t_header!=NULL)
	{
		delete t_header;
		t_header=NULL;
	}
}

matName::matName(char* inputBuffer,int size,int* sPosition,int* ePosition)
{

	t_header=new header(inputBuffer,size,sPosition,ePosition);
	*sPosition=*ePosition;
	*ePosition=t_header->length+*sPosition-6;
	name=new char[16];
	for(int i=0;i<=t_header->length-6;i++)
	{
		name[i]=inputBuffer[i+*sPosition];
	}
	
}

class color24
{
public:
	
	color24(char* inputBuffer,int size,int* sPosition,int* ePosition);
	~color24();
	header* t_header;
	unsigned char t_red;
	unsigned char t_green;
	unsigned char t_blue;
};

color24::~color24()
{
	if(t_header!=NULL)
	{
		delete t_header;
		t_header=NULL;
	}
}

color24::color24(char* inputBuffer,int size,int* sPosition,int* ePosition)
{

	t_header=new header(inputBuffer,size,sPosition,ePosition);
	*sPosition=*ePosition;
	*ePosition=t_header->length+*sPosition-6;
	t_red=reinterpret_cast<unsigned char&>(inputBuffer[0+*sPosition]);
	t_green=reinterpret_cast<unsigned char&>(inputBuffer[1+*sPosition]);
	t_blue=reinterpret_cast<unsigned char&>(inputBuffer[2+*sPosition]);
}

class linColor24
{
public:
	linColor24(char* inputBuffer,int size,int* sPosition,int* ePosition);
	~linColor24();
	header* t_header;
	unsigned char t_red;
	unsigned char t_green;
	unsigned char t_blue;
};

linColor24::~linColor24()
{
	if(t_header!=NULL)
	{
		delete t_header;
		t_header=NULL;
	}
}

linColor24::linColor24(char* inputBuffer,int size,int* sPosition,int* ePosition)
{

	t_header=new header(inputBuffer,size,sPosition,ePosition);
	*sPosition=*ePosition;
	*ePosition=t_header->length+*sPosition-6;
	t_red=reinterpret_cast<unsigned char&>(inputBuffer[0+*sPosition]);
	t_green=reinterpret_cast<unsigned char&>(inputBuffer[1+*sPosition]);
	t_blue=reinterpret_cast<unsigned char&>(inputBuffer[2+*sPosition]);
}

class intPercentage
{
public:
	intPercentage(char* inputBuffer,int size,int* sPosition,int *ePosition);
	~intPercentage();
	header* t_header;
	unsigned short t_percentage;
};

intPercentage::~intPercentage()
{
	if(t_header!=NULL)
	{
		delete t_header;
		t_header=NULL;
	}
}

intPercentage::intPercentage(char* inputBuffer,int size,int* sPosition,int *ePosition)
{
	t_header=new header(inputBuffer,size,sPosition,ePosition);
	*sPosition=*ePosition;
	*ePosition=t_header->length+*sPosition-6;

	char tempChar[2];
	tempChar[0]=inputBuffer[0+*sPosition];
	tempChar[1]=inputBuffer[1+*sPosition];
	t_percentage=reinterpret_cast<short&>(tempChar);



}

class pointArray
{
	public:
	pointArray(char* inputBuffer,int size,int* sPosition,int *ePosition);
	~pointArray();
	header* t_header;
	unsigned short numberOfPoints;
	float* pointList;
};

pointArray::~pointArray()
{
	if(t_header!=NULL)
	{
		delete t_header;
		t_header=NULL;
	}

	if(pointList!=NULL)
	{
		delete[] pointList;
		pointList=NULL;
	}
}

pointArray::pointArray(char* inputBuffer,int size,int* sPosition,int* ePosition)
{
	t_header=new header(inputBuffer,size,sPosition,ePosition);
	int start=*sPosition;
	*sPosition=*ePosition;
	*ePosition=t_header->length+*sPosition-6;
	char tempChar[2];
	tempChar[0]=inputBuffer[0+*sPosition];
	tempChar[1]=inputBuffer[1+*sPosition];
	numberOfPoints=reinterpret_cast<short&>(tempChar);
	*sPosition+=2;

	unsigned char tempChar2[4];
	pointList=new float[numberOfPoints*3];
	for(int i=0;i<=numberOfPoints-1;i++)
	{
		for(int j=0;j<=2;j++)
		{
			for(int k=0;k<=3;k++)
			{
				tempChar2[k]=inputBuffer[(12*i)+(j*4)+k+*sPosition];
			}
			pointList[(i*3)+j]=reinterpret_cast<float&>(tempChar2);
		}
		


	}
	
	
}

class mshMatGroup
{
	public:
	mshMatGroup(char* inputBuffer,int size,int* sPosition,int *ePosition);
	~mshMatGroup();
	header* t_header;
	char* name;
	unsigned short numberOfFaces;

	unsigned short* matFaceList;
	
};

mshMatGroup::~mshMatGroup()
{
	if(t_header!=NULL)
	{
		delete t_header;
		t_header=NULL;
	}
	if(matFaceList!=NULL)
	{
		delete[] matFaceList;
		matFaceList=NULL;
	}
}

mshMatGroup::mshMatGroup(char* inputBuffer,int size,int* sPosition,int* ePosition)
{

	t_header=new header(inputBuffer,size,sPosition,ePosition);
	int start=*sPosition;
	*sPosition=*ePosition;
	*ePosition=t_header->length+*sPosition-6;

	name=new char[30];
	int i=0;
	do
	{
		name[i]=inputBuffer[i+*sPosition];
		i++;
	}while(inputBuffer[i+*sPosition]!=0);
	name[i]=0;
	*sPosition+=i+1;
	
	char tempChar[2];
	tempChar[0]=inputBuffer[0+*sPosition];
	tempChar[1]=inputBuffer[1+*sPosition];
	numberOfFaces=reinterpret_cast<unsigned short&>(tempChar);
	*sPosition+=2;

	matFaceList=new unsigned short[numberOfFaces];
	for(int i=0;i<=numberOfFaces-1;i++)
	{
		
			for(int k=0;k<=1;k++)
			{
				tempChar[k]=inputBuffer[(2*i)+k+*sPosition];
			}
			matFaceList[i]=reinterpret_cast<unsigned short&>(tempChar);
	}
	
	
}

class faceArray
{
	public:
	faceArray(char* inputBuffer,int size,int* sPosition,int *ePosition);
	~faceArray();
	header* t_header;
	unsigned short numberOfFaces;
	unsigned short* faceList;
	std::vector<mshMatGroup*> t_mshMatGroup;
	std::vector<unknown*> t_unknown;
};

faceArray::~faceArray()
{
	if(t_header!=NULL)
	{
		delete t_header;
		t_header=NULL;
	}
	if(faceList!=NULL)
	{
		delete[] faceList;
		faceList=NULL;
	}
	int i=0;
	while(i<t_mshMatGroup.size())
	{
		delete t_mshMatGroup[i];
		t_mshMatGroup[i]=NULL;
		i++;
	}
	t_mshMatGroup.empty();
	i=0;
	while(i<t_unknown.size())
	{
		delete t_unknown[i];
		t_unknown[i]=NULL;
		i++;
	}
	t_unknown.empty();


}


faceArray::faceArray(char* inputBuffer,int size,int* sPosition,int* ePosition)
{
	faceList=NULL;

	t_header=new header(inputBuffer,size,sPosition,ePosition);
	int start=*sPosition;
	*sPosition=*ePosition;
	*ePosition=t_header->length+*sPosition-6;
	char tempChar[2];
	tempChar[0]=inputBuffer[0+*sPosition];
	tempChar[1]=inputBuffer[1+*sPosition];
	numberOfFaces=reinterpret_cast<short&>(tempChar);
	*sPosition+=2;
	faceList=new unsigned short[numberOfFaces*4];
	int counter=0;
	for(int i=0;i<=numberOfFaces-1;i++)
	{
		for(int j=0;j<=3;j++)
		{
			for(int k=0;k<=1;k++)
			{
				tempChar[k]=inputBuffer[(8*i)+(j*2)+k+*sPosition];
				counter++;
				
			}
			faceList[(i*4)+j]=reinterpret_cast<unsigned short&>(tempChar);
		}
	}

	*sPosition+=counter;
	mshMatGroup* tempGroup;
	while(*sPosition<*ePosition)
	{
		header tempHeader(inputBuffer,size,sPosition,ePosition);
		*ePosition=t_header->length+start;
		switch(tempHeader.id)
		{
		case 0x4130:
			tempGroup = new mshMatGroup(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			t_mshMatGroup.push_back(tempGroup);
			break;
		
		default:
			unknown* tempUnknownPtr=new unknown(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			t_unknown.push_back(tempUnknownPtr);
			break;
		}
	}
	
	
}

class textureMap
{
	public:
	textureMap(char* inputBuffer,int size,int* sPosition,int *ePosition);
	~textureMap();
	header* t_header;
	unsigned short numberOfMaps;
	float* mapList;
	
};

textureMap::~textureMap()
{
	if(t_header!=NULL)
	{
		delete t_header;
		t_header=NULL;
	}
	if(mapList!=NULL)
	{
		delete[] mapList;
		mapList=NULL;
	}
}

textureMap::textureMap(char* inputBuffer,int size,int* sPosition,int* ePosition)
{

	t_header=new header(inputBuffer,size,sPosition,ePosition);
	int start=*sPosition;
	*sPosition=*ePosition;
	*ePosition=t_header->length+*sPosition-6;
	char tempChar[4];
	tempChar[0]=inputBuffer[0+*sPosition];
	tempChar[1]=inputBuffer[1+*sPosition];
	numberOfMaps=reinterpret_cast<unsigned short&>(tempChar);
	*sPosition+=2;
	mapList=new float[numberOfMaps*2];
	float test=0;
	int counter=0;
	for(int i=0;i<=numberOfMaps-1;i++)
	{
		for(int j=0;j<=1;j++)
		{
			for(int k=0;k<=3;k++)
			{
				tempChar[k]=inputBuffer[(8*i)+(j*4)+k+*sPosition];
				counter++;
				
			}
			test=reinterpret_cast<float&>(tempChar);
			mapList[(i*2)+j]=reinterpret_cast<float&>(tempChar);
		}
	}

	*sPosition+=counter;
	
	
}



class nTriObject
{
public:
	nTriObject(char* inputBuffer,int size,int* sPosition,int *ePosition);
	~nTriObject();
	header* t_header;
	pointArray* t_pointArray;
	faceArray* t_faceArray;
	textureMap* t_textureMap;
	std::vector<mshMatGroup*> t_mshMatGroup;
	std::vector<unknown*> t_unknown;

};

nTriObject::~nTriObject()
{
	if(t_header!=NULL)
	{
		delete t_header;
		t_header=NULL;
	}
	if(t_pointArray!=NULL)
	{
		delete t_pointArray;
		t_pointArray=NULL;
	}
	if(t_faceArray!=NULL)
	{
		delete t_faceArray;
		t_faceArray=NULL;
	}
	if(t_textureMap!=NULL)
	{
		delete t_textureMap;
		t_textureMap=NULL;
	}
	int i=0;
	while(i<t_mshMatGroup.size())
	{
		delete t_mshMatGroup[i];
		t_mshMatGroup[i]=NULL;
		i++;
	}
	t_mshMatGroup.empty();
	i=0;
	while(i<t_unknown.size())
	{
		delete t_unknown[i];
		t_unknown[i]=NULL;
		i++;
	}
	t_unknown.empty();
}


nTriObject::nTriObject(char* inputBuffer,int size,int* sPosition,int* ePosition)
{
	t_faceArray=NULL;
	t_textureMap=NULL;
	t_pointArray=NULL;
	t_header=new header(inputBuffer,size,sPosition,ePosition);
	int start=*sPosition;
	*sPosition=*ePosition;
	*ePosition=t_header->length+*sPosition-6;
	mshMatGroup* tempGroup;
	
	while(*sPosition<*ePosition)
	{
		header tempHeader(inputBuffer,size,sPosition,ePosition);
		*ePosition=t_header->length+start;
		switch(tempHeader.id)
		{
		case 0x4110:
			t_pointArray=new pointArray(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			break;
		case 0x4120:
			t_faceArray=new faceArray(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			break;
		case 0x4130:
			tempGroup = new mshMatGroup(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			t_mshMatGroup.push_back(tempGroup);
			break;
		case 0x4140:
			t_textureMap=new textureMap(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			break;
		default:
			unknown* tempUnknownPtr=new unknown(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			t_unknown.push_back(tempUnknownPtr);
			break;
		}
		//*ePosition=t_header->length;
	}
}

class namedObject
{
public:
	namedObject(char* inputBuffer,int size,int* sPosition,int* ePosition);
	~namedObject();
	header* t_header;
	char* name;
	nTriObject* t_object;

};

namedObject::~namedObject()
{
	if(t_header!=NULL)
	{
		delete t_header;
		t_header=NULL;
	}
	if(name!=NULL)
	{
		delete[] name;
		name=NULL;
	}
	if(t_object!=NULL)
	{
		delete t_object;
		t_object=NULL;
	}
}

namedObject::namedObject(char* inputBuffer,int size,int* sPosition,int* ePosition)
{
	t_object=NULL;
	t_header=new header(inputBuffer,size,sPosition,ePosition);
	int start=*sPosition;
	*sPosition=*ePosition;
	*ePosition=t_header->length+*sPosition-6;
	name=new char[30];
	int i=0;
	do
	{
		name[i]=inputBuffer[i+*sPosition];
		i++;
	}while(inputBuffer[i+*sPosition]!=0);
	name[i]=0;
	*sPosition+=i+1;


	t_object=new nTriObject(inputBuffer,size,sPosition,ePosition);
	
}

class matAmbient
{
public:
	matAmbient(char* inputBuffer,int size,int* sPosition,int* ePosition);
	~matAmbient();
	header* t_header;
	color24* t_color24;
	linColor24* t_linColor24;
	std::vector<unknown*> t_unknown;

};

matAmbient::~matAmbient()
{
	if(t_header!=NULL)
	{
		delete t_header;
		t_header=NULL;
	}

	if(t_color24!=NULL)
	{
		delete t_color24;
		t_color24=NULL;
	}
	if(t_linColor24!=NULL)
	{
		delete t_linColor24;
		t_linColor24=NULL;
	}
	int i=0;
	while(i<t_unknown.size())
	{
		delete t_unknown[i];
		t_unknown[i]=NULL;
		i++;
	}
	t_unknown.empty();
}



matAmbient::matAmbient(char* inputBuffer,int size,int* sPosition,int* ePosition)
{

	t_header=new header(inputBuffer,size,sPosition,ePosition);
	int start=*sPosition;
	*sPosition=*ePosition;
	*ePosition=t_header->length+*sPosition-6;
	
	while(*sPosition<*ePosition)
	{
		header tempHeader(inputBuffer,size,sPosition,ePosition);
		*ePosition=t_header->length+start;
		switch(tempHeader.id)
		{
		case 0x0011:
			t_color24=new color24(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			break;
		case 0x0012:
			t_linColor24=new linColor24(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			break;

		default:
			unknown* tempUnknownPtr=new unknown(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			t_unknown.push_back(tempUnknownPtr);
			break;
		}
		
	}
}

class matDiffuse
{
public:
	matDiffuse(char* inputBuffer,int size,int* sPosition,int* ePosition);
	~matDiffuse();
	header* t_header;
	color24* t_color24;
	linColor24* t_linColor24;
	std::vector<unknown*> t_unknown;

};

matDiffuse::~matDiffuse()
{
	if(t_header!=NULL)
	{
		delete t_header;
		t_header=NULL;
	}

	if(t_color24!=NULL)
	{
		delete t_color24;
		t_color24=NULL;
	}
	if(t_linColor24!=NULL)
	{
		delete t_linColor24;
		t_linColor24=NULL;
	}
	int i=0;
	while(i<t_unknown.size())
	{
		delete t_unknown[i];
		t_unknown[i]=NULL;
		i++;
	}
	t_unknown.empty();
}


matDiffuse::matDiffuse(char* inputBuffer,int size,int* sPosition,int* ePosition)
{

	t_header=new header(inputBuffer,size,sPosition,ePosition);
	int start=*sPosition;
	*sPosition=*ePosition;
	*ePosition=t_header->length+*sPosition-6;
	
	while(*sPosition<*ePosition)
	{
		header tempHeader(inputBuffer,size,sPosition,ePosition);
		*ePosition=t_header->length+start;
		switch(tempHeader.id)
		{
		case 0x0011:
			t_color24=new color24(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			break;
		case 0x0012:
			t_linColor24=new linColor24(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			break;

		default:
			unknown* tempUnknownPtr=new unknown(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			t_unknown.push_back(tempUnknownPtr);
			break;
		}
		
	}
}
	
class matSpecular
{
public:
	matSpecular(char* inputBuffer,int size,int* sPosition,int* ePosition);
	~matSpecular();
	header* t_header;
	color24* t_color24;
	linColor24* t_linColor24;
	std::vector<unknown*> t_unknown;

};

matSpecular::~matSpecular()
{
	if(t_header!=NULL)
	{
		delete t_header;
		t_header=NULL;
	}

	if(t_color24!=NULL)
	{
		delete t_color24;
		t_color24=NULL;
	}
	if(t_linColor24!=NULL)
	{
		delete t_linColor24;
		t_linColor24=NULL;
	}
	int i=0;
	while(i<t_unknown.size())
	{
		delete t_unknown[i];
		t_unknown[i]=NULL;
		i++;
	}
	t_unknown.empty();
}


matSpecular::matSpecular(char* inputBuffer,int size,int* sPosition,int* ePosition)
{

	t_header=new header(inputBuffer,size,sPosition,ePosition);
	int start=*sPosition;
	*sPosition=*ePosition;
	*ePosition=t_header->length+*sPosition-6;
	
	while(*sPosition<*ePosition)
	{
		header tempHeader(inputBuffer,size,sPosition,ePosition);
		*ePosition=t_header->length+start;
		switch(tempHeader.id)
		{
		case 0x0011:
			t_color24=new color24(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			break;
		case 0x0012:
			t_linColor24=new linColor24(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			break;

		default:
			unknown* tempUnknownPtr=new unknown(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			t_unknown.push_back(tempUnknownPtr);
			break;
		}
		
	}
}
	
class masterScale
{
public:
	masterScale(char* inputBuffer,int size,int* sPosition,int* ePosition);
	~masterScale();
	header* t_header;
	float scale;
};

masterScale::~masterScale()
{
	if(t_header!=NULL)
	{
		delete t_header;
		t_header=NULL;
	}
}



masterScale::masterScale(char* inputBuffer,int size,int* sPosition,int* ePosition)
{

	t_header=new header(inputBuffer,size,sPosition,ePosition);
	*sPosition=*ePosition;
	*ePosition=t_header->length+*sPosition-6;
	char tempChar[4];
	tempChar[0]=inputBuffer[0+*sPosition];
	tempChar[1]=inputBuffer[1+*sPosition];
	tempChar[2]=inputBuffer[2+*sPosition];
	tempChar[3]=inputBuffer[3+*sPosition];
	scale=reinterpret_cast<float&>(tempChar);
}

class matEntry
{
public:
	matEntry(char* inputBuffer,int size,int* sPosition,int* ePosition);
	~matEntry();
	header* t_header;
	matName* t_name;
	matAmbient* t_ambient;
	matDiffuse* t_diffuse;
	matSpecular* t_specular;
	//matShininess* t_shininess;
	//matTransparency* t_transparency;
	//matShading* t_shading;
	std::vector<unknown*> t_unknown;
};

matEntry::~matEntry()
{
	if(t_header!=NULL)
	{
		delete t_header;
		t_header=NULL;
	}
	if(t_name!=NULL)
	{
		delete t_name;
		t_name=NULL;
	}
	if(t_ambient!=NULL)
	{
		delete t_ambient;
		t_ambient=NULL;
	}
	if(t_diffuse!=NULL)
	{
		delete t_diffuse;
		t_diffuse=NULL;
	}
	if(t_specular!=NULL)
	{
		delete t_specular;
		t_specular=NULL;
	}
	int i=0;
	while(i<t_unknown.size())
	{
		delete t_unknown[i];
		t_unknown[i]=NULL;
		i++;
	}
	t_unknown.empty();
}

matEntry::matEntry(char* inputBuffer,int size,int* sPosition,int* ePosition)
{
	t_name=NULL;
	t_ambient=NULL;
	t_diffuse=NULL;
	t_specular=NULL;
	t_header=new header(inputBuffer,size,sPosition,ePosition);
	int start=*sPosition;
	*sPosition=*ePosition;
	*ePosition=t_header->length+*sPosition-6;
	
	while(*sPosition<*ePosition)
	{
		header tempHeader(inputBuffer,size,sPosition,ePosition);
		*ePosition=t_header->length+start;
		switch(tempHeader.id)
		{
		case 0xa000:
			t_name=new matName(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			break;
		case 0xa010:
			t_ambient=new matAmbient(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			break;
		case 0xa020:
			t_diffuse=new matDiffuse(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			break;
		case 0xa030:
			t_specular=new matSpecular(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			break;
		
		//case 0xa050:


		default:
			unknown* tempUnknownPtr=new unknown(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			t_unknown.push_back(tempUnknownPtr);
			break;
		}
		//*ePosition=t_header->length;
	}
}

class meshVersion
{
public:
	meshVersion(char* inputBuffer,int size,int* sPosition,int* ePosition);
	~meshVersion();
	header* t_header;
	long version;
};

meshVersion::~meshVersion()
{
	if(t_header!=NULL)
	{
		delete t_header;
		t_header=NULL;
	}
}


meshVersion::meshVersion(char* inputBuffer,int size,int* sPosition,int* ePosition)
{

	t_header=new header(inputBuffer,size,sPosition,ePosition);
	*sPosition=*ePosition;
	*ePosition=t_header->length+*sPosition-6;
	char tempChar[4];
	tempChar[0]=inputBuffer[0+*sPosition];
	tempChar[1]=inputBuffer[1+*sPosition];
	tempChar[2]=inputBuffer[2+*sPosition];
	tempChar[3]=inputBuffer[3+*sPosition];
	version=reinterpret_cast<long&>(tempChar);
}
	
class mdata
{
public:
	mdata(char* inputBuffer,int size,int* sPosition,int* ePosition);
	~mdata();
	header* t_header;
	meshVersion* t_version;
	std::vector<matEntry*> t_mat;
	masterScale* t_scale;
	std::vector<unknown*> t_unknown;

	std::vector<namedObject*> t_name;
};

mdata::~mdata()
{
	
	if(t_header!=NULL)
	{
		delete t_header;
		t_header=NULL;
	}
	if(t_version!=NULL)
	{
		delete t_version;
		t_version=NULL;
	}
	if(t_scale!=NULL)
	{
		delete t_scale;
		t_scale=NULL;
	}
	int i=0;
	while(i<t_name.size())
	{
		delete t_name[i];
		t_name[i]=NULL;
		i++;
	}
	t_name.empty();
	i=0;
	while(i<t_unknown.size())
	{
		delete t_unknown[i];
		t_unknown[i]=NULL;
		i++;
	}
	t_unknown.empty();
}


mdata::mdata(char* inputBuffer,int size,int* sPosition,int* ePosition)
{
	t_version=NULL;
	t_scale=NULL;
	t_header=new header(inputBuffer,size,sPosition,ePosition);
	int start=*sPosition;
	*sPosition=*ePosition;
	*ePosition=t_header->length+*sPosition-6;
	
	matEntry* tempMatEntry;
	namedObject* tempObject;
	while(*sPosition<*ePosition)
	{
		header tempHeader(inputBuffer,size,sPosition,ePosition);
		*ePosition=t_header->length+start;
		switch(tempHeader.id)
		{
		case 0x3d3e:
			t_version=new meshVersion(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			break;
		case 0xafff:
			tempMatEntry=new matEntry(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			t_mat.push_back(tempMatEntry);
			break;
		case 0x4000:
			tempObject=new namedObject(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			t_name.push_back(tempObject);
			break;

		default:
			unknown* tempUnknownPtr=new unknown(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			t_unknown.push_back(tempUnknownPtr);
			break;
		}
		
	}
}

class m3dVersion
{
public:
	m3dVersion::m3dVersion(char* inputBuffer,int size,int* sPosition,int* ePosition);
	~m3dVersion();
	header* t_header;
	long version;
};

m3dVersion::~m3dVersion()
{
	if(t_header!=NULL)
	{
		delete t_header;
		t_header=NULL;
	}
}

m3dVersion::m3dVersion(char* inputBuffer,int size,int* sPosition,int* ePosition)
{

	t_header=new header(inputBuffer,size,sPosition,ePosition);
	*sPosition=*ePosition;
	*ePosition=t_header->length+*sPosition-6;
	char tempChar[4];
	tempChar[0]=inputBuffer[0+*sPosition];
	tempChar[1]=inputBuffer[1+*sPosition];
	tempChar[2]=inputBuffer[2+*sPosition];
	tempChar[3]=inputBuffer[3+*sPosition];
	version=reinterpret_cast<long&>(tempChar);
}

class m3dmagic
{
public:
	m3dmagic(char* inputBuffer,int size,int* sPosition,int *ePosition);
	~m3dmagic();
	header* t_header;
	m3dVersion* t_version;
	mdata* t_data;
	std::vector<unknown*> t_unknown;
};

m3dmagic::~m3dmagic()
{
	if(t_header!=NULL)
	{
		delete t_header;
		t_header=NULL;
	}
	if(t_version!=NULL)
	{
		delete t_version;
		t_version=NULL;
	}
	if(t_data!=NULL)
	{
		delete t_data;
		t_data=NULL;
	}
	int i=0;
	while(i<t_unknown.size())
	{
		delete t_unknown[i];
		t_unknown[i]=NULL;
		i++;
	}
	t_unknown.empty();
}

m3dmagic::m3dmagic(char* inputBuffer,int size,int* sPosition,int* ePosition)
{
	t_version=NULL;
	t_data=NULL;
	t_header=new header(inputBuffer,size,sPosition,ePosition);
	int start=*sPosition;
	*sPosition=*ePosition;
	*ePosition=t_header->length+*sPosition-6;
	
	while(*sPosition<*ePosition)
	{
		header tempHeader(inputBuffer,size,sPosition,ePosition);
		//*sPosition=*ePosition;
		*ePosition=t_header->length+start;
		switch(tempHeader.id)
		{
		case 0x0002:
			t_version=new m3dVersion(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			break;
		case 0x3d3d:
			t_data=new mdata(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			break;
		default:
			unknown* tempUnknownPtr=new unknown(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			t_unknown.push_back(tempUnknownPtr);
			break;
		}
		//*ePosition=t_header->length;
	}
}




class studioMaxModel
{
public:
	studioMaxModel();
	~studioMaxModel();
	bool loadFile(char* fileName);
	int getVertexCoordSize();
	bool getVertexCoord(float info[]);
	int getTextCoordSize();
	bool getTextCoord(float info[]);
	int getNumberOfObjects();
	void getObjectFaceLengths(int info[]);
	int getNumberOfNormals();
	bool getNormals(float info[]);
	
	
private:
	std::ifstream file;
	int fileLength;
	char* buffer;
	int* startPosition;
	int* endPosition;
	m3dmagic* pData;
	
};

studioMaxModel::studioMaxModel()
{
	fileLength=0;
	buffer=NULL;
	startPosition=NULL;
	endPosition=NULL;
	pData=NULL;
}

studioMaxModel::~studioMaxModel()
{
	if(buffer!=NULL)
	{
		delete[] buffer;
		buffer=NULL;
	}
	if(startPosition!=NULL)
	{
		delete startPosition;
		startPosition=NULL;
	}
	if(endPosition!=NULL)
	{
		delete endPosition;
		endPosition=NULL;
	}
	if(pData!=NULL)
	{
		delete pData;
		pData=NULL;
	}
}

bool studioMaxModel::loadFile(char* fileName)
{
	file.open(fileName,std::ios::binary|std::ios::ate);
	if(!file.is_open())
	{
		return 0;
	}
	fileLength=file.tellg();
	file.seekg(std::ios::beg);
	buffer = new char[fileLength+1];
	file.read(buffer,fileLength);
	file.close();
	startPosition=new int;
	endPosition=new int;
	*startPosition=0;
	*endPosition=0;
	header tempHeader(buffer,fileLength,startPosition,endPosition);
	if(tempHeader.id!=0x4d4d)
	{
		delete[] buffer;
		buffer=NULL;
		return 0;
	}
	pData=new m3dmagic(buffer,fileLength,startPosition,endPosition);
	delete[] buffer;
	buffer=NULL;
	return 1;
};

int studioMaxModel::getNumberOfNormals()
{
	int count=0;
	for(int m=0;m<=pData->t_data->t_name.size()-1;m++)
	{
		if(pData->t_data->t_name[m]->t_object->t_faceArray!=NULL)
		{
			count+=pData->t_data->t_name[m]->t_object->t_faceArray->numberOfFaces*9;
		}
		else
		{
			count+=0;
		}
	}
	return count;
}

bool studioMaxModel::getNormals(float info[])
{
	int count=0;
	int finalCount=0;
	float temp[9];
	float a[3],b[3],result[3],length;
	for(int m=0;m<=pData->t_data->t_name.size()-1;m++)
	{
	//float test=0;
	//int m=0;
		if(pData->t_data->t_name[m]->t_object->t_faceArray!=NULL)
		{
			for(int i=0;i<=pData->t_data->t_name[m]->t_object->t_faceArray->numberOfFaces-1;i++)
			{
				count=0;
				for(int j=0;j<=2;j++)
				{
					for(int k=0;k<=2;k++)
					{
						if(pData->t_data->t_name[m]->t_object->t_pointArray!=NULL)
						{
							//test=pData->t_data->t_name[0]->t_object->t_faceArray->faceList[(i*4)+j];
							temp[count]=pData->t_data->t_name[m]->t_object->t_pointArray->pointList[pData->t_data->t_name[m]->t_object->t_faceArray->faceList[(i*4)+j]*3+k];
							//test=info[count];
						}
						else
						{
							temp[count]=0;
						}
						count++;
					}

				}

				a[0]=temp[0]-temp[3];
				a[1]=temp[1]-temp[4];
				a[2]=temp[2]-temp[5];

				b[0]=temp[0]-temp[6];
				b[1]=temp[1]-temp[7];
				b[2]=temp[2]-temp[8];

				result[0]=a[1]*b[2]-b[1]*a[2];
				result[1]=b[0]*a[2]-a[0]*b[2];
				result[2]=a[0]*b[1]-b[0]*a[1];

				length=(float)sqrt(result[0]*result[0]+result[1]*result[1]+result[2]*result[2]);


				info[finalCount*9+0]=result[0]/length;
				info[finalCount*9+1]=result[1]/length;
				info[finalCount*9+2]=result[2]/length;
				info[finalCount*9+3]=result[0]/length;
				info[finalCount*9+4]=result[1]/length;
				info[finalCount*9+5]=result[2]/length;
				info[finalCount*9+6]=result[0]/length;
				info[finalCount*9+7]=result[1]/length;
				info[finalCount*9+8]=result[2]/length;




				finalCount++;
			}
		}
	}
	return 1;
}



int studioMaxModel::getNumberOfObjects()
{
	return pData->t_data->t_name.size();
}

void studioMaxModel::getObjectFaceLengths(int info[])
{
	for(int m=0;m<=pData->t_data->t_name.size()-1;m++)
	{
		if(pData->t_data->t_name[m]->t_object->t_faceArray!=NULL)
		{
			info[m]=pData->t_data->t_name[m]->t_object->t_faceArray->numberOfFaces;
		}
		else
		{
			info[m]=0;
		}
	}
}

bool studioMaxModel::getVertexCoord(float info[])
{
	int count=0;
	for(int m=0;m<=pData->t_data->t_name.size()-1;m++)
	{
	//float test=0;
	//int m=0;
		if(pData->t_data->t_name[m]->t_object->t_faceArray!=NULL)
		{
			for(int i=0;i<=pData->t_data->t_name[m]->t_object->t_faceArray->numberOfFaces-1;i++)
			{
				for(int j=0;j<=2;j++)
				{
					for(int k=0;k<=2;k++)
					{
						if(pData->t_data->t_name[m]->t_object->t_pointArray!=NULL)
						{
							//test=pData->t_data->t_name[0]->t_object->t_faceArray->faceList[(i*4)+j];
							info[count]=pData->t_data->t_name[m]->t_object->t_pointArray->pointList[pData->t_data->t_name[m]->t_object->t_faceArray->faceList[(i*4)+j]*3+k];
							//test=info[count];
						}
						else
						{
							info[count]=0;
						}
						count++;
					}
				}
			}
		}
	}
	return 1;
}

bool studioMaxModel::getTextCoord(float info[])
{
	int count=0;
	for(int m=0;m<=pData->t_data->t_name.size()-1;m++)
	{
	//float test=0;
	//int m=0;
		if(pData->t_data->t_name[m]->t_object->t_faceArray!=NULL)
		{
			for(int i=0;i<=pData->t_data->t_name[m]->t_object->t_faceArray->numberOfFaces-1;i++)
			{
				for(int j=0;j<=2;j++)
				{
					for(int k=0;k<=1;k++)
					{
						if(pData->t_data->t_name[m]->t_object->t_textureMap!=NULL)
						{
							//test=pData->t_data->t_name[0]->t_object->t_faceArray->faceList[(i*3)+j];
							info[count]=pData->t_data->t_name[m]->t_object->t_textureMap->mapList[pData->t_data->t_name[m]->t_object->t_faceArray->faceList[(i*4)+j]*2+k];
							//test=info[count];
						}
						else
						{
							info[count]=0;
						}
						count++;
					}
				}
			}
		}
	}
	return 1;
	
}

int studioMaxModel::getTextCoordSize()
{
	int count=0;
	for(int i=0;i<=pData->t_data->t_name.size()-1;i++)
	{
		if(pData->t_data->t_name[i]->t_object->t_faceArray!=NULL)
		{
			count+=pData->t_data->t_name[i]->t_object->t_faceArray->numberOfFaces*6;//numberOfMaps*6;
		}
	}
	return count;
}

int studioMaxModel::getVertexCoordSize()
{
	int count=0;
	for(int i=0;i<=pData->t_data->t_name.size()-1;i++)
	{
	//int i=0;
		if(pData->t_data->t_name[i]->t_object->t_faceArray!=NULL)
		{
			count+=pData->t_data->t_name[i]->t_object->t_faceArray->numberOfFaces*9;
		}
	}
	return count;
}

