#include "openglsb.h"
#include <math.h>
#include <stdio.h>

#define GL_PI 3.1415f
#define TRUE 1


// A clipping's size. its aspectRatio will be set in ChangeSize().
GLfloat clippingWidth;
GLfloat clippingHeight;

// A square's moving speed
// pixel per one moving
static GLfloat xstep = 1.5f;
static GLfloat ystep = 1.0f;

// Square's Initial position and size
GLfloat x = 0.0f;
GLfloat y = 0.0f;
GLfloat rsize = 25.0f;

static char bEdgeFlag = 0;
//---------------------------------//

//Set RenderScene
void RenderScene(void)
{
  //Initial Radius and Angle 
  GLdouble dRadius = 0.1;
  GLdouble dAngle;

  //set Backgroud Color
  glClearColor(0.0f, 0.0f, 1.0f, 0.0f);

  //enable Stencil test , and set stencil 0.0f
  glClearStencil(0.0f);
  glEnable(GL_STENCIL_TEST);

  //clear Stensil and Color bit
  glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  //doing below procesure, All drawing command is never drawn
  //after stencil test, stencil's buffer value is increased.
  glStencilFunc(GL_NEVER, 0x0, 0x0);
  glStencilOp(GL_INCR, GL_INCR, GL_INCR);

  //makes Spiral Stencil Pattern
  //use white color for seeing stencil buffer effect

  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_LINE_STRIP);
    for(dAngle = 0; dAngle < 400.0; dAngle += 0.1){
      glVertex2d(dRadius * cos(dAngle), dRadius * sin(dAngle));
      dRadius *= 1.002;
    }
  glEnd();

  //allow to draw using stencil pattern except stencil patten has 0x1.
  glStencilFunc(GL_NOTEQUAL, 0x0, 0x1); //do change 0x0 <-> 1x0
  glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

  //draw red color Rectangle. it move.it use Timer Func
  glColor3f(1.0f, 0.0f, 0.0f);
  glRectf(x, y, x + rsize, y - rsize);

  //draw
  glutSwapBuffers();
}

//Setup Rendering Option
void SetupRC(void)
{
  //set bg clear color
  glClearColor(0.13f,0.43f,0.86f,1.0f);

  //set Initial drawing color
  glColor3f(0.7f, 0.2f, 0.2f);
}

//Change and Modify Window Size
void ChangeSize(GLsizei w, GLsizei h)
{
  GLfloat aspectRatio;

  //Can't not divide with 0
  if (h==0)
    h=1;

  //Change Viewport size for fitting a Window size
  glViewport(0,0,w,h);
  //Initiate System
  ////Matrix Transport
  glMatrixMode(GL_PROJECTION);
  ////Initiate System
  glLoadIdentity();

  //set Clipping area with order (left-, right+, bottom-, top+, near, far)
  aspectRatio = (GLfloat)w / (GLfloat)h;
  if (w <= h)
    {
      //set clippingWidth
      clippingWidth = 100.0f;
      //set clippingHeight
      clippingHeight = 100.0f / aspectRatio;
      //set clipping area fitting with aspectRatio
      glOrtho(-100.0,100.0,
	    -clippingHeight, clippingHeight,
	    -100.0, 100.0);
    }
  else
    {
      //set clippingWidth
      clippingWidth = 100 * aspectRatio;
      //set clippingHeight
      clippingHeight = 100.0f;
      //set clipping area fitting with aspectRatio
      glOrtho(-clippingWidth, clippingHeight,
	    -100, 100,
	    -100.0,100.0);
    }
  //Initiate System
  ////Matrix Transport
  glMatrixMode(GL_MODELVIEW);
  ////Initiate System
  glLoadIdentity();
}

//Move Object Each Time, Using Timer, when Window's size is changed or window don't move.
void TimerFunction(int value)
{
  //change xstep's direction,When a object is bounded at left or right.
  if (x > clippingWidth -rsize || x < -clippingWidth)
    xstep = -xstep;

  //chage ystep's direction,When a object is bounded at left or right.
  if (y > clippingHeight || y < -clippingHeight + rsize)
    ystep = -ystep;

  //move a object.
  x += xstep;
  y += ystep;

  //check whether square is out of window range or not.
  //When a window size is changed,  a object is sometime not in clipping area.
  if(x > (clippingWidth-rsize + xstep))
    x = clippingWidth -rsize -1;
  else if(x < -(clippingWidth + xstep))
    x = -clippingWidth -1;

  if(y > (clippingHeight + ystep))
    y = clippingHeight - 1;
  else if(y < -(clippingHeight - rsize + ystep))
    y = -clippingHeight + rsize -1; //why "-1 --> -ystep" can't do well?

  // Redraw scene in new system
  glutPostRedisplay();
  glutTimerFunc(33,TimerFunction,1);
}

//Start Main Program.
void main(int argc, char* argv[])
{

  //Initiate glut
  glutInit(&argc,argv);
  //Initiate DisplayMode
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
  //Create an Window with X
  glutCreateWindow("STENCIL PATTERN - 20130220");
  //set Callback Func - Display Routine
  glutDisplayFunc(RenderScene);
  //set Callback Func - Reshape Routine
  glutReshapeFunc(ChangeSize);
  //set Calback Func - Timer Routine
  glutTimerFunc(33, TimerFunction, 1);
  //set Rendering Option
  SetupRC();
  //Start Routine
  glutMainLoop();
}
