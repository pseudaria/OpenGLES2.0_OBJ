// StarField.c
// OpenGL SuperBible
// Demonstrates using Vertex Arrays
// Program by Richard S. Wright Jr.
#include "../../Common/OpenGLSB.h"	// System and OpenGL Stuff
#include "../../Common/GLTools.h"       // OpenGL Tools library
#include <math.h>


// Array of small stars
#define SMALL_STARS 150
GLTVector2  vSmallStars[SMALL_STARS];

#define MEDIUM_STARS   40
GLTVector2 vMediumStars[MEDIUM_STARS];

#define LARGE_STARS 15
GLTVector2 vLargeStars[LARGE_STARS];

#define SCREEN_X    800
#define SCREEN_Y    600



// This function does any needed initialization on the rendering
// context. 
void SetupRC()
    {
    int i;
        
    // Populate star list
    for(i = 0; i < SMALL_STARS; i++)
        {
        vSmallStars[i][0] = (GLfloat)(rand() % SCREEN_X);
        vSmallStars[i][1] = (GLfloat)(rand() % (SCREEN_Y - 100))+100.0f;
        }
            
    // Populate star list
    for(i = 0; i < MEDIUM_STARS; i++)
        {
        vMediumStars[i][0] = (GLfloat)(rand() % SCREEN_X * 10)/10.0f;
        vMediumStars[i][1] = (GLfloat)(rand() % (SCREEN_Y - 100))+100.0f;
        }

    // Populate star list
    for(i = 0; i < LARGE_STARS; i++)
        {
        vLargeStars[i][0] = (GLfloat)(rand() % SCREEN_X*10)/10.0f;
        vLargeStars[i][1] = (GLfloat)(rand() % (SCREEN_Y - 100)*10.0f)/ 10.0f +100.0f;
        }
            
            
    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

    // Set drawing color to white
    glColor3f(0.0f, 0.0f, 0.0f);
    }


///////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
    {
    GLfloat x = 700.0f;     // Location and radius of moon
    GLfloat y = 500.0f;
    GLfloat r = 50.0f;
    GLfloat angle = 0.0f;   // Another looping variable
		        
    // Clear the window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         
    // Everything is white
    glColor3f(1.0f, 1.0f, 1.0f);
    
    // Using vertex arrays
    glEnableClientState(GL_VERTEX_ARRAY);
    
    // Draw small stars
    glPointSize(1.0f);
//  This code is no longer needed
//    glBegin(GL_POINTS);
//        for(i = 0; i < SMALL_STARS; i++)
//            glVertex2fv(vSmallStars[i]);
//    glEnd();

    // Newer vertex array functionality
    glVertexPointer(2, GL_FLOAT, 0, vSmallStars);
    glDrawArrays(GL_POINTS, 0, SMALL_STARS);
  
        
                    
    // Draw medium sized stars
    glPointSize(3.05f);
    glVertexPointer(2, GL_FLOAT, 0, vMediumStars);
    glDrawArrays(GL_POINTS, 0, MEDIUM_STARS);
              
    // Draw largest stars
    glPointSize(5.5f);
    glVertexPointer(2, GL_FLOAT, 0, vLargeStars);
    glDrawArrays(GL_POINTS, 0, LARGE_STARS);
        
    // Draw the "moon"
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for(angle = 0; angle < 2.0f * 3.141592f; angle += 0.1f)
            glVertex2f(x + (float)cos(angle) * r, y + (float)sin(angle) * r);
            glVertex2f(x + r, y);
    glEnd();

    // Draw distant horizon
    glLineWidth(3.5);
    glBegin(GL_LINE_STRIP);
        glVertex2f(0.0f, 25.0f);
        glVertex2f(50.0f, 100.0f);
        glVertex2f(100.0f, 25.0f);
        glVertex2f(225.0f, 125.0f);
        glVertex2f(300.0f, 50.0f);
        glVertex2f(375.0f, 100.0f);
        glVertex2f(460.0f, 25.0f);
        glVertex2f(525.0f, 100.0f);
        glVertex2f(600.0f, 20.0f);
        glVertex2f(675.0f, 70.0f);
        glVertex2f(750.0f, 25.0f);
        glVertex2f(800.0f, 90.0f);    
    glEnd();


    // Swap buffers
    glutSwapBuffers();
    }



//////////////////////////////////////////////////////////////////////////
// Called at least once to set coordinates
void ChangeSize(int w, int h)
    {
    // Prevent a divide by zero
    if(h == 0)
        h = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);

    // Reset projection matrix stack
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Establish clipping volume (left, right, bottom, top, near, far)
    gluOrtho2D(0.0, SCREEN_X, 0.0, SCREEN_Y);


    // Reset Model view matrix stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    }

//////////////////////////////////////////////////////////////////////
// Main entrypoint
int main(int argc, char* argv[])
	{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Vertex Array Star Field");
		
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();

	return 0;
	}
