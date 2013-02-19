#include <GL/glut.h> 
#include <math.h>

void log_routine(double *x, double *y){
*y = log(*x);
*x += 0.01;
};


/* 그래픽 창(윈도우)를 초기화 한다.*/
void winInit(void){
    gluOrtho2D(-10.0, 100, -60, 60);
};

/* 콜백함수:
    화면을 다시 그릴때 어떻게 할 것인가?*/
void display(void){
int step = 10000;
int i;
double x=0.01;
double y;
    glColor3f(0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

glBegin(GL_LINES);
for(i=0; i<120; i++)
{
glVertex2f(i-10,-0.3);
glVertex2f(i-10,0.3);

glVertex2f(-0.3,i-60);
glVertex2f(0.3,i-60);
}
glEnd();

glBegin(GL_POINTS);

for(i=0; i<11000; i++)
{
glVertex2f(i*0.01-10,0);
}
for(i=0; i<11000; i++)
{
glVertex2f(0,i*0.01-60);
}


for(i=0; i<10000; i++)
{
log_routine(&x,&y);
glVertex2f(x,y);
}
glEnd();

     glFlush();
};


int main(int argc, char **argv)  {  
  /* GLUT초기화 */
  glutInit(&argc, argv);  
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  
  glutInitWindowPosition(5,5);  
  glutInitWindowSize(300,300);
  
  /*창을 하나 연다. */
  glutCreateWindow("Log(e,x)");  
  
  /* 창을 초기화 한다. */
  winInit();

  /* 콜백함수를 등록한다. */
  glutDisplayFunc(display);  

  /* 이벤트처리기를 실행한다.*/
  glutMainLoop();  
  
  return 0;  
}  
