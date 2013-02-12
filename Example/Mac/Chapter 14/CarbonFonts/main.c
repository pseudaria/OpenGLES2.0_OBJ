// CARBONFONTS Sample program
// Mike Sweet and Nick Haemel

/*
 * Include necessary headers...
 */

#include <stdio.h>
#include <stdlib.h>
#include <Carbon/Carbon.h>
#include <AGL/agl.h>

/*
 * Globals...
 */

float   CubeRotation[3],	/* Rotation of cube */
		CubeRate[3];		/* Rotation rate of cube */
int		CubeMouseButton,	/* Button that was pressed */
		CubeMouseX,		/* Start X position of mouse */
		CubeMouseY;		/* Start Y position of mouse */
int		CubeX,			/* X position of window */
		CubeY,			/* Y position of window */
		CubeWidth,		/* Width of window */
		CubeHeight;		/* Height of window */
int		CubeVisible;		/* Is the window visible? */
AGLContext	CubeContext;		/* OpenGL context */
GLuint		CubeFont;		/* Display list base for font */


/*
 * Functions...
 */

void		DisplayFunc(void);
static pascal OSStatus
		EventHandler(EventHandlerCallRef nextHandler,
		             EventRef event, void *userData);
void		IdleFunc(void);
void		MotionFunc(int x, int y);
void		MouseFunc(int button, int state, int x, int y);
void		ReshapeFunc(int width, int height);


/*
 * 'main()' - Main entry for example program.
 */

int					/* O - Exit status */
main(int  argc,				/* I - Number of command-line args */
     char *argv[])			/* I - Command-line args */
{
  AGLPixelFormat	format;		/* OpenGL pixel format */
  WindowPtr		window;		/* Window */
  int			winattrs;	/* Window attributes */
  Str255		title;		/* Title of window */
  Rect			rect;		/* Rectangle definition */
  EventHandlerUPP	handler;	/* Event handler */
  EventLoopTimerUPP	thandler;	/* Timer handler */
  EventLoopTimerRef	timer;		/* Timer for animating the window */
  ProcessSerialNumber	psn;		/* Process serial number */
  short			font;		/* Font number */
  Str255		fontname;	/* Font name */
  static EventTypeSpec	events[] =	/* Events we are interested in... */
			{
			  { kEventClassMouse, kEventMouseDown },
			  { kEventClassMouse, kEventMouseUp },
			  { kEventClassMouse, kEventMouseMoved },
			  { kEventClassMouse, kEventMouseDragged },
			  { kEventClassWindow, kEventWindowDrawContent },
			  { kEventClassWindow, kEventWindowShown },
			  { kEventClassWindow, kEventWindowHidden },
			  { kEventClassWindow, kEventWindowActivated },
			  { kEventClassWindow, kEventWindowDeactivated },
			  { kEventClassWindow, kEventWindowClose },
			  { kEventClassWindow, kEventWindowBoundsChanged }
			};
  static GLint 		attributes[] =	/* OpenGL attributes */
			{
			  AGL_RGBA,
			  AGL_GREEN_SIZE, 1,
			  AGL_DOUBLEBUFFER,
			  AGL_DEPTH_SIZE, 16,
			  AGL_NONE
			};

//Set initial values for window
const int	    	    origWinHeight = 628;
const int	    	    origWinWidth  = 850;
const int	    	    origWinXOffset = 50;
const int	    	    origWinYOffset = 50;


 /*
  * Create the window...
  */

  CubeContext = 0;
  CubeVisible = 0;

  SetRect(&rect, origWinXOffset, origWinYOffset, origWinWidth, origWinHeight);

  winattrs = kWindowStandardHandlerAttribute | kWindowCloseBoxAttribute |
	     kWindowCollapseBoxAttribute | kWindowFullZoomAttribute |
	     kWindowResizableAttribute | kWindowLiveResizeAttribute;
  winattrs &= GetAvailableWindowAttributes(kDocumentWindowClass);

  strcpy(title + 1, "Carbon OpenGL Example");
  title[0] = strlen(title + 1);

  CreateNewWindow(kDocumentWindowClass, winattrs, &rect, &window);
  SetWTitle(window, title);

  handler = NewEventHandlerUPP(EventHandler);
  InstallWindowEventHandler(window, handler,
			    sizeof(events) / sizeof(events[0]),
			    events, NULL, 0L);
  thandler = NewEventLoopTimerUPP((void (*)(EventLoopTimerRef, void *))IdleFunc);
  InstallEventLoopTimer(GetMainEventLoop(), 0, 0, thandler,
                        0, &timer);

  GetCurrentProcess(&psn);
  SetFrontProcess(&psn);

  DrawGrowIcon(window);

  ShowWindow(window);

 /*
  * Create the OpenGL context and bind it to the window...
  */

  format      = aglChoosePixelFormat(NULL, 0, attributes);
  CubeContext = aglCreateContext(format, NULL);

  if (!CubeContext)
  {
    puts("Unable to get OpenGL context!");
    return (1);
  }

  aglDestroyPixelFormat(format);
  aglSetDrawable(CubeContext, GetWindowPort(window));

 /*
  * Setup remaining globals...
  */

  CubeX           = 50;
  CubeY           = 50;
  CubeWidth       = 400;
  CubeHeight      = 400;
  CubeRotation[0] = 45.0f;
  CubeRotation[1] = 45.0f;
  CubeRotation[2] = 45.0f;
  CubeRate[0]     = 1.0f;
  CubeRate[1]     = 1.0f;
  CubeRate[2]     = 1.0f;

 /*
  * Setup font...
  */

  strcpy(fontname + 1, "Courier New");
  fontname[0] = strlen(fontname + 1);

  GetFNum(fontname, &font);

  CubeFont = glGenLists(96);

  aglUseFont(CubeContext, font, bold, 14, ' ', 96, CubeFont);

//Set the initial size of the cube
ReshapeFunc(origWinWidth - origWinXOffset, origWinHeight - origWinYOffset);

 /*
  * Loop forever...
  */

  for (;;)
  {
    if (CubeVisible)
      SetEventLoopTimerNextFireTime(timer, 0.05);

    RunApplicationEventLoop();

    if (CubeVisible)
    {
     /*
      * Animate the cube...
      */
  
      DisplayFunc();
    }
  }
}


/*
 * 'DisplayFunc()' - Draw a cube.
 */

void
DisplayFunc(void)
{
  int			i, j;		/* Looping vars */
  float         aspectRatio,windowWidth, windowHeight;
  static const GLfloat	corners[8][3] =	/* Corner vertices */
			{
			  {  1.0f,  1.0f,  1.0f },	/* Front top right */
			  {  1.0f, -1.0f,  1.0f },	/* Front bottom right */
			  { -1.0f, -1.0f,  1.0f },	/* Front bottom left */
			  { -1.0f,  1.0f,  1.0f },	/* Front top left */
			  {  1.0f,  1.0f, -1.0f },	/* Back top right */
			  {  1.0f, -1.0f, -1.0f },	/* Back bottom right */
			  { -1.0f, -1.0f, -1.0f },	/* Back bottom left */
			  { -1.0f,  1.0f, -1.0f }	/* Back top left */
			};
  static const int	sides[6][4] =	/* Sides */
			{
			  { 0, 1, 2, 3 },		/* Front */
			  { 4, 5, 6, 7 },		/* Back */
			  { 0, 1, 5, 4 },		/* Right */
			  { 2, 3, 7, 6 },		/* Left */
			  { 0, 3, 7, 4 },		/* Top */
			  { 1, 2, 6, 5 }		/* Bottom */
			};
  static const GLfloat	colors[6][3] =	/* Colors */
			{
			  { 1.0f, 0.0f, 0.0f },		/* Red */
			  { 0.0f, 1.0f, 0.0f },		/* Green */
			  { 1.0f, 1.0f, 0.0f },		/* Yellow */
			  { 0.0f, 0.0f, 1.0f },		/* Blue */
			  { 1.0f, 0.0f, 1.0f },		/* Magenta */
			  { 0.0f, 1.0f, 1.0f }		/* Cyan */
			};


 /*
  * Set the current OpenGL context...
  */
  
  aglSetCurrentContext(CubeContext);

 /*
  * Clear the window...
  */

  glViewport(0, 0, CubeWidth, CubeHeight);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 /*
  * Setup the matrices...
  */

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  aspectRatio = (GLfloat)CubeWidth / (GLfloat)CubeHeight;
if(CubeWidth <= CubeHeight)
{
	    windowWidth = 2.0f;
	    windowHeight = 2.0f / aspectRatio;
	    glOrtho(-2.0f, 2.0f, -windowHeight, windowHeight, 2.0f, -2.0f);
}
else
{
	    windowWidth = 2.0f * aspectRatio;
	    windowHeight = 2.0f;
	    glOrtho(-windowHeight, windowHeight, -2.0f, 2.0f, 2.0f, -2.0f);

}

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotatef(CubeRotation[0], 1.0f, 0.0f, 0.0f);
  glRotatef(CubeRotation[1], 0.0f, 1.0f, 0.0f);
  glRotatef(CubeRotation[2], 0.0f, 0.0f, 1.0f);

 /*
  * Draw the cube...
  */

  glEnable(GL_DEPTH_TEST);

  glBegin(GL_QUADS);

  for (i = 0; i < 6; i ++)
  {
    glColor3fv(colors[i]);
    for (j = 0; j < 4; j ++)
      glVertex3fv(corners[sides[i][j]]);
  }

  glEnd();

 /*
  * Draw lines coming out of the cube...
  */

  glColor3f(1.0f, 1.0f, 1.0f);

  glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, -1.5f);
    glVertex3f(0.0f, 0.0f, 1.5f);

    glVertex3f(-1.5f, 0.0f, 0.0f);
    glVertex3f(1.5f, 0.0f, 0.0f);

    glVertex3f(0.0f, 1.5f, 0.0f);
    glVertex3f(0.0f, -1.5f, 0.0f);
  glEnd();

 /*
  * Draw text for each side...
  */

  glPushAttrib(GL_LIST_BIT);
    glListBase(CubeFont - ' ');

    glRasterPos3f(0.0f, 0.0f, -1.5f);
    glCallLists(4, GL_BYTE, "Back");

    glRasterPos3f(0.0f, 0.0f, 1.5f);
    glCallLists(5, GL_BYTE, "Front");

    glRasterPos3f(-1.5f, 0.0f, 0.0f);
    glCallLists(4, GL_BYTE, "Left");

    glRasterPos3f(1.5f, 0.0f, 0.0f);
    glCallLists(5, GL_BYTE, "Right");

    glRasterPos3f(0.0f, 1.5f, 0.0f);
    glCallLists(3, GL_BYTE, "Top");

    glRasterPos3f(0.0f, -1.5f, 0.0f);
    glCallLists(6, GL_BYTE, "Bottom");
  glPopAttrib();

 /*
  * Swap the front and back buffers...
  */

  aglSwapBuffers(CubeContext);
}


/*
 * 'EventHandler()' - Handle window and mouse events from the window manager.
 */

static pascal OSStatus				/* O - noErr on success or error code */
EventHandler(EventHandlerCallRef nextHandler,	/* I - Next handler to call */
             EventRef            event,		/* I - Event reference */
	     void                *userData)	/* I - User data (not used) */
{
  UInt32		kind;			/* Kind of event */
  Rect			rect;			/* New window size */
  EventMouseButton	button;			/* Mouse button */
  Point			point;			/* Mouse position */


  kind = GetEventKind(event);

  if (GetEventClass(event) == kEventClassWindow)
  {
    switch (kind)
    {
      case kEventWindowDrawContent :
	  if (CubeVisible && CubeContext)
	    DisplayFunc();
	  break;
  
      case kEventWindowBoundsChanged :
	  GetEventParameter(event, kEventParamCurrentBounds, typeQDRectangle,
			    NULL, sizeof(Rect), NULL, &rect);

	  CubeX = rect.left;
	  CubeY = rect.top;

          if (CubeContext)
	    aglUpdateContext(CubeContext);

	  ReshapeFunc(rect.right - rect.left, rect.bottom - rect.top);
  
	  if (CubeVisible && CubeContext)
	    DisplayFunc();
	  break;
  
      case kEventWindowShown :
	  CubeVisible = 1;
	  if (CubeContext)
	    DisplayFunc();
	  break;
  
      case kEventWindowHidden :
	  CubeVisible = 0;
	  break;
  
      case kEventWindowClose :
	  ExitToShell();
	  break;
    }
  }
  else
  {
    switch (kind)
    {
      case kEventMouseDown :
	  GetEventParameter(event, kEventParamMouseButton, typeMouseButton,
			    NULL, sizeof(EventMouseButton), NULL, &button);
	  GetEventParameter(event, kEventParamMouseLocation, typeQDPoint,
			    NULL, sizeof(Point), NULL, &point);

          if (point.v < CubeY ||
	      (point.v > (CubeY + CubeHeight - 8) &&
	       point.h > (CubeX + CubeWidth - 8)))
	    return (CallNextEventHandler(nextHandler, event));

	  MouseFunc(button, 0, point.h, point.v);
	  break;
  
      case kEventMouseUp :
	  GetEventParameter(event, kEventParamMouseButton, typeMouseButton,
			    NULL, sizeof(EventMouseButton), NULL, &button);
	  GetEventParameter(event, kEventParamMouseLocation, typeQDPoint,
			    NULL, sizeof(Point), NULL, &point);

          if (point.v < CubeY ||
	      (point.v > (CubeY + CubeHeight - 8) &&
	       point.h > (CubeX + CubeWidth - 8)))
	    return (CallNextEventHandler(nextHandler, event));

	  MouseFunc(button, 1, point.h, point.v);
	  break;
  
      case kEventMouseDragged :
	  GetEventParameter(event, kEventParamMouseLocation, typeQDPoint,
			    NULL, sizeof(Point), NULL, &point);

          if (point.v < CubeY ||
	      (point.v > (CubeY + CubeHeight - 8) &&
	       point.h > (CubeX + CubeWidth - 8)))
	    return (CallNextEventHandler(nextHandler, event));

	  MotionFunc(point.h, point.v);
	  break;

      default :
	  return (CallNextEventHandler(nextHandler, event));
    }
  }

 /*
  * Return whether we handled the event...
  */

  return (noErr);
}


/*
 * 'IdleFunc()' - Rotate and redraw the cube.
 */

void
IdleFunc(void)
{
  CubeRotation[0] += CubeRate[0];
  CubeRotation[1] += CubeRate[1];
  CubeRotation[2] += CubeRate[2];

  QuitApplicationEventLoop();
}


/*
 * 'MotionFunc()' - Handle mouse pointer motion.
 */

void
MotionFunc(int x,			/* I - X position */
           int y)			/* I - Y position */
{
 /*
  * Get the mouse movement...
  */

  x -= CubeMouseX;
  y -= CubeMouseY;

 /*
  * Update the cube rotation rate based upon the mouse movement and
  * button...
  */

  switch (CubeMouseButton)
  {
    case 0 :				/* Button 1 */
	CubeRate[0] = 0.01f * y;
        CubeRate[1] = 0.01f * x;
	CubeRate[2] = 0.0f;
	break;

    case 1 :				/* Button 2 */
	CubeRate[0] = 0.0f;
	CubeRate[1] = 0.01f * y;
        CubeRate[2] = 0.01f * x;
	break;

    default :				/* Button 3 */
	CubeRate[0] = 0.01f * y;
	CubeRate[1] = 0.0f;
        CubeRate[2] = 0.01f * x;
	break;
  }
}


/*
 * 'MouseFunc()' - Handle mouse button press/release events.
 */

void
MouseFunc(int button,			/* I - Button that was pressed */
          int state,			/* I - Button state (0 = down) */
	  int x,			/* I - X position */
	  int y)			/* I - Y position */
{
 /*
  * Only respond to button presses...
  */

  if (state)
    return;

 /*
  * Save the mouse state...
  */

  CubeMouseButton = button;
  CubeMouseX      = x;
  CubeMouseY      = y;

 /*
  * Zero-out the rotation rates...
  */

  CubeRate[0] = 0.0f;
  CubeRate[1] = 0.0f;
  CubeRate[2] = 0.0f;
}


/*
 * 'ReshapeFunc()' - Resize the window.
 */

void
ReshapeFunc(int width,			/* I - Width of window */
            int height)			/* I - Height of window */
{
  CubeWidth  = width;
  CubeHeight = height;
}

