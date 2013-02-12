#include "openglsb.h"
#include <math.h>
#include <stdio.h>

#define GL_PI 3.1415f

typedef GLfloat GLTVector3[3];

// A clipping's size. its aspectRatio will be set in ChangeSize().
GLfloat clippingWidth;
GLfloat clippingHeight;

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

GLTVector3 vCupVertexs[161];
static GLubyte indexes_circle[32][3];
static GLubyte indexes_quad[128][4];
//---------------------------------//

//Set RenderScene
void RenderScene(void)
{
  //Temporary Vertex Array && Index
  float vertex[161][3];
  GLubyte index_c[32][3];
  GLubyte index_q[128][4];
  //position and angle value
  GLfloat y;
  //line tick range
  GLfloat fSizes[2];
  //current line tick
  GLfloat fCurrSize;
  //Glfloat line tick step
  GLfloat step;
  //int i
  int i;
  
  //clear bg with present color by setting SetupRC() -> glClearColor()
  glClear(GL_COLOR_BUFFER_BIT);

  //set WireFrame Model
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

  //dot size
  //glPointSize(3.0f);

  //save Matrix state and rotate
  glPushMatrix();
  glRotatef(xRot, 1.0f, 0.0f, 0.0f);
  glRotatef(yRot, 0.0f, 1.0f, 0.0f);

  printf("GLubyte %d ,uchar %d\n",sizeof(GLubyte),sizeof(unsigned char));

  //Get Vertex from obj file
  objtovert2(vertex,index_c,index_q);

  for(i=0;i<161;i++)
    {
      if(i<32){
	indexes_circle[i][0] = index_c[i][0];
	indexes_circle[i][1] = index_c[i][1];
	indexes_circle[i][2] = index_c[i][2];
      }
      if(i<128){
	indexes_quad[i][0] = index_q[i][0];
	indexes_quad[i][1] = index_q[i][1];
	indexes_quad[i][2] = index_q[i][2];
	indexes_quad[i][3] = index_q[i][3];
      }
      vCupVertexs[i][0]=vertex[i][0];
      vCupVertexs[i][1]=vertex[i][1];
      vCupVertexs[i][2]=vertex[i][2];
      vCupVertexs[i][0]=vCupVertexs[i][0]*60;
      vCupVertexs[i][1]=vCupVertexs[i][1]*60;
      vCupVertexs[i][2]=vCupVertexs[i][2]*60;
      // printf("(%f,%f,%f)\n",vCupVertexs[i][0],vCupVertexs[i][1],vCupVertexs[i][2]);
    }
  for(i=0;i<32;i++)
    {
      // printf("Tri %d %d %d\n",indexes_circle[i][0],indexes_circle[i][1],indexes_circle[i][2]);
    }
  for(i=0;i<128;i++)
    {
      // printf("Quad %d %d %d %d\n",indexes_quad[i][0],indexes_quad[i][1],indexes_quad[i][2],indexes_quad[i][3]);
    }


  //use Vertex Array
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3,GL_FLOAT,0,vCupVertexs);

  glDrawElements(GL_TRIANGLE_FAN,96,GL_UNSIGNED_BYTE,indexes_circle);
  glDrawElements(GL_QUADS,512,GL_UNSIGNED_BYTE,indexes_quad);

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
  glutCreateWindow("Drawing from OBJ File - 20130126");
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
