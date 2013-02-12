// Lines.c
// Demonstrates primative GL_LINES
// OpenGL SuperBible, 3rd Edition
// Richard S. Wright Jr.
// rwright@starstonesoftware.com

#include "./openglsb.h"	// System and OpenGL Stuff


// Define a constant for the value of PI
#define GL_PI 3.1415f

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

///////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
	{
        GLfloat x,y,z,t; // Storeage for coordinates and angles

	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT);

	// Save matrix state and do the rotation
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	// Call only once for all remaining points
	glBegin(GL_LINES);

	y = 0.0f;
	//X axis
	x = 0.0f;
	y = 0.0f;
	glVertex3f(x,y,z);
	x = 150.0f;
	y = 0.0f;
	glVertex3f(x,y,z);
	//Y axis
	x = 0.0f;
	y = 0.0f;
	glVertex3f(x,y,z);
	x = 0.0f;
	y = 150.0f;
	glVertex3f(x,y,z);
	//Z axis
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,0.0f,150.0f);
	for(t = 0.0f; t <= 150.f; t += 1.0f)
	  {
		// Bottom half of the circle
		x = 20*cos(t/GL_PI);
		z = 20*sin(t/GL_PI);
		y = 2*t;
		glVertex3f(x, y, z);	
	  }

	// Done drawing points
	glEnd();

	// Restore transformations
	glPopMatrix();

	// Flush drawing commands
	glutSwapBuffers();
	}

///////////////////////////////////////////////////////////
// This function does any needed initialization on the 
// rendering context. 
void SetupRC()
	{
	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

	// Set drawing color to green
	glColor3f(0.0f, 1.0f, 0.0f);
	}

///////////////////////////////////////////////////////////
// Respond to arrow keys
void SpecialKeys(int key, int x, int y)
	{
	if(key == GLUT_KEY_UP)
		xRot-= 5.0f;

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

	// Refresh the Window
	glutPostRedisplay();
	}

///////////////////////////////////////////////////////////
// Window has changed size, recalculate projection
void ChangeSize(int w, int h)
	{
	GLfloat nRange = 100.0f;

	// Prevent a divide by zero
	if(h == 0)
		h = 1;

	// Set Viewport to window dimensions
    glViewport(0, 0, w, h);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish clipping volume (left, right, bottom, top, near, far)
    if (w <= h) 
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else 
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	}

///////////////////////////////////////////////////////////
// Main Program Entry Point
int main(int argc, char* argv[])
	{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,600);
	glutCreateWindow("Lines Example");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();

	return 0;
	}
