#include "openglsb.h"

void RenderScene(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}

void SetupRC(void)
{
  glClearColor(0.98f,0.04f,1.0f,0.7f);
}

void main(int argc, char* argv[])
{
  glutInit(&argc, argv); //Linux
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutCreateWindow("Code_2_1_For goal.");
  glutDisplayFunc(RenderScene);
  SetupRC();
  glutMainLoop();
}
