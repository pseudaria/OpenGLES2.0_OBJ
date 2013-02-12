#include"openglsb.h"

//RenderScene set
void RenderScene(void)
{
  //clear bg with present color by setting SetupRC()->glclear()
  glClear(GL_COLOR_BUFFER_BIT);
  //draw
  glFlush();
}

//Rendering Option Setup
void SetupRC(void)
{
  glClearColor(0.0f,1.0f,1.0f,1.0f);
}

//Starting Main Program.
void main(int argc, char* argv[])
{
  //Initiate glut
  glutInit(&argc,argv);
  //Initiate DisplayMode
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  //Create an Window with X
  glutCreateWindow("two review");
  //set Callback Func - Display Routine
  glutDisplayFunc(RenderScene);
  //set Rendering Option
  SetupRC();
  //Start Routine
  glutMainLoop();
}
