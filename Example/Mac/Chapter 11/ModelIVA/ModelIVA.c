// ModelIVA.c
// OpenGL SuperBible
// Demonstrates rendering a sample model with indexed vertex arrays
// Program by Richard S. Wright Jr.

#include "../../Common/OpenGLSB.h"	// System and OpenGL Stuff
#include "../../Common/GLTools.h"	// OpenGL toolkit
#include <math.h>


// Function in model.c
void DrawModel(void);
        
// Called to draw scene
void RenderScene(void)
    {
    static GLfloat yRot = 0.0f;
    yRot += 0.5f;
        
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        
    glTranslatef(0.0f, 0.0f, -15.f);
    glRotatef(-70.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 0.0f, 1.0f);

    DrawModel();
    
    glPopMatrix();
    
    // Do the buffer Swap
    glutSwapBuffers();
    }


// This function does any needed initialization on the rendering
// context. 
void SetupRC()
    {
    GLint iWidth, iHeight,iComponents;
    GLenum eFormat;
    GLbyte *pBytes;
    GLfloat fAmbLight[] =   { 0.1f, 0.1f, 0.1f };
    GLfloat fDiffLight[] =  { 1.0f, 1.0f, 1.0f };

    // Bluish background
    glClearColor(0.0f, 0.0f, .50f, 1.0f );
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
        
    // Lit texture environment
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    // Load the main texture
    pBytes = gltLoadTGA("hummer.tga", &iWidth, &iHeight, &iComponents, &eFormat);    
    glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, (void *)pBytes);
    free(pBytes);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glEnable(GL_TEXTURE_2D);

    // Set up lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glLightfv(GL_LIGHT0, GL_AMBIENT, fAmbLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, fDiffLight);
    }

///////////////////////////////////////////////////////////
// Called by GLUT library when idle (window not being
// resized or moved)
void TimerFunction(int value)
    {
    // Redraw the scene with new coordinates
    glutPostRedisplay();
    glutTimerFunc(5,TimerFunction, 1);
    }


//////////////////////////////////////////////////////////
// Window has changed size
void ChangeSize(int w, int h)
	{
	GLfloat fAspect;
    GLfloat lightPos[] = { -10.0f, 100.0f, 20.0f, 1.0f };

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
    if(h == 0)
        h = 1;

    glViewport(0, 0, w, h);
        
    fAspect = (GLfloat)w / (GLfloat)h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the clipping volume
	gluPerspective(35.0f, fAspect, 1.0f, 50.0f);
        
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
        
    // Light never changes, put it here
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    }

int main(int argc, char* argv[])
	{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,600);
	glutCreateWindow("Indexed Model Data");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);

	SetupRC();
    glutTimerFunc(5, TimerFunction, 1);

	glutMainLoop();

	return 0;
	}
