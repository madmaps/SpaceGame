// Matthew Applin
// gameEngine class


#define PLANET 0x00
#define SHIP 0x01
#define PROJECTILE 0x02
#define MENU 0x03
#define COCKPIT 0x04
#define BACKGROUND 0x05
#define OTHER 0x09

class gameEngine
{
public:
	bool loadModels(char* info,int type);
	bool loadTextures(char* info,int type);
	bool loadShipTypes(char* info);
	bool loadEngineTypes(char* info);
	bool loadGunTypes(char* info);
	bool loadTurnThrusterTypes(char* info);
	bool loadShieldTypes(char* info);
	bool loadEnergyDistributerTypes(char* info);
	bool loadSolarRechargerTypes(char* info);
	void addPlayer(player& info);
	void addShipToPlayer(int playerInt,int info);
	void addEngineToPlayer(int playerInt,int info);
	void addGunToPlayer(int playerInt,int info);
	void addTurnThrusterToPlayer(int playerInt,int info);
	void addShieldToPlayer(int playerInt,int info);
	void addEngergyDistributerToPlayer(int playerInt,int info);
	void addSolarRechargerToPlayer(int playerInt,int info);
	void draw();
	void setMainPlayer(int info);
	void setCockpit(int info,int text);
	void setBackground(int info,int text);
	void setTime(const double& info);
	void update();
	void addGalaxy(galaxy* info);
	void createPlanets();
	void checkCollisions();

	//bool frustum(

	std::vector<player*> t_players;
private:
	int mainPlayer;
	double timeChange;
	
	
	std::vector<planet*> t_planets;
	std::vector<projectile> t_projectiles;
	//std::vector<menu*> t_menu;
	std::vector<s_object*> t_cockpit;
	std::vector<s_object*> t_background;

	std::vector<model*> t_planetModels;
	std::vector<model*> t_shipModels;
	std::vector<model*> t_projectileModels;
	std::vector<model*> t_menuModels;
	std::vector<model*> t_cockpitModels;
	std::vector<model*> t_backgroundModels;
	std::vector<model*> t_otherModels;

	std::vector<shipType> t_shipType;
	std::vector<engineType> t_engineType;
	std::vector<gunType> t_gunType;
	std::vector<turnThrusterType> t_turnThrusterType;
	std::vector<shieldType> t_shieldType;
	std::vector<energyDistributerType> t_energyDistributerType;
	std::vector<solarRechargerType> t_solarRechargerType;

	int numberOfPlanetTextures;
	unsigned int* t_planetTextures;
	bmpLoader* t_planetTextureFile;
	int numberOfShipTextures;
	unsigned int* t_shipTextures;
	bmpLoader* t_shipTextureFile;
	int numberOfMenuTextures;
	unsigned int* t_menuTextures;
	bmpLoader* t_menuTextureFile;
	int numberOfOtherTextures;
	unsigned int* t_otherTextures;
	bmpLoader* t_otherTextureFile;
	int numberOfCockpitTextures;
	unsigned int* t_cockpitTextures;
	bmpLoader* t_cockpitTextureFile;
	int numberOfBackgroundTextures;
	unsigned int* t_backgroundTextures;
	bmpLoader* t_backgroundTextureFile;
	int numberOfProjectileTextures;
	unsigned int* t_projectileTextures;
	bmpLoader* t_projectileTextureFile;

	galaxy* t_galaxy;
	frustum t_frustum;

	collision t_collision;
	
};

void gameEngine::checkCollisions()
{
	double tempPrevLoc[4];
	double tempPrevLoc2[4];
	double tempNewLoc[4];
	double tempNewLoc2[4];
	double collisionX,collisionY,collisionZ;
	int i=0;
	int k=-1,u=-1,m=-1;
	int tempX,tempY,tempZ;


	while(i<t_players.size())
	{
		m=-1;
		while(m<2)
		{
			u=-1;
			while(u<2)
			{
				k=-1;
				while(k<2)
				{
					tempX=t_players[i]->t_ship.getSectorX()+k;
					if(tempX>t_galaxy->getWidth()-1)
					{
						tempX=0;
					}
					if(tempX<0)
					{
						tempX=t_galaxy->getWidth()-1;
					}
					tempZ=t_players[i]->t_ship.getSectorZ()+u;
					if(tempZ>t_galaxy->getDepth()-1)
					{
						tempZ=0;
					}
					if(tempZ<0)
					{
						tempZ=t_galaxy->getDepth()-1;
					}
					tempY=t_players[i]->t_ship.getSectorY()+m;
					if(tempY>t_galaxy->getHeight()-1)
					{
						tempY=0;
					}
					if(tempY<0)
					{
						tempY=t_galaxy->getHeight()-1;
					}



					//if(i!=mainPlayer && t_players[i]->t_ship.getSectorX()==tempX && t_players[i]->t_ship.getSectorY()==tempY && t_players[i]->t_ship.getSectorZ()==tempZ)
					//{
					//	t_players[i]->t_ship.getLocation(tempLocSect);
					//	t_players[i]->t_ship.setLocation(tempLocSect[0]+(t_galaxy->getSectorSize()*k),tempLocSect[1]+(t_galaxy->getSectorSize()*m),tempLocSect[2]+(t_galaxy->getSectorSize()*j));
					//	if(t_frustum.frustumCheck(tempLocSect[0]+(t_galaxy->getSectorSize()*k),tempLocSect[1]+(t_galaxy->getSectorSize()*m),tempLocSect[2]+(t_galaxy->getSectorSize()*j),t_players[i]->t_ship.getShipType()->shipRadius))
					//	{
					//		t_players[i]->t_ship.draw();
					//	}
					//	t_players[i]->t_ship.setLocation(tempLocSect);
					//}
					//i++;
				

					int j=i+1;
					//while(j<t_players.size())
					//{
					//	if(t_players[j]->t_ship.getSectorX()==tempX && t_players[j]->t_ship.getSectorY()==tempY && t_players[j]->t_ship.getSectorZ()==tempZ)
					//	{
					//		t_players[i]->t_ship.getPrevLocation(tempPrevLoc);
					//		t_players[j]->t_ship.getPrevLocation(tempPrevLoc2);
					//		t_players[j]->t_ship.setPrevLocation(tempPrevLoc2[0]+(t_galaxy->getSectorSize()*k),tempPrevLoc2[1]+(t_galaxy->getSectorSize()*m),tempPrevLoc2[2]+(t_galaxy->getSectorSize()*u));
					//		t_players[i]->t_ship.getLocation(tempNewLoc);
					//		t_players[j]->t_ship.getLocation(tempNewLoc2);
					//		t_players[j]->t_ship.setLocation(tempNewLoc2[0]+(t_galaxy->getSectorSize()*k),tempNewLoc2[1]+(t_galaxy->getSectorSize()*m),tempNewLoc2[2]+(t_galaxy->getSectorSize()*u));
					//		if(t_collision.detect(tempPrevLoc[0],tempPrevLoc[1],tempPrevLoc[2],tempPrevLoc2[0],tempPrevLoc2[1],tempPrevLoc2[2],tempNewLoc[0],tempNewLoc[1],tempNewLoc[2],1,tempNewLoc2[0],tempNewLoc2[1],tempNewLoc2[2],1,collisionX,collisionY,collisionZ))
					//		{
					//			PlaySound(TEXT("c:/test/sound.wav"),NULL,SND_FILENAME|SND_ASYNC);
					//		}
					//		t_players[j]->t_ship.setPrevLocation(tempPrevLoc2);
					//		t_players[j]->t_ship.setLocation(tempNewLoc2);
					//	}


					//	j++;
					//}

					j=0;
					while(j<t_projectiles.size())
					{
						if(t_projectiles[j].getSectorX()==tempX && t_projectiles[j].getSectorY()==tempY && t_projectiles[j].getSectorZ()==tempZ)
						{
							t_players[i]->t_ship.getPrevLocation(tempPrevLoc);
							t_players[i]->t_ship.getLocation(tempNewLoc);

							t_projectiles[j].getPrevLocation(tempPrevLoc2);
							t_projectiles[j].getLocation(tempNewLoc2);
							if(t_collision.detect(tempPrevLoc[0],tempPrevLoc[1],tempPrevLoc[2],tempPrevLoc2[0]+(t_galaxy->getSectorSize()*k),tempPrevLoc2[1]+(t_galaxy->getSectorSize()*m),tempPrevLoc2[2]+(t_galaxy->getSectorSize()*u),tempNewLoc[0],tempNewLoc[1],tempNewLoc[2],1,tempNewLoc2[0]+(t_galaxy->getSectorSize()*k),tempNewLoc2[1]+(t_galaxy->getSectorSize()*m),tempNewLoc2[2]+(t_galaxy->getSectorSize()*u),.5,collisionX,collisionY,collisionZ))
							{
								t_players[i]->t_ship.recieveDamage(t_projectiles[j].getDamage());
								t_projectiles[j].setDone();
								PlaySound(TEXT("c:/test/sound.wav"),NULL,SND_FILENAME|SND_ASYNC);
							}
						}
						j++;
					}

					//j=0;
					//while(j<t_projectiles.size())
					//{
					//	t_players[i]->t_ship.getPrevLocation(tempPrevLoc);
					//	t_players[i]->t_ship.getLocation(tempNewLoc);
					//	t_projectiles[j].getPrevLocation(tempPrevLoc2);
					//	t_projectiles[j].getLocation(tempNewLoc2);
					//	if(t_collision.detect(tempPrevLoc[0],tempPrevLoc[1],tempPrevLoc[2],tempPrevLoc2[0],tempPrevLoc2[1],tempPrevLoc2[2],tempNewLoc[0],tempNewLoc[1],tempNewLoc[2],1,tempNewLoc2[0],tempNewLoc2[1],tempNewLoc2[2],.5,collisionX,collisionY,collisionZ))
					//	{
					//		//create small Explosion at collision x,y,z
					//		t_players[i]->t_ship.recieveDamage(t_projectiles[j].getDamage());
					//		t_projectiles[j].setDone();
					//		PlaySound(TEXT("c:/test/sound.wav"),NULL,SND_FILENAME|SND_ASYNC);
					//	}
					//	j++;
					//}
					j=0;
					while(j<t_planets.size())
					{
						if(t_planets[j]->getSectorX()==tempX && t_planets[j]->getSectorY()==tempY && t_planets[j]->getSectorZ()==tempZ)
						{
							t_players[i]->t_ship.getPrevLocation(tempPrevLoc);
							t_players[i]->t_ship.getLocation(tempNewLoc);

							t_planets[j]->getPrevLocation(tempPrevLoc2);
							t_planets[j]->getLocation(tempNewLoc2);
							if(t_collision.detect(tempPrevLoc[0],tempPrevLoc[1],tempPrevLoc[2],tempPrevLoc2[0]+(t_galaxy->getSectorSize()*k),tempPrevLoc2[1]+(t_galaxy->getSectorSize()*m),tempPrevLoc2[2]+(t_galaxy->getSectorSize()*u),tempNewLoc[0],tempNewLoc[1],tempNewLoc[2],2,tempNewLoc2[0]+(t_galaxy->getSectorSize()*k),tempNewLoc2[1]+(t_galaxy->getSectorSize()*m),tempNewLoc2[2]+(t_galaxy->getSectorSize()*u),150,collisionX,collisionY,collisionZ))
							{
								t_players[i]->t_ship.setLocation((collisionX-tempNewLoc2[0])*1.01+tempNewLoc2[0],(collisionY-tempNewLoc2[1])*1.01+tempNewLoc2[1],(collisionZ-tempNewLoc2[2])*1.01+tempNewLoc2[2]);
								t_players[i]->t_ship.setShipSpeed(0);
							}
						}
						j++;
					}
					k++;
				}
				u++;
			}
			m++;
		}
		i++;
	}
}


void gameEngine::createPlanets()
{
	
	//sectorX,sectorY,sectorZ,LocationX,LocationY,LocationZ,model,texture
	std::mt19937 eng(static_cast<unsigned long>(time(nullptr)));
	std::uniform_int_distribution<int> sectX(0,t_galaxy->getWidth()-1);
	std::uniform_int_distribution<int> sectY(0,t_galaxy->getHeight()-1);
	std::uniform_int_distribution<int> sectZ(0,t_galaxy->getDepth()-1);
	std::uniform_int_distribution<int> loc(0,t_galaxy->getSectorSize()-1);
	std::uniform_int_distribution<int> mod(0,t_planetModels.size()-1);
	std::uniform_int_distribution<int> text(0,numberOfPlanetTextures-1);

	planet* theTempPlanet;
	int x,y,z;
	int i=0;
	while(i<t_galaxy->getNumberOfPlanets()-1)
	{
		theTempPlanet=new planet;
		theTempPlanet->setMaxSectors(t_galaxy->getWidth(),t_galaxy->getHeight(),t_galaxy->getDepth(),t_galaxy->getSectorSize());
		theTempPlanet->setSector(sectX(eng),sectY(eng),sectZ(eng));
		x=loc(eng);
		y=loc(eng);
		z=loc(eng);
		theTempPlanet->setPrevLocation(x,y,z);
		theTempPlanet->setLocation(x,y,z);
		theTempPlanet->addModel(*t_planetModels[mod(eng)]);
		theTempPlanet->addTextures(&t_planetTextures[text(eng)],1);
		t_planets.push_back(theTempPlanet);
		i++;
	}

	




	
	//std::uniform_int_distribution<int> dist(0,1000);
	//double Degrees=360/(dist(eng));
}

void gameEngine::addGalaxy(galaxy* info)
{
	t_galaxy=info;
}

void gameEngine::setTime(const double& info)
{
	timeChange=info;
}

void gameEngine::setCockpit(int info,int text)
{
	s_object* tempCockpit=new s_object;
	t_cockpit.push_back(tempCockpit);
	t_cockpit[0]->addModel(*t_cockpitModels[info]);
	t_cockpit[0]->addTextures(t_planetTextures,1);
}

void gameEngine::setBackground(int info,int text)
{
	s_object* tempBackground=new s_object;
	t_background.push_back(tempBackground);

	t_background[0]->addModel(*t_backgroundModels[info]);
	t_background[0]->addTextures(t_backgroundTextures,1);
}

void gameEngine::update()
{
	int i=0;
	while(i<t_planets.size())
	{
		t_planets[i]->setTime(timeChange);
		t_planets[i]->update();
		i++;
	}
		
	i=0;
	while(i<t_players.size())
	{
		t_players[i]->t_ship.setTime(timeChange);
		t_players[i]->t_ship.update();
		if(t_players[i]->t_ship.getHullStrength()<0)
		{
			t_players[i]->t_ship.setHullStrength(t_players[i]->t_ship.getShipType()->hullStrength);
			//create Explosion at ship Location
			PlaySound(TEXT("c:/test/explosion.wav"),NULL,SND_FILENAME|SND_ASYNC);
		}

		i++;
	}
	int tempCount;
	int k=0;
	i=0;
	while(i<t_players.size())
	{
		tempCount=t_players[i]->t_ship.hasFired(t_projectiles);
		if(tempCount>0)
		{
			k=t_projectiles.size()-1;
			int tempShit=(t_projectiles.size()-tempCount)-1;
			while(k>tempShit)
			{
				t_projectiles[k].addModel(*t_projectileModels[0]);
				t_projectiles[k].addTextures(&t_projectileTextures[0],1);
				k--;
			}
		}
		i++;
	}
	int j=0;
	i=0;
	while(i<t_projectiles.size())
	{
		t_projectiles[i].setTime(timeChange);
		t_projectiles[i].update();

		if(t_projectiles[i].isDone())
		{
			j=i;
			while(j<=t_projectiles.size()-2 && t_projectiles.size()>1)
			{
				t_projectiles[j]=t_projectiles[j+1];
				j++;
			}
			t_projectiles.pop_back();
			i--;
		}



		i++;
	}

	//t_background[0]->update();
	
	//i=0;
	//while(i<t_menu.size())
	//{
	//	if(t_menu[i]->disabled())
	//	{
	//		t_menu[i]->update()
	//	}
	//	i++;
	//}
}


void gameEngine::setMainPlayer(int info)
{
	mainPlayer=info;
}

void gameEngine::draw()
{
	
	double tempArrOrient[16];
	double tempArrLoc[4];
	GLfloat white[]={1,1,1,1};
	GLfloat lightDir[]={1,0,0,0};
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     
	glLoadIdentity();
	glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,white);

	glPushMatrix();
	glTranslatef(0,-1,-4);
	t_cockpit[0]->draw();
	glPopMatrix();

	glBegin(GL_LINES);
			glVertex3f(-.3,0,-10);
			glVertex3f(.3,0,-10);
			glVertex3f(0,-.3,-10);
			glVertex3f(0,.3,-10);
			glVertex3f(0,.3,-10);
			glVertex3f(-.3,0,-10);
			glVertex3f(-.3,0,-10);
			glVertex3f(0,-.3,-10);
			glVertex3f(0,-.3,-10);
			glVertex3f(.3,0,-10);
			glVertex3f(.3,0,-10);
			glVertex3f(0,.3,-10);
	glEnd();

	glPushMatrix();

	t_players[mainPlayer]->t_ship.getLocation(tempArrLoc);
	t_players[mainPlayer]->t_ship.getOrientation(tempArrOrient);
	glMultMatrixd(tempArrOrient);
	glTranslatef(-tempArrLoc[0],-tempArrLoc[1],-tempArrLoc[2]);
	glLightfv(GL_LIGHT0,GL_POSITION,lightDir);

	t_frustum.update();


	
	
	int k=-1,j=-1,m=-1,i=0;
	int planetCount=0;
	int tempX,tempY,tempZ;
	double tempLocSect[4];
	while(m<2)
	{
		j=-1;
		while(j<2)
		{
			k=-1;
			while(k<2)
			{
				tempX=t_players[mainPlayer]->t_ship.getSectorX()+k;
				if(tempX>t_galaxy->getWidth()-1)
				{
					tempX=0;
				}
				if(tempX<0)
				{
					tempX=t_galaxy->getWidth()-1;
				}
				tempZ=t_players[mainPlayer]->t_ship.getSectorZ()+j;
				if(tempZ>t_galaxy->getDepth()-1)
				{
					tempZ=0;
				}
				if(tempZ<0)
				{
					tempZ=t_galaxy->getDepth()-1;
				}
				tempY=t_players[mainPlayer]->t_ship.getSectorY()+m;
				if(tempY>t_galaxy->getHeight()-1)
				{
					tempY=0;
				}
				if(tempY<0)
				{
					tempY=t_galaxy->getHeight()-1;
				}
				

				i=0;
				while(i<t_players.size())
				{
					if(i!=mainPlayer && t_players[i]->t_ship.getSectorX()==tempX && t_players[i]->t_ship.getSectorY()==tempY && t_players[i]->t_ship.getSectorZ()==tempZ)
					{
						t_players[i]->t_ship.getLocation(tempLocSect);
						t_players[i]->t_ship.setLocation(tempLocSect[0]+(t_galaxy->getSectorSize()*k),tempLocSect[1]+(t_galaxy->getSectorSize()*m),tempLocSect[2]+(t_galaxy->getSectorSize()*j));
						if(t_frustum.frustumCheck(tempLocSect[0]+(t_galaxy->getSectorSize()*k),tempLocSect[1]+(t_galaxy->getSectorSize()*m),tempLocSect[2]+(t_galaxy->getSectorSize()*j),t_players[i]->t_ship.getShipType()->shipRadius))
						{
							t_players[i]->t_ship.draw();
						}
						t_players[i]->t_ship.setLocation(tempLocSect);
					}
					i++;
				}
				i=0;
				while(i<t_planets.size())
				{
					if(t_planets[i]->getSectorX()==tempX && t_planets[i]->getSectorY()==tempY && t_planets[i]->getSectorZ()==tempZ)
					{
						t_planets[i]->getLocation(tempLocSect);
						t_planets[i]->setLocation(tempLocSect[0]+(t_galaxy->getSectorSize()*k),tempLocSect[1]+(t_galaxy->getSectorSize()*m),tempLocSect[2]+(t_galaxy->getSectorSize()*j));
						if(t_frustum.frustumCheck(tempLocSect[0]+(t_galaxy->getSectorSize()*k),tempLocSect[1]+(t_galaxy->getSectorSize()*m),tempLocSect[2]+(t_galaxy->getSectorSize()*j),100))
						{
							
							t_planets[i]->draw();
						}
						t_planets[i]->setLocation(tempLocSect);
					}
					i++;
				}
				i=0;
				while(i<t_projectiles.size())
				{
					if(t_projectiles[i].getSectorX()==tempX && t_projectiles[i].getSectorY()==tempY && t_projectiles[i].getSectorZ()==tempZ)
					{
						t_projectiles[i].getLocation(tempLocSect);
						t_projectiles[i].setLocation(tempLocSect[0]+(t_galaxy->getSectorSize()*k),tempLocSect[1]+(t_galaxy->getSectorSize()*m),tempLocSect[2]+(t_galaxy->getSectorSize()*j));
						if(t_frustum.frustumCheck(tempLocSect[0]+(t_galaxy->getSectorSize()*k),tempLocSect[1]+(t_galaxy->getSectorSize()*m),tempLocSect[2]+(t_galaxy->getSectorSize()*j),5))
						{
							
							t_projectiles[i].draw();
						}
						t_projectiles[i].setLocation(tempLocSect);
					}
					i++;
				}


				k++;
			}
			j++;
		}
		m++;
	}

	//i=0;
	//while(i<t_projectiles.size())
	//{
	//	//t_projectiles[i]->draw();
	//	i++;
	//}
	glFrontFace(GL_CW);
	glDisable(GL_LIGHTING);
	t_background[0]->setLocation(tempArrLoc[0],tempArrLoc[1],tempArrLoc[2]);
	t_background[0]->draw();
	glEnable(GL_LIGHTING);
	glFrontFace(GL_CCW);

	glPopMatrix();
	
	//i=0;
	//while(i<t_menu.size())
	//{
	//	if(t_menu[i]->disabled())
	//	{
	//		t_menu[i]->draw()
	//	}
	//	i++;
	//}
		
	
	
}


void gameEngine::addShipToPlayer(int playerInt,int info)
{
	t_players[playerInt]->t_ship.addShipType(t_shipType[info]);
	t_players[playerInt]->t_ship.addModel(*t_shipModels[t_shipType[info].model]);
	int i=0;
	unsigned int tempTex[10];
	while(t_shipType[info].numberOfTextures>i)
	{
		tempTex[i]=t_shipTextures[t_shipType[info].textures[i]];
		i++;
	}

		t_players[playerInt]->t_ship.addTextures(tempTex,t_shipType[info].numberOfTextures);
}

void gameEngine::addEngineToPlayer(int playerInt,int info)
{
	t_players[playerInt]->t_ship.addEngine(t_engineType[info]);
}

void gameEngine::addGunToPlayer(int playerInt,int info)
{
	t_players[playerInt]->t_ship.addGun(t_gunType[info]);
}

void gameEngine::addTurnThrusterToPlayer(int playerInt,int info)
{
	t_players[playerInt]->t_ship.addTurnThruster(t_turnThrusterType[info]);
}

void gameEngine::addShieldToPlayer(int playerInt,int info)
{
	t_players[playerInt]->t_ship.addShield(t_shieldType[info]);
}

void gameEngine::addEngergyDistributerToPlayer(int playerInt,int info)
{
	t_players[playerInt]->t_ship.addEnergyDistributer(t_energyDistributerType[info]);
}

void gameEngine::addSolarRechargerToPlayer(int playerInt, int info)
{
	t_players[playerInt]->t_ship.addSolarRecharger(t_solarRechargerType[info]);
}

void gameEngine::addPlayer(player& info)
{
	info.t_ship.setMaxSectors(t_galaxy->getWidth(),t_galaxy->getHeight(),t_galaxy->getDepth(),t_galaxy->getSectorSize());
	t_players.push_back(&info);
}


bool gameEngine::loadSolarRechargerTypes(char* info)
{
	std::ifstream file;
	file.open(info,std::ios::in);
	if(!file.is_open())
	{
		return 0;
	}

	char buffer[300]={};
	char miniBuffer[30];
	solarRechargerType* tempSolarRechargerType=new solarRechargerType;
	int i=0;

	while(!file.eof())
	{
		file >> buffer;
		i=0;
		int counter=0;
		int dataType=0;
		for(int k=0;k<=18;k++)
		{
			while(buffer[i]!=',' && buffer[i]!=NULL)
			{
				miniBuffer[counter]=buffer[i];
				i++;
				counter++;
			}
			miniBuffer[counter]=NULL;
			switch(dataType)
			{
			case 0:
				tempSolarRechargerType->name=new char[i+1];
				for(int j=0;j<=i;j++)
				{
					tempSolarRechargerType->name[j]=miniBuffer[j];
				}
				break;
			case 1:
				tempSolarRechargerType->solarRechargerClass=atoi(miniBuffer);
				break;
			case 2:
				tempSolarRechargerType->rechargeRate=atof(miniBuffer);
				break;
			case 3:
				tempSolarRechargerType->price=atoi(miniBuffer);
				break;
			default:
				break;
			}
			i++;
			counter=0;
			dataType++;
		}

		t_solarRechargerType.push_back(*tempSolarRechargerType);
	}
	delete tempSolarRechargerType;
	tempSolarRechargerType=NULL;
	file.close();
	return 1;
}


bool gameEngine::loadEnergyDistributerTypes(char* info)
{
	std::ifstream file;
	file.open(info,std::ios::in);
	if(!file.is_open())
	{
		return 0;
	}

	char buffer[300]={};
	char miniBuffer[30];
	energyDistributerType* tempEnergyDistributerType=new energyDistributerType;
	int i=0;

	while(!file.eof())
	{
		file >> buffer;
		i=0;
		int counter=0;
		int dataType=0;
		for(int k=0;k<=18;k++)
		{
			while(buffer[i]!=',' && buffer[i]!=NULL)
			{
				miniBuffer[counter]=buffer[i];
				i++;
				counter++;
			}
			miniBuffer[counter]=NULL;
			switch(dataType)
			{
			case 0:
				tempEnergyDistributerType->name=new char[i+1];
				for(int j=0;j<=i;j++)
				{
					tempEnergyDistributerType->name[j]=miniBuffer[j];
				}
				break;
			case 1:
				tempEnergyDistributerType->energyDistributerClass=atoi(miniBuffer);
				break;
			case 2:
				tempEnergyDistributerType->capacity=atoi(miniBuffer);
				break;
			case 3:
				tempEnergyDistributerType->price=atoi(miniBuffer);
				break;
			default:
				break;
			}
			i++;
			counter=0;
			dataType++;
		}

		t_energyDistributerType.push_back(*tempEnergyDistributerType);
	}
	delete tempEnergyDistributerType;
	tempEnergyDistributerType=NULL;
	file.close();
	return 1;
}

bool gameEngine::loadShieldTypes(char* info)
{
	std::ifstream file;
	file.open(info,std::ios::in);
	if(!file.is_open())
	{
		return 0;
	}

	char buffer[300]={};
	char miniBuffer[30];
	shieldType* tempShieldType=new shieldType;
	int i=0;

	while(!file.eof())
	{
		file >> buffer;
		i=0;
		int counter=0;
		int dataType=0;
		for(int k=0;k<=18;k++)
		{
			while(buffer[i]!=',' && buffer[i]!=NULL)
			{
				miniBuffer[counter]=buffer[i];
				i++;
				counter++;
			}
			miniBuffer[counter]=NULL;
			switch(dataType)
			{
			case 0:
				tempShieldType->name=new char[i+1];
				for(int j=0;j<=i;j++)
				{
					tempShieldType->name[j]=miniBuffer[j];
				}
				break;
			case 1:
				tempShieldType->shieldClass=atoi(miniBuffer);
				break;
			case 2:
				tempShieldType->strength=atof(miniBuffer);
				break;
			case 3:
				tempShieldType->regeneratetionRate=atof(miniBuffer);
				break;
			case 4:
				tempShieldType->restoreTime=atof(miniBuffer);
				break;
			case 5:
				tempShieldType->energyDraw=atof(miniBuffer);
				break;
			case 6:
				tempShieldType->price=atoi(miniBuffer);
				break;
			default:
				break;
			}
			i++;
			counter=0;
			dataType++;
		}

		t_shieldType.push_back(*tempShieldType);
	}
	delete tempShieldType;
	tempShieldType=NULL;
	file.close();
	return 1;
}


bool gameEngine::loadTurnThrusterTypes(char* info)
{
	std::ifstream file;
	file.open(info,std::ios::in);
	if(!file.is_open())
	{
		return 0;
	}

	char buffer[300]={};
	char miniBuffer[30];
	turnThrusterType* tempTurnThrusterType=new turnThrusterType;
	int i=0;

	while(!file.eof())
	{
		file >> buffer;
		i=0;
		int counter=0;
		int dataType=0;
		for(int k=0;k<=18;k++)
		{
			while(buffer[i]!=',' && buffer[i]!=NULL)
			{
				miniBuffer[counter]=buffer[i];
				i++;
				counter++;
			}
			miniBuffer[counter]=NULL;
			switch(dataType)
			{
			case 0:
				tempTurnThrusterType->name=new char[i+1];
				for(int j=0;j<=i;j++)
				{
					tempTurnThrusterType->name[j]=miniBuffer[j];
				}
				break;
			case 1:
				tempTurnThrusterType->thrusterClass=atoi(miniBuffer);
				break;
			case 2:
				tempTurnThrusterType->yawRateOfTurn=atof(miniBuffer);
				break;
			case 3:
				tempTurnThrusterType->pitchRateOfTurn=atof(miniBuffer);
				break;
			case 4:
				tempTurnThrusterType->rollRateOfTurn=atof(miniBuffer);
				break;
			case 5:
				tempTurnThrusterType->responseTime=atof(miniBuffer);
				break;
			case 6:
				tempTurnThrusterType->energyDraw=atof(miniBuffer);
				break;
			case 7:
				tempTurnThrusterType->price=atoi(miniBuffer);
				break;

			default:
				break;
			}
			i++;
			counter=0;
			dataType++;
		}

		t_turnThrusterType.push_back(*tempTurnThrusterType);
	}
	delete tempTurnThrusterType;
	tempTurnThrusterType=NULL;
	file.close();
	return 1;
}

bool gameEngine::loadGunTypes(char* info)
{
	std::ifstream file;
	file.open(info,std::ios::in);
	if(!file.is_open())
	{
		return 0;
	}

	char buffer[300]={};
	char miniBuffer[30];
	gunType* tempGunType=new gunType;
	int i=0;
	double tempFloat[4]={};

	while(!file.eof())
	{
		file >> buffer;
		i=0;
		int counter=0;
		int dataType=0;
		
		for(int k=0;k<=18;k++)
		{
			while(buffer[i]!=',' && buffer[i]!=NULL)
			{
				miniBuffer[counter]=buffer[i];
				i++;
				counter++;
			}
			miniBuffer[counter]=NULL;
			switch(dataType)
			{
			case 0:
				tempGunType->name=new char[i+1];
				for(int j=0;j<=i;j++)
				{
					tempGunType->name[j]=miniBuffer[j];
				}
				break;
			case 1:
				tempGunType->gunClass=atoi(miniBuffer);
				break;
			case 2:
				tempGunType->damagePotential=atoi(miniBuffer);
				break;
			case 3:
				tempGunType->rateOfFire=atof(miniBuffer);
				break;
			case 4:
				tempGunType->projectileSpeed=atof(miniBuffer);
				break;
			case 5:
				tempGunType->projectileRange=atof(miniBuffer);
				break;
			case 6:
				tempGunType->energyDraw=atof(miniBuffer);
				break;
			case 7:
				tempGunType->price=atoi(miniBuffer);
				break;
			case 8:
				tempFloat[0]=atof(miniBuffer);
				break;
			case 9:
				tempFloat[1]=atof(miniBuffer);
				break;
			case 10:
				tempFloat[2]=atof(miniBuffer);
				break;

			default:
				break;
			}
			i++;
			counter=0;
			dataType++;
		}
		tempGunType->location.setMatrix(4,1,tempFloat);

		t_gunType.push_back(*tempGunType);
	}
	delete tempGunType;
	tempGunType=NULL;
	file.close();
	return 1;
}


bool gameEngine::loadEngineTypes(char* info)
{
	std::ifstream file;
	file.open(info,std::ios::in);
	if(!file.is_open())
	{
		return 0;
	}

	char buffer[300]={};
	char miniBuffer[30];
	engineType* tempEngineType=new engineType;
	int i=0;

	while(!file.eof())
	{
		file >> buffer;
		i=0;
		int counter=0;
		int dataType=0;
		for(int k=0;k<=18;k++)
		{
			while(buffer[i]!=',' && buffer[i]!=NULL)
			{
				miniBuffer[counter]=buffer[i];
				i++;
				counter++;
			}
			miniBuffer[counter]=NULL;
			switch(dataType)
			{
			case 0:
				tempEngineType->name=new char[i+1];
				for(int j=0;j<=i;j++)
				{
					tempEngineType->name[j]=miniBuffer[j];
				}
				break;
			case 1:
				tempEngineType->engineClass=atoi(miniBuffer);
				break;
			case 2:
				tempEngineType->topSpeed=atof(miniBuffer);
				break;
			case 3:
				tempEngineType->accerationRate=atof(miniBuffer);
				break;
			case 4:
				tempEngineType->responseTime=atof(miniBuffer);
				break;
			case 5:
				tempEngineType->energyDraw=atof(miniBuffer);
				break;
			case 6:
				tempEngineType->price=atoi(miniBuffer);
				break;
			default:
				break;
			}
			i++;
			counter=0;
			dataType++;
		}

		t_engineType.push_back(*tempEngineType);
	}
	delete tempEngineType;
	tempEngineType=NULL;
	file.close();
	return 1;
}



bool gameEngine::loadShipTypes(char* info)
{
	std::ifstream file;
	file.open(info,std::ios::in);
	if(!file.is_open())
	{
		return 0;
	}

	char buffer[300]={};
	char miniBuffer[30];
	shipType* tempShipType=new shipType;
	int i=0;

	while(!file.eof())
	{
		file >> buffer;
		i=0;
		int counter=0;
		int dataType=0;
		for(int k=0;k<=18;k++)
		{

			while(buffer[i]!=',' && buffer[i]!=NULL)
			{
				miniBuffer[counter]=buffer[i];
				i++;
				counter++;
			}
			miniBuffer[counter]=NULL;
			switch(dataType)
			{
			case 0:
				tempShipType->name=new char[i+1];
				for(int j=0;j<=i;j++)
				{
					tempShipType->name[j]=miniBuffer[j];
				}
				break;
			case 1:
				tempShipType->shipClass=atoi(miniBuffer);
				break;
			case 2:
				tempShipType->engineCapability=atoi(miniBuffer);
				break;
			case 3:
				tempShipType->weaponCapablity=atoi(miniBuffer);
				break;
			case 4:
				tempShipType->turnThrusterCapability=atoi(miniBuffer);
				break;
			case 5:
				tempShipType->shieldCapability=atoi(miniBuffer);
				break;
			case 6:
				tempShipType->energyCapability=atoi(miniBuffer);
				break;
			case 7:
				tempShipType->solarRechargeCapability=atoi(miniBuffer);
				break;
			case 8:
				tempShipType->numberOfEngineMounts=atoi(miniBuffer);
				break;
			case 9:
				tempShipType->numberOfGunMounts=atoi(miniBuffer);
				break;
			case 10:
				tempShipType->numberOfShields=atoi(miniBuffer);
				break;
			case 11:
				tempShipType->passengerQuarterSize=atoi(miniBuffer);
				break;
			case 12:
				tempShipType->cargoSize=atoi(miniBuffer);
				break;
			case 13:
				tempShipType->hullStrength=atoi(miniBuffer);
				break;
			case 14:
				tempShipType->price=atoi(miniBuffer);
				break;
			case 15:
				tempShipType->shipMass=atoi(miniBuffer);
				break;
			case 16:
				tempShipType->shipRadius=atoi(miniBuffer);
				break;
			case 17:
				tempShipType->model=atoi(miniBuffer);
				break;
			case 18:
				tempShipType->numberOfTextures=atoi(miniBuffer);
				break;
			default:
				break;
			}



			i++;
			counter=0;
			dataType++;
		}
		tempShipType->textures=new unsigned int[tempShipType->numberOfTextures];
		for(int k=0;k<=tempShipType->numberOfTextures-1;k++)
		{
			while(buffer[i]!=',' && buffer[i]!=NULL)
			{
				miniBuffer[counter]=buffer[i];
				i++;
				counter++;
			}
			miniBuffer[counter]=NULL;

			tempShipType->textures[k]=atoi(miniBuffer);
			i++;
			counter=0;
		}
		matrix tempMatrix;
		double tempInput[4];
		tempInput[3]=0;
		int tempCount=0;

		for(int k=0;k<=tempShipType->numberOfGunMounts*3-1;k++)
		{
			while(buffer[i]!=',' && buffer[i]!=NULL)
			{
				miniBuffer[counter]=buffer[i];
				i++;
				counter++;
			}
			miniBuffer[counter]=NULL;

			tempInput[tempCount]=atof(miniBuffer);
			if(tempCount>=2)
			{
				tempMatrix.setMatrix(4,1,tempInput);
				tempShipType->gunMountLocation.push_back(tempMatrix);
				tempCount=-1;
			}

			i++;
			counter=0;
			tempCount++;
		}

		tempCount=0;

		for(int k=0;k<=tempShipType->numberOfGunMounts*3-1;k++)
		{
			while(buffer[i]!=',' && buffer[i]!=NULL)
			{
				miniBuffer[counter]=buffer[i];
				i++;
				counter++;
			}
			miniBuffer[counter]=NULL;

			tempInput[tempCount]=atof(miniBuffer);
			if(tempCount>=2)
			{
				tempMatrix.setMatrix(4,1,tempInput);
				tempShipType->gunMountUpDirection.push_back(tempMatrix);
				tempCount=-1;
			}

			i++;
			counter=0;
			tempCount++;
		}

		t_shipType.push_back(*tempShipType);
		tempShipType->gunMountLocation.clear();
		tempShipType->gunMountUpDirection.clear();

	}
	delete tempShipType;
	tempShipType=NULL;
	file.close();
	return 1;
}

bool gameEngine::loadTextures(char* info,int type)
{
	std::ifstream file;
	file.open(info,std::ios::in);
	if(!file.is_open())
	{
		return 0;
	}

	int numberOfTextures=0;
	char buffer[300]={};
	unsigned int* t_textures;
	bmpLoader* t_textureFile;


	while(!file.eof())
	{
		file >> buffer;
		numberOfTextures++;
	}
	file.clear();
	switch(type)
	{
	case PLANET:
		numberOfPlanetTextures=numberOfTextures;
		t_textures = t_planetTextures = new unsigned int[numberOfTextures];
		t_textureFile = t_planetTextureFile = new bmpLoader[numberOfTextures];
		glGenTextures(numberOfTextures,t_planetTextures);
		break;
	case SHIP:
		numberOfShipTextures=numberOfTextures;
		t_textures = t_shipTextures = new unsigned int[numberOfTextures];
		t_textureFile= t_shipTextureFile = new bmpLoader[numberOfTextures];
		glGenTextures(numberOfTextures,t_shipTextures);
		break;
	case PROJECTILE:
		numberOfProjectileTextures=numberOfTextures;
		t_textures = t_projectileTextures = new unsigned int[numberOfTextures];
		t_textureFile=t_projectileTextureFile = new bmpLoader[numberOfTextures];
		glGenTextures(numberOfTextures,t_projectileTextures);
	case MENU:
		numberOfMenuTextures=numberOfTextures;
		t_textures=t_menuTextures = new unsigned int[numberOfTextures];
		t_textureFile=t_menuTextureFile=new bmpLoader[numberOfTextures];
		glGenTextures(numberOfTextures,t_menuTextures);
		break;
	case COCKPIT:
		numberOfCockpitTextures=numberOfTextures;
		t_textures=t_cockpitTextures = new unsigned int[numberOfTextures];
		t_textureFile=t_cockpitTextureFile=new bmpLoader[numberOfTextures];
		glGenTextures(numberOfTextures,t_cockpitTextures);
		break;
	case BACKGROUND:
		numberOfBackgroundTextures=numberOfTextures;
		t_textures=t_backgroundTextures=new unsigned int[numberOfTextures];
		t_textureFile=t_backgroundTextureFile=new bmpLoader[numberOfTextures];
		glGenTextures(numberOfTextures,t_backgroundTextures);
		break;
	case OTHER:
		numberOfOtherTextures=numberOfTextures;
		t_textures = t_otherTextures = new unsigned int[numberOfTextures];
		t_textureFile = t_otherTextureFile = new bmpLoader[numberOfTextures];
		glGenTextures(numberOfTextures,t_otherTextures);
		break;
	default:
		break;
	}
	file.seekg(0,std::ios::beg);
	GLint rgb;
	int i=0;
	while(!file.eof())
	{
		file >> buffer;
		if(!t_textureFile[i].loadFile(buffer))
		{
			file.close();
			return 0;
		}

		glBindTexture(GL_TEXTURE_2D,t_textures[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		t_textureFile[i].reverseRGB();
		if(t_textureFile[i].getColorBits()==4)
		{
			rgb=GL_RGBA;
		}
		else
		{
			rgb=GL_RGB;
		}
		
		
		glTexImage2D(GL_TEXTURE_2D,0,rgb,t_textureFile[i].getWidth(),t_textureFile[i].getHeigth(),0,rgb,GL_UNSIGNED_BYTE,t_textureFile[i].getData());
		i++;
	}
	file.close();
	return 1;
}



bool gameEngine::loadModels(char* info,int type)
{
	std::ifstream file;
	file.open(info,std::ios::in);
	if(!file.is_open())
	{
		return 0;
	}
	float* pointArray;
	float* textArray;
	int* objectArray;
	float* normalArray;

	char buffer[300]={};
	studioMaxModel* tempLoader;
	model* tempModel;

	while(!file.eof())
	{
		file >> buffer;
		tempLoader=new studioMaxModel;
		
		if(!tempLoader->loadFile(buffer))
		{
			file.close();
			return 0;
		}

		pointArray=new float[tempLoader->getVertexCoordSize()];
		textArray=new float[tempLoader->getTextCoordSize()];
		objectArray=new int[tempLoader->getNumberOfObjects()];
		normalArray=new float[tempLoader->getNumberOfNormals()];
		tempLoader->getVertexCoord(pointArray);
		tempLoader->getTextCoord(textArray);
		tempLoader->getObjectFaceLengths(objectArray);
		tempLoader->getNormals(normalArray);
		
		tempModel=new model;
		
		tempModel->getPointArray(pointArray,tempLoader->getVertexCoordSize());
		tempModel->getTextArray(textArray,tempLoader->getTextCoordSize());
		tempModel->getObjectArray(objectArray,tempLoader->getNumberOfObjects());
		tempModel->getNormalArray(normalArray,tempLoader->getNumberOfNormals());
	
		delete[] pointArray; pointArray=NULL;
		delete[] textArray; textArray=NULL;
		delete[] objectArray; objectArray=NULL;
		delete[] normalArray; normalArray=NULL;
		delete tempLoader; tempLoader=NULL;
		switch(type)
		{
			case PLANET:
				t_planetModels.push_back(tempModel);
				break;
			case SHIP:
				t_shipModels.push_back(tempModel);
				break;
			case PROJECTILE:
				t_projectileModels.push_back(tempModel);
				break;
			case MENU:
				t_menuModels.push_back(tempModel);
				break;
			case COCKPIT:
				t_cockpitModels.push_back(tempModel);
				break;
			case BACKGROUND:
				t_backgroundModels.push_back(tempModel);
				break;
			case OTHER:
				t_otherModels.push_back(tempModel);
				break;
			default:
				break;
		}
	}

	file.close();
	return 1;
}

//void gameEngine::checkCollisions()
//{
//	double tempPrevLoc[4];
//	double tempPrevLoc2[4];
//	double tempNewLoc[4];
//	double tempNewLoc2[4];
//	double collisionX,collisionY,collisionZ;
//	int i=0;
//
//
//	while(i<t_players.size())
//	{
//		int j=i+1;
//		while(j<t_players.size())
//		{
//			t_players[i]->t_ship.getPrevLocation(tempPrevLoc);
//			t_players[j]->t_ship.getPrevLocation(tempPrevLoc2);
//			t_players[i]->t_ship.getLocation(tempNewLoc);
//			t_players[j]->t_ship.getLocation(tempNewLoc2);
//			if(t_collision.detect(tempPrevLoc[0],tempPrevLoc[1],tempPrevLoc[2],tempPrevLoc2[0],tempPrevLoc2[1],tempPrevLoc2[2],tempNewLoc[0],tempNewLoc[1],tempNewLoc[2],1,tempNewLoc2[0],tempNewLoc2[1],tempNewLoc2[2],1,collisionX,collisionY,collisionZ))
//			{
//				PlaySound(TEXT("c:/test/sound.wav"),NULL,SND_FILENAME|SND_ASYNC);
//			}
//			j++;
//		}
//
//		j=0;
//		while(j<t_projectiles.size())
//		{
//			t_players[i]->t_ship.getPrevLocation(tempPrevLoc);
//			t_players[i]->t_ship.getLocation(tempNewLoc);
//			t_projectiles[j].getPrevLocation(tempPrevLoc2);
//			t_projectiles[j].getLocation(tempNewLoc2);
//			if(t_collision.detect(tempPrevLoc[0],tempPrevLoc[1],tempPrevLoc[2],tempPrevLoc2[0],tempPrevLoc2[1],tempPrevLoc2[2],tempNewLoc[0],tempNewLoc[1],tempNewLoc[2],1,tempNewLoc2[0],tempNewLoc2[1],tempNewLoc2[2],.5,collisionX,collisionY,collisionZ))
//			{
//				//create small Explosion at collision x,y,z
//				t_players[i]->t_ship.recieveDamage(t_projectiles[j].getDamage());
//				t_projectiles[j].setDone();
//				PlaySound(TEXT("c:/test/sound.wav"),NULL,SND_FILENAME|SND_ASYNC);
//			}
//			j++;
//		}
//		j=0;
//		double orient[16];
//		while(j<t_planets.size())
//		{
//			t_players[i]->t_ship.getPrevLocation(tempPrevLoc);
//			t_players[i]->t_ship.getLocation(tempNewLoc);
//			t_planets[j]->getPrevLocation(tempPrevLoc2);
//			t_planets[j]->getLocation(tempNewLoc2);
//			if(t_collision.detect(tempPrevLoc[0],tempPrevLoc[1],tempPrevLoc[2],tempPrevLoc2[0],tempPrevLoc2[1],tempPrevLoc2[2],tempNewLoc[0],tempNewLoc[1],tempNewLoc[2],2,tempNewLoc2[0],tempNewLoc2[1],tempNewLoc2[2],150,collisionX,collisionY,collisionZ))
//			{
//				t_players[i]->t_ship.setLocation((collisionX-tempNewLoc2[0])*1.01+tempNewLoc2[0],(collisionY-tempNewLoc2[1])*1.01+tempNewLoc2[1],(collisionZ-tempNewLoc2[2])*1.01+tempNewLoc2[2]);
//				t_players[i]->t_ship.setShipSpeed(0);
//				//PlaySound(TEXT("c:/test/sound.wav"),NULL,SND_FILENAME|SND_ASYNC);
//			}
//			j++;
//
//
//		}
//
//		i++;
//	}
//}

//void gameEngine::checkCollisions()
//{
//	double tempPrevLoc[4];
//	double tempPrevLoc2[4];
//	double tempNewLoc[4];
//	double tempNewLoc2[4];
//	double collisionX,collisionY,collisionZ;
//	int i=0;
//	int k=-1,u=-1,m=-1;
//	int tempX,tempY,tempZ;
//
//
//	while(i<t_players.size())
//	{
//
//		while(m<2)
//		{
//			u=-1;
//			while(u<2)
//			{
//				k=-1;
//				while(k<2)
//				{
//					tempX=t_players[i]->t_ship.getSectorX()+k;
//					if(tempX>t_galaxy->getWidth()-1)
//					{
//						tempX=0;
//					}
//					if(tempX<0)
//					{
//						tempX=t_galaxy->getWidth()-1;
//					}
//					tempZ=t_players[i]->t_ship.getSectorZ()+u;
//					if(tempZ>t_galaxy->getDepth()-1)
//					{
//						tempZ=0;
//					}
//					if(tempZ<0)
//					{
//						tempZ=t_galaxy->getDepth()-1;
//					}
//					tempY=t_players[i]->t_ship.getSectorY()+m;
//					if(tempY>t_galaxy->getHeight()-1)
//					{
//						tempY=0;
//					}
//					if(tempY<0)
//					{
//						tempY=t_galaxy->getHeight()-1;
//					}
//
//
//
//					//if(i!=mainPlayer && t_players[i]->t_ship.getSectorX()==tempX && t_players[i]->t_ship.getSectorY()==tempY && t_players[i]->t_ship.getSectorZ()==tempZ)
//					//{
//					//	t_players[i]->t_ship.getLocation(tempLocSect);
//					//	t_players[i]->t_ship.setLocation(tempLocSect[0]+(t_galaxy->getSectorSize()*k),tempLocSect[1]+(t_galaxy->getSectorSize()*m),tempLocSect[2]+(t_galaxy->getSectorSize()*j));
//					//	if(t_frustum.frustumCheck(tempLocSect[0]+(t_galaxy->getSectorSize()*k),tempLocSect[1]+(t_galaxy->getSectorSize()*m),tempLocSect[2]+(t_galaxy->getSectorSize()*j),t_players[i]->t_ship.getShipType()->shipRadius))
//					//	{
//					//		t_players[i]->t_ship.draw();
//					//	}
//					//	t_players[i]->t_ship.setLocation(tempLocSect);
//					//}
//					//i++;
//				
//
//					int j=i+1;
//					while(j<t_players.size())
//					{
//						if(t_players[j]->t_ship.getSectorX()==tempX && t_players[j]->t_ship.getSectorY()==tempY && t_players[j]->t_ship.getSectorZ()==tempZ)
//						{
//							t_players[i]->t_ship.getPrevLocation(tempPrevLoc);
//							t_players[j]->t_ship.getPrevLocation(tempPrevLoc2);
//							t_players[j]->t_ship.setPrevLocation(tempPrevLoc2[0]+(t_galaxy->getSectorSize()*k),tempPrevLoc2[1]+(t_galaxy->getSectorSize()*m),tempPrevLoc2[2]+(t_galaxy->getSectorSize()*u));
//							t_players[i]->t_ship.getLocation(tempNewLoc);
//							t_players[j]->t_ship.getLocation(tempNewLoc2);
//							t_players[j]->t_ship.setLocation(tempNewLoc2[0]+(t_galaxy->getSectorSize()*k),tempNewLoc2[1]+(t_galaxy->getSectorSize()*m),tempNewLoc2[2]+(t_galaxy->getSectorSize()*u));
//							if(t_collision.detect(tempPrevLoc[0],tempPrevLoc[1],tempPrevLoc[2],tempPrevLoc2[0],tempPrevLoc2[1],tempPrevLoc2[2],tempNewLoc[0],tempNewLoc[1],tempNewLoc[2],1,tempNewLoc2[0],tempNewLoc2[1],tempNewLoc2[2],1,collisionX,collisionY,collisionZ))
//							{
//								PlaySound(TEXT("c:/test/sound.wav"),NULL,SND_FILENAME|SND_ASYNC);
//							}
//							t_players[j]->t_ship.setPrevLocation(tempPrevLoc2);
//							t_players[j]->t_ship.setLocation(tempNewLoc2);
//						}
//
//
//						j++;
//					}
//
//					//j=0;
//					//while(j<t_projectiles.size())
//					//{
//					//	t_players[i]->t_ship.getPrevLocation(tempPrevLoc);
//					//	t_players[i]->t_ship.getLocation(tempNewLoc);
//					//	t_projectiles[j].getPrevLocation(tempPrevLoc2);
//					//	t_projectiles[j].getLocation(tempNewLoc2);
//					//	if(t_collision.detect(tempPrevLoc[0],tempPrevLoc[1],tempPrevLoc[2],tempPrevLoc2[0],tempPrevLoc2[1],tempPrevLoc2[2],tempNewLoc[0],tempNewLoc[1],tempNewLoc[2],1,tempNewLoc2[0],tempNewLoc2[1],tempNewLoc2[2],.5,collisionX,collisionY,collisionZ))
//					//	{
//					//		//create small Explosion at collision x,y,z
//					//		t_players[i]->t_ship.recieveDamage(t_projectiles[j].getDamage());
//					//		t_projectiles[j].setDone();
//					//		PlaySound(TEXT("c:/test/sound.wav"),NULL,SND_FILENAME|SND_ASYNC);
//					//	}
//					//	j++;
//					//}
//					j=0;
//					//double orient[16];
//					while(j<t_planets.size())
//					{
//						if(t_planets[j]->getSectorX()==tempX && t_planets[j]->getSectorY()==tempY && t_planets[j]->getSectorZ()==tempZ)
//						{
//							t_players[i]->t_ship.getPrevLocation(tempPrevLoc);
//							t_players[i]->t_ship.getLocation(tempNewLoc);
//
//							t_planets[j]->getPrevLocation(tempPrevLoc2);
//							t_planets[j]->setPrevLocation(tempPrevLoc2[0]+(t_galaxy->getSectorSize()*k),tempPrevLoc2[1]+(t_galaxy->getSectorSize()*m),tempPrevLoc2[2]+(t_galaxy->getSectorSize()*u));
//							t_planets[j]->getLocation(tempNewLoc2);
//							t_planets[j]->setLocation(tempNewLoc2[0]+(t_galaxy->getSectorSize()*k),tempNewLoc2[1]+(t_galaxy->getSectorSize()*m),tempNewLoc2[2]+(t_galaxy->getSectorSize()*u));
//							if(t_collision.detect(tempPrevLoc[0],tempPrevLoc[1],tempPrevLoc[2],tempPrevLoc2[0],tempPrevLoc2[1],tempPrevLoc2[2],tempNewLoc[0],tempNewLoc[1],tempNewLoc[2],2,tempNewLoc2[0],tempNewLoc2[1],tempNewLoc2[2],150,collisionX,collisionY,collisionZ))
//							{
//								t_players[i]->t_ship.setLocation((collisionX-tempNewLoc2[0])*1.01+tempNewLoc2[0],(collisionY-tempNewLoc2[1])*1.01+tempNewLoc2[1],(collisionZ-tempNewLoc2[2])*1.01+tempNewLoc2[2]);
//								t_players[i]->t_ship.setShipSpeed(0);
//								//PlaySound(TEXT("c:/test/sound.wav"),NULL,SND_FILENAME|SND_ASYNC);
//							}
//							t_planets[j]->setPrevLocation(tempPrevLoc2);
//							t_planets[j]->setLocation(tempNewLoc2);
//						}
//						j++;
//					}
//					k++;
//				}
//				u++;
//			}
//			m++;
//		}
//		i++;
//	}
//}

