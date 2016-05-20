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

class matName
{
public:
	matName(char* inputBuffer,int size,int* sPosition,int* ePosition);
	~matName();
	header* t_header;
	char* name;
};

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
	header* t_header;
	unsigned char t_red;
	unsigned char t_green;
	unsigned char t_blue;
};

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

faceArray::faceArray(char* inputBuffer,int size,int* sPosition,int* ePosition)
{

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

		default:
			unknown* tempUnknownPtr=new unknown(inputBuffer,size,sPosition,ePosition);
			*sPosition=*ePosition;
			*ePosition=t_header->length+start;
			t_unknown.push_back(tempUnknownPtr);
			break;
		}
	}
	
	
}

class nTriObject
{
public:
	nTriObject(char* inputBuffer,int size,int* sPosition,int *ePosition);
	~nTriObject();
	header* t_header;
	pointArray* t_pointArray;
	faceArray* t_faceArray;
	std::vector<mshMatGroup*> t_mshMatGroup;
	std::vector<unknown*> t_unknown;

};

nTriObject::nTriObject(char* inputBuffer,int size,int* sPosition,int* ePosition)
{

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
	header* t_header;
	char* name;
	nTriObject* t_object;

};

namedObject::namedObject(char* inputBuffer,int size,int* sPosition,int* ePosition)
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
	header* t_header;
	float scale;
};

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

matEntry::matEntry(char* inputBuffer,int size,int* sPosition,int* ePosition)
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

mdata::mdata(char* inputBuffer,int size,int* sPosition,int* ePosition)
{

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
	header* t_header;
	long version;
};

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

m3dmagic::m3dmagic(char* inputBuffer,int size,int* sPosition,int* ePosition)
{

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



