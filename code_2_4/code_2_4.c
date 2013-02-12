#include"openglsb.h"

// Square's Initial position and size
GLfloat x1 = 0.0f;
GLfloat y1 = 0.0f;
GLfloat rsize = 25;

// A square's moving speed
// pixel per one moving
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

// A clipping's size. its aspectRatio will be set in ChangeSize().
GLfloat clippingWidth;
GLfloat clippingHeight;

//---------------------------------//

//Set RenderScene
void RenderScene(void)
{
  //clear bg with present color by setting SetupRC()->glClearColor()
  glClear(GL_COLOR_BUFFER_BIT);
  //set drawing color for next object
  glColor3f(1.0f,0.0f,1.0f);
  //draw Rentangular with above drawing-color
  glRectf(x1,y1,x1 + rsize,y1 - rsize);
  //draw and swap buffers
  glutSwapBuffers();
}

//Setup Rendering Option
void SetupRC(void)
{
  //set bg clear color
  glClearColor(0.0f,1.0f,1.0f,1.0f);
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
	    1.0, -1.0);
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
	    1.0,-1.0);
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
  if (x1 > clippingWidth -rsize || x1 < -clippingWidth)
    xstep = -xstep;

  //chage ystep's direction,When a object is bounded at left or right.
  if (y1 > clippingHeight || y1 < -clippingHeight + rsize)
    ystep = -ystep;

  //move a object.
  x1 += xstep;
  y1 += ystep;

  //check whether square is out of window range or not.
  //When a window size is changed,  a object is sometime not in clipping area.
  if(x1 > (clippingWidth-rsize + xstep))
    x1 = clippingWidth -rsize -1;
  else if(x1 < -(clippingWidth + xstep))
    x1 = -clippingWidth -1;

  if(y1 > (clippingHeight + ystep))
    y1 = clippingHeight - 1;
  else if(y1 < -(clippingHeight - rsize + ystep))
    y1 = -clippingHeight + rsize -1; //why "-1 --> -ystep" can't do well?

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
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  //Create an Window with X
  glutCreateWindow("Bounce Square - 20130113");
  //set Callback Func - Display Routine
  glutDisplayFunc(RenderScene);
  //set Callback Func - Reshape Routine
  glutReshapeFunc(ChangeSize);
  //set Callback Func - Timer Routine
  glutTimerFunc(33, TimerFunction, 1);
  //set Rendering Option
  SetupRC();
  //Start Routine
  glutMainLoop();
}
