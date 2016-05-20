#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN


#include <windows.h>
#include <gl/glu.h>
#include <gl/gl.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>
#include <math.h>
#include <random>
#include <time.h>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "timer.h"
#include "CGfxOpenGL.h"
#include "matrix.h"


#include "resourceType.h"
#include "resource.h"
#include "resourceSlot.h"

#include "bmpLoader.h"
#include "3dsLoader.h"
#include "faction.h"
#include "model.h"
#include "s_object.h"
#include "projectile.h"
#include "ship.h"
#include "planet.h"
#include "player.h"
#include "galaxy.h"
#include "frustum.h"
#include "collision.h"
#include "gameEngine.h"








//ship Enterprise;

//s_object Voyager;


LPDIRECTINPUT8 pDirectInput;
LPDIRECTINPUTDEVICE8 pDevice;



bool exiting = false;
long windowWidth = 800;
long windowHeight = 600;
long windowBits = 32;
bool fullscreen = true;

HDC hDC;

CGfxOpenGL *g_glRender = NULL;
char* tempBuffer=new char[windowWidth*windowHeight*3];



void SetupPixelFormat(HDC hDC)
{
    int pixelFormat;

    PIXELFORMATDESCRIPTOR pfd =
    {   
        sizeof(PIXELFORMATDESCRIPTOR),  // size
            1,                          // version
            PFD_SUPPORT_OPENGL |        // OpenGL window
            PFD_DRAW_TO_WINDOW |        // render to window
            PFD_DOUBLEBUFFER,           // support double-buffering
            PFD_TYPE_RGBA,              // color type
            32,                         // prefered color depth
            0, 0, 0, 0, 0, 0,           // color bits (ignored)
            0,                          // no alpha buffer
            0,                          // alpha bits (ignored)
            0,                          // no accumulation buffer
            0, 0, 0, 0,                 // accum bits (ignored)
            16,                         // depth buffer
            0,                          // no stencil buffer
            0,                          // no auxiliary buffers
            PFD_MAIN_PLANE,             // main layer
            0,                          // reserved
            0, 0, 0,                    // no layer, visible, damage masks
    };

    pixelFormat = ChoosePixelFormat(hDC, &pfd);
    SetPixelFormat(hDC, pixelFormat, &pfd);
}

LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HDC hDC;
    static HGLRC hRC;
    int height, width;
	char header[54]={};//0x42,0x4D,36,F9 15 00 00 00 00 00 36 00 00 00 28 00 00 00 20 03 00 00 58 02 00 00 01 00 18 00 00 00 00 00 00 F9 15 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00};
	std::ofstream outFile;
	char* tempCharR;
	long tempLong;
	
	
	//Enterprise.setAcceleration(0);

    // dispatch messages
    switch (uMsg)
    {   
    case WM_CREATE:         // window creation
        hDC = GetDC(hWnd);
        SetupPixelFormat(hDC);
        //SetupPalette();
        hRC = wglCreateContext(hDC);
        wglMakeCurrent(hDC, hRC);
        break;

    case WM_DESTROY:            // window destroy
    case WM_QUIT:
    case WM_CLOSE:                  // windows is closing

        // deselect rendering context and delete it
		pDevice->Unacquire();
        wglMakeCurrent(hDC, NULL);
        wglDeleteContext(hRC);

        // send WM_QUIT to message queue
        PostQuitMessage(0);
        break;

    case WM_SIZE:
        height = HIWORD(lParam);        // retrieve width and height
        width = LOWORD(lParam);

        g_glRender->SetupProjection(width, height);

        break;

    case WM_ACTIVATEAPP:		// activate app
		
        break;
	case WM_SETFOCUS:
		if(FAILED(pDevice->Acquire()))
		{
			PostQuitMessage(0);
		}
		break;
	case WM_KILLFOCUS:
		if(FAILED(pDevice->Unacquire()))
		{
			PostQuitMessage(0);
		}
		break;

    case WM_PAINT:              // paint
        PAINTSTRUCT ps;
        BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;

    case WM_LBUTTONDOWN:        // left mouse button
        break;

    case WM_RBUTTONDOWN:        // right mouse button
        break;

    case WM_MOUSEMOVE:          // mouse movement
        break;

    case WM_LBUTTONUP:          // left button release
        break;

    case WM_RBUTTONUP:          // right button release
        break;

    case WM_KEYUP:
        break;

    case WM_KEYDOWN:
        int fwKeys;
        LPARAM keyData;
        fwKeys = (int)wParam;    // virtual-key code 
        keyData = lParam;          // key data 

        switch(fwKeys)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;

		case 'W':
			//Enterprise.turn(PITCH,-1);
			break;
		case 'S':
			//Enterprise.turn(PITCH,1);
			break;
		case 'A':
			//Enterprise.turn(ROLL,-1);
			break;
		case 'D':
			//Enterprise.turn(ROLL,1);
			break;
		case 'E':
			//Enterprise.turn(YAW,-1);
			break;
		case 'Q':
			//Enterprise.turn(YAW,1);
			break;
		case 'F':
			//Enterprise.recieveDamage(20);
			break;
		case '1':
			//Enterprise.removeEnergyDistributer();
			break;
		case '2':
		//	Enterprise.lowerShields(1);
			break;
		case '3':
			//Enterprise.raiseShields(1);
			break;
		case VK_SHIFT:
			//Enterprise.Accelerate(1);
			break;
		case VK_CONTROL:
			//Enterprise.Accelerate(-1);
			break;
		case VK_SPACE:
					//Enterprise.turn(PITCH,0);
					//Enterprise.turn(ROLL,0);
					//Enterprise.turn(YAW,0);
					break;
		case VK_TAB:
			//Enterprise.Accelerate(0);
			break;
		case VK_F12:
			//*****************************************CREATING SCREENSHOT*******************************
			glReadPixels(0,0,windowWidth,windowHeight,GL_BGR_EXT,GL_UNSIGNED_BYTE,tempBuffer);
			outFile.open("c:/test/screenshot.bmp",std::ios::binary);
			header[0]=0x42;
			header[1]=0x4d;
			tempLong=windowWidth*windowHeight*3+54;
			tempCharR=reinterpret_cast<char*>(&tempLong);
			header[2]=tempCharR[0];
			header[3]=tempCharR[1];
			header[4]=tempCharR[2];
			header[5]=tempCharR[3];
			header[10]=0x36;
			header[14]=0x28;
			tempLong=windowWidth;
			tempCharR=reinterpret_cast<char*>(&tempLong);
			header[18]=tempCharR[0];
			header[19]=tempCharR[1];
			header[20]=tempCharR[2];
			header[21]=tempCharR[3];
			tempLong=windowHeight;
			tempCharR=reinterpret_cast<char*>(&tempLong);
			header[22]=tempCharR[0];
			header[23]=tempCharR[1];
			header[24]=tempCharR[2];
			header[25]=tempCharR[3];
			header[26]=0x01;
			header[28]=0x18;
			tempLong=windowWidth*windowHeight*3;
			tempCharR=reinterpret_cast<char*>(&tempLong);
			header[34]=tempCharR[0];
			header[35]=tempCharR[1];
			header[36]=tempCharR[2];
			header[37]=tempCharR[3];
			outFile.write(header,54);
			outFile.write(tempBuffer,windowWidth*windowHeight*3);
			outFile.close();

			
			break;
		default:
            break;
        }

        break;

    default:
        break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    WNDCLASSEX windowClass;     // window class
    HWND       hwnd;            // window handle
    MSG        msg;             // message
    DWORD      dwExStyle;       // Window Extended Style
    DWORD      dwStyle;         // Window Style
    RECT       windowRect;
	GLUquadricObj *Planet=gluNewQuadric();

    g_glRender = new CGfxOpenGL;

    windowRect.left=(long)0;                        // Set Left Value To 0
    windowRect.right=(long)windowWidth; // Set Right Value To Requested Width
    windowRect.top=(long)0;                         // Set Top Value To 0
    windowRect.bottom=(long)windowHeight;   // Set Bottom Value To Requested Height

    // fill out the window class structure
    windowClass.cbSize          = sizeof(WNDCLASSEX);
    windowClass.style           = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc     = MainWindowProc;
    windowClass.cbClsExtra      = 0;
    windowClass.cbWndExtra      = 0;
    windowClass.hInstance       = hInstance;
    windowClass.hIcon           = LoadIcon(NULL, IDI_APPLICATION);  // default icon
    windowClass.hCursor         = LoadCursor(NULL, IDC_ARROW);      // default arrow
    windowClass.hbrBackground   = NULL;                             // don't need background
    windowClass.lpszMenuName    = NULL;                             // no menu
    windowClass.lpszClassName   = L"GLClass";
    windowClass.hIconSm         = LoadIcon(NULL, IDI_WINLOGO);      // windows logo small icon

    // register the windows class
    if (!RegisterClassEx(&windowClass))
        return 0;

    if (fullscreen)                             // fullscreen?
    {
        DEVMODE dmScreenSettings;                   // device mode
        memset(&dmScreenSettings,0,sizeof(dmScreenSettings));
        dmScreenSettings.dmSize = sizeof(dmScreenSettings); 
        dmScreenSettings.dmPelsWidth = windowWidth;         // screen width
        dmScreenSettings.dmPelsHeight = windowHeight;           // screen height
        dmScreenSettings.dmBitsPerPel = windowBits;             // bits per pixel
        dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

        // 
        if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
        {
            // setting display mode failed, switch to windowed
            MessageBox(NULL, L"Display mode failed", NULL, MB_OK);
            fullscreen = FALSE; 
        }
    }

    if (fullscreen)                             // Are We Still In Fullscreen Mode?
    {
        dwExStyle=WS_EX_APPWINDOW;                  // Window Extended Style
        dwStyle=WS_POPUP;                       // Windows Style
        ShowCursor(FALSE);                      // Hide Mouse Pointer
    }
    else
    {
        dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;   // Window Extended Style
        dwStyle=WS_OVERLAPPEDWINDOW;                    // Windows Style
    }

    AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);     // Adjust Window To True Requested Size

    // class registered, so now create our window
    hwnd = CreateWindowEx(NULL,                                 // extended style
        L"GLClass",                          // class name
        L"Game",      // app name
        dwStyle | WS_CLIPCHILDREN |
        WS_CLIPSIBLINGS,
        0, 0,                               // x,y coordinate
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top, // width, height
        NULL,                               // handle to parent
        NULL,                               // handle to menu
        hInstance,                          // application instance
        NULL);                              // no extra params

    hDC = GetDC(hwnd);

    // check if window creation failed (hwnd would equal NULL)
    if (!hwnd)
        return 0;

    ShowWindow(hwnd, SW_SHOW);          // display the window
    UpdateWindow(hwnd);					// update the window




	//collision test;
	//test.setResolution(5);
	//test.detect(1,1,0,.001,8,3.05,0,.001,12,12,0,.001,8,10.82,0,.001);







	//************************************************JOYSTICK SETUP*********************************************
	DIJOYSTATE devInfo;
	//LPDIRECTINPUTDEVICE8 pDevice;
	if(FAILED(DirectInput8Create(hInstance,DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&pDirectInput,NULL)))
	{
		return 0;
	}
	BOOL CALLBACK myDeviceCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef);
	HRESULT h;
	h=pDirectInput->EnumDevices(DI8DEVTYPE_JOYSTICK,myDeviceCallback,NULL,DIEDFL_ALLDEVICES);
	if(FAILED(h))
	{
		return 0;
	}
	h=pDevice->SetDataFormat(&c_dfDIJoystick);
	if(FAILED(h))
	{
		return 0;
	}
	h=pDevice->SetCooperativeLevel(hwnd,DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
	if(FAILED(h))
	{
		return 0;
	}
	h=pDevice->Acquire();
	if(FAILED(h))
	{
		return 0;
	}

    g_glRender->Init();
	CTime timer;
	timer.Initialize();



	//***************************************LOADING MODELS******************************************
	faction goodguys;
	goodguys.setName("The Super Human Monkeys");
	unsigned char* tempColor=new unsigned char[3];
	tempColor[0]=0x36;
	tempColor[1]=0xE4;
	tempColor[2]=0xF8;
	goodguys.setColor(tempColor);

	faction badguys;
	badguys.setName("Herpy Herpison");
	tempColor[0]=0xEF;
	tempColor[1]=0x27;
	tempColor[2]=0x2D;
	badguys.setColor(tempColor);

	player tim;
	tim.setName("Tim");
	tim.addMoney(10000);
	tim.setFaction(goodguys);

	player matt;
	matt.setName("Matt");
	matt.addMoney(10000);
	matt.setFaction(badguys);

	galaxy milkyWay(2,2,2,20000,40,0,0,300);


	


	gameEngine mygame;
	mygame.addGalaxy(&milkyWay);

	mygame.loadModels("c:/test/Models/Planets/planetModelFiles.txt",PLANET);
	mygame.loadModels("c:/test/Models/Ships/shipModelFiles.txt",SHIP);
	mygame.loadModels("c:/test/Models/Menus/menuModelFiles.txt",MENU);
	mygame.loadModels("c:/test/Models/Cockpits/cockpitModelFiles.txt",COCKPIT);
	mygame.loadModels("c:/test/Models/Backgrounds/backgroundModelFiles.txt",BACKGROUND);
	mygame.loadModels("c:/test/Models/Projectiles/ProjectileModelFiles.txt",PROJECTILE);

	mygame.loadTextures("c:/test/Textures/PlanetTextures/PlanetTextureFiles.txt",PLANET);
	mygame.loadTextures("c:/test/Textures/ShipTextures/ShipTextureFiles.txt",SHIP);
	mygame.loadTextures("c:/test/Textures/MenuTextures/MenuTextureFiles.txt",MENU);
	//mygame.loadTextures("c:/test/Textures/CockpitTextures/CockpitTextureFiles.txt",COCKPIT);
	mygame.loadTextures("c:/test/Textures/BackgroundTextures/BackgroundTextureFiles.txt",BACKGROUND);
	mygame.loadTextures("c:/test/Textures/Projectile Textures/ProjectileTextureFiles.txt",PROJECTILE);

	

	mygame.loadShipTypes("c:/test/Types/ShipTypes.txt");
	mygame.loadEngineTypes("c:/test/Types/EngineTypes.txt");
	mygame.loadGunTypes("c:/test/Types/GunTypes.txt");
	mygame.loadTurnThrusterTypes("c:/test/Types/TurnThrusterTypes.txt");
	mygame.loadShieldTypes("c:/test/Types/ShieldTypes.txt");
	mygame.loadEnergyDistributerTypes("c:/test/Types/EnergyDistributerTypes.txt");
	mygame.loadSolarRechargerTypes("c:/test/Types/SolarRechargerTypes.txt");

	mygame.createPlanets();

	mygame.addPlayer(tim);
	mygame.addPlayer(matt);
	mygame.setMainPlayer(0);


	mygame.addShipToPlayer(0,0);
	mygame.addEngineToPlayer(0,0);
	mygame.addGunToPlayer(0,0);
	mygame.addGunToPlayer(0,0);
	//mygame.addGunToPlayer(0,0);
	mygame.addTurnThrusterToPlayer(0,0);
	mygame.addShieldToPlayer(0,0);
	mygame.addEngergyDistributerToPlayer(0,0);
	mygame.addSolarRechargerToPlayer(0,0);

	mygame.addShipToPlayer(1,1);
	mygame.addEngineToPlayer(1,0);
	mygame.addGunToPlayer(1,0);
	mygame.addGunToPlayer(1,0);
	mygame.addTurnThrusterToPlayer(1,0);
	mygame.addShieldToPlayer(1,0);
	mygame.addEngergyDistributerToPlayer(1,0);
	mygame.addSolarRechargerToPlayer(1,0);

	mygame.setCockpit(0,0);
	mygame.setBackground(0,0);

	//mygame.t_players[1]->t_ship.setLocation(7000,5000,1152);
	mygame.t_players[1]->t_ship.setLocation(5010,5000,4950);
	mygame.t_players[0]->t_ship.setLocation(5000,5000,5000);
	//mygame.t_players[1]->t_ship.Rotate(YAW,45);
	//mygame.t_players[0]->t_ship.Rotate(YAW,-46);
	//mygame.t_players[0]->t_ship.setLocation(3000,5000,1152);
	//mygame.t_players[0]->t_ship.Accelerate(1);
	//mygame.t_players[1]->t_ship.Accelerate(1);
	
	//mygame.t_players[0]->t_ship.Rotate(YAW,90);



	//****************************************LIGHTING/MATERIAL SETUP********************************************

	//GLfloat black[]={0,0,0,0};
	GLfloat blue[]={.7764,.9450,1,1};
	//GLfloat emmOn[]={.3,.3,.3,0};
	//GLfloat emmOff[]={0,0,0,0};

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	
	GLfloat lightDir[]={1,0,0,0};
	glLightfv(GL_LIGHT0,GL_POSITION,lightDir);
	//glLightfv(GL_LIGHT0,GL_DIFFUSE,blue);

	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	//glLightfv(GL_LIGHT0,GL_DIFFUSE,blue);
	//glLightf(GL_LIGHT0,GL_SPECULAR,*white);
	
	//double buttonTimer=1;
	double inputDouble;
	
    while (!exiting)
    {
		timer.Update();
		//*************************************INPUT ***************************************************
		pDevice->Poll();
		pDevice->GetDeviceState(sizeof(DIJOYSTATE),&devInfo);
		inputDouble=devInfo.lRz;
		inputDouble=-(inputDouble-32767)/32767;
		mygame.t_players[0]->t_ship.turn(YAW,inputDouble);
		//Enterprise.turn(YAW,inputDouble);
		inputDouble=devInfo.lY;
		inputDouble=(inputDouble-32767)/32767;
		mygame.t_players[0]->t_ship.turn(PITCH,inputDouble);
		//Enterprise.turn(PITCH,inputDouble);
		inputDouble=devInfo.lX;
		inputDouble=-(inputDouble-32767)/32767;
		mygame.t_players[0]->t_ship.turn(ROLL,inputDouble);
		//Enterprise.turn(ROLL,inputDouble);
		inputDouble=devInfo.lZ;
		inputDouble=-(inputDouble-32767)/32767;
		mygame.t_players[0]->t_ship.Accelerate(inputDouble);
		//Enterprise.Accelerate(inputDouble);
		if(devInfo.rgbButtons[0]==128)
		{
			mygame.t_players[0]->t_ship.fire();
			//Enterprise.fire();
		}
		if(devInfo.rgbButtons[1]==128)
		{
			mygame.t_players[1]->t_ship.Accelerate(1);
		}
		if(devInfo.rgbButtons[2]==128)
		{
			mygame.t_players[1]->t_ship.Accelerate(0);
		}

		//******************************************UPDATE************************************************


		mygame.setTime(timer.Get_dt()/100);
		//mygame.setTime(.2);
		mygame.update();
		mygame.checkCollisions();

		mygame.draw();

		
		
		SwapBuffers(hDC);

		while (PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage (&msg, NULL, 0, 0))
			{
				exiting = true;
				break;
			}

			TranslateMessage (&msg);
			DispatchMessage (&msg);
		}
    }

    delete g_glRender;

    if (fullscreen)
    {
        //ChangeDisplaySettings(NULL,0);          // If So Switch Back To The Desktop
        ShowCursor(TRUE);                       // Show Mouse Pointer
    }

    return (int)msg.wParam;
}

BOOL CALLBACK myDeviceCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
{
	HRESULT h;

	h=pDirectInput->CreateDevice(lpddi->guidInstance,&pDevice,NULL);
	if(FAILED(h))
	{
		return DIENUM_CONTINUE;
	}
	return DIENUM_STOP;
}