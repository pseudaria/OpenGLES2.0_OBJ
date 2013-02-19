#include "openglsb.h"
#include <math.h>
#include <stdio.h>

#define GL_PI 3.1415f
#define TRUE 1


// A clipping's size. its aspectRatio will be set in ChangeSize().
GLfloat clippingWidth;
GLfloat clippingHeight;

//---------------------------------//

//Set RenderScene
void RenderScene(void)
{
  //set bg clear color
  glClearColor(0.13f,0.43f,0.86f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  //enable scissor test
  glEnable(GL_SCISSOR_TEST);

  //set 2nd Background Color
  glClearColor(0.231373f, 0.627451f, 0.423529f, 1.0f);
  //set Scissor Area
  glScissor(100, 100, 600, 400);  
  //draw Background with 2nd Color
  glClear(GL_COLOR_BUFFER_BIT);

  //set 3rd Background Color and draw Background with this Color
  glClearColor(1.0f, 0.262745f, 0.901961f, 1.0f);
  //set Scissor Area
  glScissor(200, 200, 400, 200);  
  //draw Background with 3nd Color
  glClear(GL_COLOR_BUFFER_BIT);

  //disable scissor test for next rendering
  glDisable(GL_SCISSOR_TEST);

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

//Start Main Program.
void main(int argc, char* argv[])
{
  //Initiate glut
  glutInit(&argc,argv);
  //Initiate DisplayMode
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  //Create an Window with X
  glutCreateWindow("Scissor Rectangle - 20130219");
 //set Callback Func - Display Routine
  glutDisplayFunc(RenderScene);
  //set Callback Func - Reshape Routine
  glutReshapeFunc(ChangeSize);
 //set Rendering Option
  SetupRC(); 
  //Start Routine
  glutMainLoop();
}
