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
static GLubyte indexes_circle[] = {33, 1, 2,
				   33, 2, 3,
				   33, 3, 4,
				   33, 4, 5,
				   33, 5, 6,
				   33, 6, 7,
				   33, 7, 8,
				   33, 8, 9,
				   33, 9, 10,
				   33, 10, 11,
				   33, 11, 12,
				   33, 12, 13,
				   33, 13, 14,
				   33, 14, 15,
				   33, 15, 16,
				   33, 16, 17,
				   33, 17, 18,
				   33, 18, 19,
				   33, 19, 20,
				   33, 20, 21,
				   33, 21, 22,
				   33, 22, 23,
				   33, 23, 24,
				   33, 24, 25,
				   33, 25, 26,
				   33, 26, 27,
				   33, 27, 28,
				   33, 28, 29,
				   33, 29, 30,
				   33, 30, 31,
				   33, 31, 32,
				   32, 1, 33};
static GLubyte indexes_quad[] = { 1, 32, 35, 34,
				  32, 31, 36, 35,
				  31, 30, 37, 36,
				  30, 29, 38, 37,
				  29, 28, 39, 38,
				  28, 27, 40, 39,
				  27, 26, 41, 40,
				  26, 25, 42, 41,
				  25, 24, 43, 42,
				  24, 23, 44, 43,
				  23, 22, 45, 44,
				  22, 21, 46, 45,
				  21, 20, 47, 46,
				  20, 19, 48, 47,
				  19, 18, 49, 48,
				  18, 17, 50, 49,
				  17, 16, 51, 50,
				  16, 15, 52, 51,
				  15, 14, 53, 52,
				  14, 13, 54, 53,
				  13, 12, 55, 54,
				  12, 11, 56, 55,
				  11, 10, 57, 56,
				  10, 9, 58, 57,
				  9, 8, 59, 58,
				  8, 7, 60, 59,
				  7, 6, 61, 60,
				  6, 5, 62, 61,
				  5, 4, 63, 62,
				  4, 3, 64, 63,
				  3, 2, 65, 64,
				  2, 1, 34, 65,
				  34, 98, 100, 65,
				  98, 99, 101, 100,
				  99, 66, 67, 101,
				  65, 100, 102, 64,
				  100, 101, 103, 102,
				  101, 67, 68, 103,
				  64, 102, 104, 63,
				  102, 103, 105, 104,
				  103, 68, 69, 105,
				  63, 104, 106, 62,
				  104, 105, 107, 106,
				  105, 69, 70, 107,
				  62, 106, 108, 61,
				  106, 107, 109, 108,
				  107, 70, 71, 109,
				  61, 108, 110, 60,
				  108, 109, 111, 110,
				  109, 71, 72, 111,
				  60, 110, 112, 59,
				  110, 111, 113, 112,
				  111, 72, 73, 113,
				  59, 112, 114, 58,
				  112, 113, 115, 114,
				  113, 73, 74, 115,
				  58, 114, 116, 57,
				  114, 115, 117, 116,
				  115, 74, 75, 117,
				  57, 116, 118, 56,
				  116, 117, 119, 118,
				  117, 75, 76, 119,
				  56, 118, 120, 55,
				  118, 119, 121, 120,
				  119, 76, 77, 121,
				  55, 120, 122, 54,
				  120, 121, 123, 122,
				  121, 77, 78, 123,
				  54, 122, 124, 53,
				  122, 123, 125, 124,
				  123, 78, 79, 125,
				  53, 124, 126, 52,
				  124, 125, 127, 126,
				  125, 79, 80, 127,
				  52, 126, 128, 51,
				  126, 127, 129, 128,
				  127, 80, 81, 129,
				  51, 128, 130, 50,
				  128, 129, 131, 130,
				  129, 81, 82, 131,
				  50, 130, 132, 49,
				  130, 131, 133, 132,
				  131, 82, 83, 133,
				  49, 132, 134, 48,
				  132, 133, 135, 134,
				  133, 83, 84, 135,
				  48, 134, 136, 47,
				  134, 135, 137, 136,
				  135, 84, 85, 137,
				  47, 136, 138, 46,
				  136, 137, 139, 138,
				  137, 85, 86, 139,
				  46, 138, 140, 45,
				  138, 139, 141, 140,
				  139, 86, 87, 141,
				  45, 140, 142, 44,
				  140, 141, 143, 142,
				  141, 87, 88, 143,
				  44, 142, 144, 43,
				  142, 143, 145, 144,
				  143, 88, 89, 145,
				  43, 144, 146, 42,
				  144, 145, 147, 146,
				  145, 89, 90, 147,
				  42, 146, 148, 41,
				  146, 147, 149, 148,
				  147, 90, 91, 149,
				  41, 148, 150, 40,
				  148, 149, 151, 150,
				  149, 91, 92, 151,
				  40, 150, 152, 39,
				  150, 151, 153, 152,
				  151, 92, 93, 153,
				  39, 152, 154, 38,
				  152, 153, 155, 154,
				  153, 93, 94, 155,
				  38, 154, 156, 37,
				  154, 155, 157, 156,
				  155, 94, 95, 157,
				  37, 156, 158, 36,
				  156, 157, 159, 158,
				  157, 95, 96, 159,
				  36, 158, 160, 35,
				  158, 159, 161, 160,
				  159, 96, 97, 161,
				  35, 160, 98, 34,
				  160, 161, 99, 98,
				  161, 97, 66, 99};
//---------------------------------//

//Set RenderScene
void RenderScene(void)
{
  //Temporary Vertex Array
  float vertex[161][3];
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

  //Get Vertex from obj file
  objtovert2(vertex);

  for(i=0;i<161;i++)
    {
      vCupVertexs[i][0]=vertex[i][0];
      vCupVertexs[i][1]=vertex[i][1];
      vCupVertexs[i][2]=vertex[i][2];
      vCupVertexs[i][0]=vCupVertexs[i][0]*60;
      vCupVertexs[i][1]=vCupVertexs[i][1]*60;
      vCupVertexs[i][2]=vCupVertexs[i][2]*60;
      // printf("(%f,%f,%f)\n",vCupVertexs[i][0],vCupVertexs[i][1],vCupVertexs[i][2]);
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
