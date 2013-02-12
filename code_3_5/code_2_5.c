#include "openglsb.h"
#include <math.h>

#define GL_PI 3.1415f

// A clipping's size. its aspectRatio will be set in ChangeSize().
GLfloat clippingWidth;
GLfloat clippingHeight;

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

//---------------------------------//

//Set RenderScene
void RenderScene(void)
{
  //position and angle value
  GLfloat x,y,z,angle;
  //clear bg with present color by setting SetupRC() -> glClearColor()
  glClear(GL_COLOR_BUFFER_BIT);

  //save Matrix state and rotate
  glPushMatrix();
  glRotatef(xRot, 1.0f, 0.0f, 0.0f);
  glRotatef(yRot, 0.0f, 1.0f, 0.0f);

  //start to drawing POINTS
  glBegin(GL_POINTS);
    z = -50.0f;
    for(angle = 0.0f; angle <= (2.0f * GL_PI) * 3.0f; angle+=0.1f)
      {
	x = 50.0f*sin(angle);
	y = 50.0f*cos(angle);
	//set a point's position
	glVertex3f(x,y,z);
	//increase z value
	z += 0.5f;
      }
  //end to drawing POINTS
  glEnd();

  //reload Matrix for using translation
  glPopMatrix();
  //draw
  glutSwapBuffers();
}

//Setup Rendering Option
void SetupRC(void)
{
  //set bg clear color
  glClearColor(0.192157f,0.533333f,0.196078f,1.0f);

  //set drawing color
  glColor3f(0.533333f, 0.192157f, 0.490196f);
}

void SpecialKeys(int key, int x, int y)
{
  if(key == GLUT_KEY_UP)
    xRot -= 5.0f;

  if(key == GLUT_KEY_DOWN)
    xRot += 5.0f;

  if(key == GLUT_KEY_LEFT)
    yRot -= 5.0f;

  if(key == GLUT_KEY_RIGHT)
    yRot += 5.0f;

  if(key > 356.0f)
    xRot = 0.0f;

  if(key < -1.0f)
    xRot = 355.0f;

  if(key > 356.0f)
    yRot = 0.0f;

  if(key < -1.0f)
    yRot = 355.0f;

  //Refresh the Window
  glutPostRedisplay();
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
  glutCreateWindow("Spiral Dot - 20130114");
  //set Callback Func - Display Routine
  glutDisplayFunc(RenderScene);
  //set Callback Func - Reshape Routine
  glutReshapeFunc(ChangeSize);
  //set Callback Func - Special Key Input Routine
  glutSpecialFunc(SpecialKeys);
  //set Rendering Option
  SetupRC();
  //Start Routine
  glutMainLoop();
}
