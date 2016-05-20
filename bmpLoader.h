// Matthew Applin
// bpmLoader class
#include<fstream>

class bitMapHeader
{
public:
	bitMapHeader(char* inputBuffer,int*sPosition,int* ePosition);
	unsigned short id;
	unsigned long length;
	unsigned long offset;
};

bitMapHeader::bitMapHeader(char* inputBuffer,int* sPosition,int* ePosition)
{
	char tempChar[5];

	for(int i=0;i<=1;i++)
	{
		tempChar[i]=inputBuffer[(*sPosition)++];
	}
	id=reinterpret_cast<short&>(tempChar);

	for(int i=0;i<=3;i++)
	{
		tempChar[i]=inputBuffer[(*sPosition)++];
	}
	length=reinterpret_cast<long&>(tempChar);

	*sPosition+=4;

	for(int i=0;i<=3;i++)
	{
		tempChar[i]=inputBuffer[(*sPosition)++];
	}
	offset=reinterpret_cast<long&>(tempChar);
	*ePosition=*sPosition;
}

class dibHeader
{
public:
	dibHeader(char* inputBuffer,int* sPosition,int* ePosition);
	unsigned long headerSize;
	int width;
	int height;
	unsigned short numColorPlanes;
	unsigned short bitsPerPix;
	long compression;
	unsigned long imageSize;
	int xPixPerMeter;
	int yPixPerMeter;
	long numColorPal;
	long numImpCols;
};

dibHeader::dibHeader(char* inputBuffer,int* sPosition,int* ePosition)
{
	int start=*sPosition;
	char tempChar[5];

	for(int i=0;i<=3;i++)
	{
		tempChar[i]=inputBuffer[(*sPosition)++];
	}
	headerSize=reinterpret_cast<long&>(tempChar);
	*ePosition=start+headerSize;

	for(int i=0;i<=3;i++)
	{
		tempChar[i]=inputBuffer[(*sPosition)++];
	}
	width=reinterpret_cast<int&>(tempChar);

	for(int i=0;i<=3;i++)
	{
		tempChar[i]=inputBuffer[(*sPosition)++];
	}
	height=reinterpret_cast<int&>(tempChar);

	for(int i=0;i<=1;i++)
	{
		tempChar[i]=inputBuffer[(*sPosition)++];
	}
	numColorPlanes=reinterpret_cast<short&>(tempChar);

	for(int i=0;i<=1;i++)
	{
		tempChar[i]=inputBuffer[(*sPosition)++];
	}
	bitsPerPix=reinterpret_cast<short&>(tempChar);

	for(int i=0;i<=3;i++)
	{
		tempChar[i]=inputBuffer[(*sPosition)++];
	}
	compression=reinterpret_cast<long&>(tempChar);

	for(int i=0;i<=3;i++)
	{
		tempChar[i]=inputBuffer[(*sPosition)++];
	}
	imageSize=reinterpret_cast<long&>(tempChar);

	for(int i=0;i<=3;i++)
	{
		tempChar[i]=inputBuffer[(*sPosition)++];
	}
	xPixPerMeter=reinterpret_cast<int&>(tempChar);

	for(int i=0;i<=3;i++)
	{
		tempChar[i]=inputBuffer[(*sPosition)++];
	}
	yPixPerMeter=reinterpret_cast<int&>(tempChar);

	for(int i=0;i<=3;i++)
	{
		tempChar[i]=inputBuffer[(*sPosition)++];
	}
	numColorPal=reinterpret_cast<long&>(tempChar);

	for(int i=0;i<=3;i++)
	{
		tempChar[i]=inputBuffer[(*sPosition)++];
	}
	numImpCols=reinterpret_cast<long&>(tempChar);
}






class bmpLoader
{
public:
	bmpLoader();
	~bmpLoader();
	bool loadFile(char* info);
	unsigned char* getData();
	int getSizeOfData();
	int getWidth();
	int getHeigth();
	int getColorBits();
	void reverseRGB();
private:
	std::ifstream file;
	bitMapHeader* t_bitMapHeader;
	dibHeader* t_dibHeader;
	unsigned char* t_data;
	char* buffer;
	int fileSize;
	int* startPosition;
	int* endPosition;
	int padding;
	int imageSize;
	int numOfColorBits;
};

bmpLoader::bmpLoader()
{
	t_bitMapHeader=NULL;
	t_dibHeader=NULL;
	t_data=NULL;
	buffer=NULL;
	startPosition=NULL;
	endPosition=NULL;
	fileSize=0;
	padding=0;
	imageSize=0;
	numOfColorBits=0;
}
bmpLoader::~bmpLoader()
{
	if(t_bitMapHeader!=NULL)
	{
		delete t_bitMapHeader;
		t_bitMapHeader=NULL;
	}
	if(t_dibHeader!=NULL)
	{
		delete t_dibHeader;
		t_dibHeader=NULL;
	}
	if(t_data!=NULL)
	{
		delete t_data;
		t_data=NULL;
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
}

void bmpLoader::reverseRGB()
{
	
	
	for(int i=0;i<=imageSize;i+=numOfColorBits)
	{
		unsigned char temp=t_data[i];
		t_data[i]=t_data[i+2];
		t_data[i+2]=temp;
	}
}

int bmpLoader::getColorBits()
{
	return numOfColorBits;
}
int bmpLoader::getWidth()
{
	return t_dibHeader->width;
}

int bmpLoader::getHeigth()
{
	return t_dibHeader->height;
}

int bmpLoader::getSizeOfData()
{
	return imageSize;
}

unsigned char* bmpLoader::getData()
{
	return t_data;
}



bool bmpLoader::loadFile(char* fileName)
{
	file.open(fileName,std::ios::binary|std::ios::ate);
	if(!file.is_open())
	{
		return 0;
	}
	fileSize=file.tellg();
	file.seekg(std::ios::beg);
	buffer=new char[fileSize+1];
	file.read(buffer,fileSize);
	file.close();
	startPosition=new int;
	endPosition=new int;
	*startPosition=0;
	*endPosition=0;
	int start=0;

	t_bitMapHeader=new bitMapHeader(buffer,startPosition,endPosition);
	*startPosition=*endPosition;
	*endPosition=fileSize;

	t_dibHeader=new dibHeader(buffer,startPosition,endPosition);
	

	*startPosition=t_bitMapHeader->offset;
	*endPosition=fileSize;
	imageSize=t_bitMapHeader->length-t_bitMapHeader->offset;
	numOfColorBits=t_dibHeader->bitsPerPix/8;

	float tempWidth=t_dibHeader->width;
	float tempHeight=t_dibHeader->height;
	float tempLength=imageSize;
	float tempPadding=(((tempLength/numOfColorBits)/tempHeight)-tempWidth)*numOfColorBits;
	padding=tempPadding;
	unsigned char tempcharington;

	t_data=new unsigned char[imageSize];//+2*t_dibHeader->height+1];

	for(int j=0;j<=t_dibHeader->height-1;j++)
	{
		for(int i=0;i<=t_dibHeader->width*numOfColorBits+padding-1;i++)
		{
			t_data[(j*t_dibHeader->width*numOfColorBits+padding)+i]=buffer[(*startPosition)++];
			tempcharington=t_data[(j*t_dibHeader->width*numOfColorBits+padding)+i];
		}
	}
	
	delete[] buffer;
	buffer=NULL;

	return 1;
}


