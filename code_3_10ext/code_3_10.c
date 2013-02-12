#include "openglsb.h"
#include <math.h>
#include <stdio.h>

#define GL_PI 3.1415f

// A clipping's size. its aspectRatio will be set in ChangeSize().
GLfloat clippingWidth;
GLfloat clippingHeight;

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat Vertex[16][2] =
  {
    {-2.5f, 0.8f},
    {-1.7f, 1.5f},
    {-0.7f, 1.9f},
    {0.0f, 1.0f},
    {0.2f, 0.7f},
    {0.6f, 0.0f},
    {1.0f, -0.5f},
    {0.9f, -1.3f},
    {0.6f, -1.9f},
    {0.1f, -2.1f},
    {-0.3f, -1.4f},
    {-0.4f, -0.7f},
    {0.0f, 0.0f},
    {0.9f, 0.5f},
    {1.4f, 0.7f},
    {1.9f, 0.8f}
  };

//---------------------------------//

//Set RenderScene
void RenderScene(void)
{
  //set count value
  int i=0;
  //set stippling factor
  GLint factor = 1;
  //set stippling pattern
  GLushort pattern = 0x5555;
  //set Line Width
  //Line width range and Granularity
  GLfloat line_size;
  GLfloat l_width_range[2];
  GLfloat l_width_step;

  //clear bg with present color by setting SetupRC() -> glClearColor()
  glClear(GL_COLOR_BUFFER_BIT);

  //save Matrix state and rotate
  glPushMatrix();
  glRotatef(xRot, 1.0f, 0.0f, 0.0f);
  glRotatef(yRot, 0.0f, 1.0f, 0.0f);

  //enable line stippling
  glEnable(GL_LINE_STIPPLE);

  //get minimum line width and setup Line Width
  glGetFloatv(GL_LINE_WIDTH_RANGE,l_width_range);
  glGetFloatv(GL_LINE_WIDTH_GRANULARITY,&l_width_step);
  line_size = l_width_range[0] + l_width_step * 10;
  glLineWidth(line_size);

  //initiate setting for stipple factor and pattern
  glLineStipple(factor,pattern);

  //start to drawing LINE_STRIP
  glBegin(GL_LINE_STRIP);
  //set a point's position
  for(i=0; i<16; i++)
    {
      glVertex2f(Vertex[i][0]*24,Vertex[i][1]*24);
    }
  //end to drawing LINE_STRIP
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
  glClearColor(0.13f,0.43f,0.86f,1.0f);

  //set drawing color
  glColor3f(0.7f, 0.2f, 0.2f);
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
  glutCreateWindow("Stippled Line - one bit to increasing factor - 20130116");
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
