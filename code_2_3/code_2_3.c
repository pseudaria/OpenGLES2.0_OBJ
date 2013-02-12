#include"openglsb.h"

//Set RenderScene
void RenderScene(void)
{
  //clear bg with present color by setting SetupRC()->glclear()
  glClear(GL_COLOR_BUFFER_BIT);
  //set drawing color for next object
  glColor3f(1.0f,0.0f,1.0f);
  //draw Rectangu with setting drawing-color before
  glRectf(-25.0f,25.0f,25.0f,-25.0f);
  //draw
  glFlush();
}

//Setup Rendering Option
void SetupRC(void)
{
  glClearColor(0.0f,1.0f,1.0f,1.0f);
}

//Change and Modify Window Size
void ChangeSize(GLsizei w, GLsizei h)
{
  GLfloat aspectRatio;

  //can't not divide with 0
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
    glOrtho(-100.0,100.0,-100 / aspectRatio,
	    100 / aspectRatio,
	    1.0, -1.0);
  else
    glOrtho(-100.0 * aspectRatio,
	    100.0 * aspectRatio,
	    -100.0,100.0,1.0,-1.0);
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
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  //Create an Window with X
  glutCreateWindow("GLRect - 20130113");
  //set Callback Func - Display Routine
  glutDisplayFunc(RenderScene);
  //set Callback Func - Reshape Routine
  glutReshapeFunc(ChangeSize);
  //set Rendering Option
  SetupRC();
  //Start Routine
  glutMainLoop();
}
