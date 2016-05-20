#ifdef _WINDOWS
#include <windows.h>
#endif

#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include "CGfxOpenGL.h"






// disable implicit float-double casting
#pragma warning(disable:4305)

CGfxOpenGL::CGfxOpenGL()
{
	matrix[0]=1;
	matrix[1]=0;
	matrix[2]=0;
	matrix[3]=0;
	matrix[4]=0;
	matrix[5]=1;
	matrix[6]=0;
	matrix[7]=0;
	matrix[8]=0;
	matrix[9]=0;
	matrix[10]=1;
	matrix[11]=0;
	matrix[12]=0;
	matrix[13]=0;
	matrix[14]=0;
	matrix[15]=1;
	
	 

}

CGfxOpenGL::~CGfxOpenGL()
{
}

bool CGfxOpenGL::Init()
{   
    // clear to black background
    glClearColor(0.0, 0.0, 0.0, 0.0);

    m_angle = 0.0f;

    return true;
}

bool CGfxOpenGL::Shutdown()
{
    return true;
}

void CGfxOpenGL::SetupProjection(int width, int height)
{
    if (height == 0)                    // don't want a divide by zero
    {
        height = 1;                 
    }

    glViewport(0, 0, width, height);        // reset the viewport to new dimensions
    glMatrixMode(GL_PROJECTION);            // set projection matrix current matrix
    glLoadIdentity();                       // reset projection matrix

    // calculate aspect ratio of window
    gluPerspective(52.0f,(GLfloat)width/(GLfloat)height,1.0f,20000.0f);

    glMatrixMode(GL_MODELVIEW);   	// set modelview matrix
	glEnable(GL_DEPTH_TEST);
    glLoadIdentity();                       // reset modelview matrix

    m_windowWidth = width;
    m_windowHeight = height;
}

void CGfxOpenGL::Prepare(float dt)
{
    m_angle += 0.01f;
}

void CGfxOpenGL::Render(float Counter)
{
	Counter++;
    // clear screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     
    glLoadIdentity();

    // move back 5 units and rotate about all 3 axes
    glTranslatef(0.0, 0.0, -5.0f);
	
	//glPushMatrix();
	glMultMatrixf(matrix);
	
   /* glRotatef(m_angle, 1.0f, 0.0f, 0.0f);
    glRotatef(m_angle, 0.0f, 1.0f, 0.0f);
    glRotatef(m_angle, 0.0f, 0.0f, 1.0f);*/

    // lime greenish color
    //glColor3ui(255, 0, 0);
	float Red = (abs(sin(Counter+2.094951))-sin(Counter+2.094951))/2;
	float Blue = (abs(sin(Counter+4.188790))-sin(Counter+4.188790))/2;
	float Green = (abs(sin(Counter+6.283185))-sin(Counter+6.283185))/2;
	
	glColor3f(Red,Blue,Green);

    // draw the triangle such that the rotation point is in the center
    glBegin(GL_TRIANGLES);
        glVertex3f(1.0f, -1.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();
	//glPopMatrix();
	
}

