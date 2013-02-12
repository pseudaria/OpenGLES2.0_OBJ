//
// main.m
// COCOACUBE
// Mike Sweet
#import <Cocoa/Cocoa.h>
#import <Carbon/Carbon.h>
#import <OpenGL/gl.h>
#import <OpenGL/glext.h>
#import <OpenGL/glu.h>


// Interface definition for our NIB CustomView
// In the NIB builder, derive as subclass named
// Cube from NSOpenGLView. Then assign this to a 
// customview that fills the window.
@interface Cube : NSOpenGLView
    {
    bool	    initialized;
    NSTimer	    *timer;
    float	    rotation[3],
                rate[3];
    int         mouse_x,
	    	    mouse_y;
    GLuint	    font;
    }
@end


//
// 'main()' - Main entry for program.
//

int					// O - Exit status
main(int  argc,				// I - Number of command-line args
     const char *argv[])    // I - Command-line arguments
{
  return (NSApplicationMain(argc, argv));
}


//
// Cube class based upon NSOpenGLView
//

@implementation Cube : NSOpenGLView
{
  bool		initialized;		// Are we initialized?
  NSTimer	*timer;			// Timer for animation

  float		rotation[3],		// Rotation of cube
		rate[3];		// Rotation rate of cube
  int		mouse_x,		// Start X position of mouse
		mouse_y;		// Start Y position of mouse
  GLuint	font;			// Display list base for font

}

//
// 'basicPixelFormat()' - Set the pixel format for the window.
//

+ (NSOpenGLPixelFormat*) basicPixelFormat
{
  static NSOpenGLPixelFormatAttribute	attributes[] =	// OpenGL context attributes
					{
					  NSOpenGLPFAWindow,
					  NSOpenGLPFADoubleBuffer,
					  NSOpenGLPFADepthSize, (NSOpenGLPixelFormatAttribute)16,
					  (NSOpenGLPixelFormatAttribute)nil
					};

  return ([[[NSOpenGLPixelFormat alloc] initWithAttributes:attributes] autorelease]);
}



//
// 'resizeGL()' - Resize the window.
//

- (void) resizeGL
{
}


//
// 'idle()' - Update the display using the current rotation rates...
//

- (void)idle:(NSTimer *)timer
{
  // Rotate...
  rotation[0] += rate[0];
  rotation[1] += rate[1];
  rotation[2] += rate[2];

  // Redraw the window...
  [self drawRect:[self bounds]];
}


//
// 'mouseDown()' - Handle left mouse button presses...
//

- (void)mouseDown:(NSEvent *)theEvent
{
  NSPoint	point;			// Mouse position


  // Get and save the mouse position
  point   = [self convertPoint:[theEvent locationInWindow] fromView:nil];
  mouse_x = point.x;
  mouse_y = point.y;

  // Null the rotation rates...
  rate[0] = 0.0f;
  rate[1] = 0.0f;
  rate[2] = 0.0f;
}


//
// 'rightMouseDown()' - Handle right mouse button presses...
//

- (void)rightMouseDown:(NSEvent *)theEvent
{
  NSPoint	point;			// Mouse position


  // Get and save the mouse position
  point   = [self convertPoint:[theEvent locationInWindow] fromView:nil];
  mouse_x = point.x;
  mouse_y = point.y;

  // Null the rotation rates...
  rate[0] = 0.0f;
  rate[1] = 0.0f;
  rate[2] = 0.0f;
}


//
// 'otherMouseDown()' - Handle middle mouse button presses...
//

- (void)otherMouseDown:(NSEvent *)theEvent
{
  NSPoint	point;			// Mouse position


  // Get and save the mouse position
  point   = [self convertPoint:[theEvent locationInWindow] fromView:nil];
  mouse_x = point.x;
  mouse_y = point.y;

  // Null the rotation rates...
  rate[0] = 0.0f;
  rate[1] = 0.0f;
  rate[2] = 0.0f;
}


//
// 'mouseDragged()' - Handle drags using the left mouse button.
//

- (void)mouseDragged:(NSEvent *)theEvent
{
  NSPoint	point;			// Mouse position


  // Get the mouse position and update the rotation rates...
  point   = [self convertPoint:[theEvent locationInWindow] fromView:nil];
  rate[0] = 0.01f * (mouse_y - point.y);
  rate[1] = 0.01f * (mouse_x - point.x);
}


//
// 'rightMouseDragged()' - Handle drags using the right mouse button.
//

- (void)rightMouseDragged:(NSEvent *)theEvent
{
  NSPoint	point;			// Mouse position


  // Get the mouse position and update the rotation rates...
  point   = [self convertPoint:[theEvent locationInWindow] fromView:nil];
  rate[0] = 0.01f * (mouse_y - point.y);
  rate[2] = 0.01f * (mouse_x - point.x);
}


//
// 'otherMouseDragged()' - Handle drags using the middle mouse button.
//

- (void)otherMouseDragged:(NSEvent *)theEvent
{
  NSPoint	point;			// Mouse position

  // Get the mouse position and update the rotation rates...
  point   = [self convertPoint:[theEvent locationInWindow] fromView:nil];
  rate[1] = 0.01f * (mouse_y - point.y);
  rate[2] = 0.01f * (mouse_x - point.x);
}


- (void)drawRect:(NSRect)rect
{
  int			width,		// Width of window
			height;		// Height of window
  int			i, j;		// Looping vars
  float     aspectRatio, windowWidth, windowHeight;
  static const GLfloat	corners[8][3] =	// Corner vertices
			{
			  {  1.0f,  1.0f,  1.0f },	// Front top right
			  {  1.0f, -1.0f,  1.0f },	// Front bottom right
			  { -1.0f, -1.0f,  1.0f },	// Front bottom left
			  { -1.0f,  1.0f,  1.0f },	// Front top left
			  {  1.0f,  1.0f, -1.0f },	// Back top right
			  {  1.0f, -1.0f, -1.0f },	// Back bottom right
			  { -1.0f, -1.0f, -1.0f },	// Back bottom left
			  { -1.0f,  1.0f, -1.0f }	// Back top left
			};
  static const int	sides[6][4] =	// Sides
			{
			  { 0, 1, 2, 3 },		// Front
			  { 4, 5, 6, 7 },		// Back
			  { 0, 1, 5, 4 },		// Right
			  { 2, 3, 7, 6 },		// Left
			  { 0, 3, 7, 4 },		// Top
			  { 1, 2, 6, 5 }		// Bottom
			};
  static const GLfloat	colors[6][3] =	// Colors
			{
			  { 1.0f, 0.0f, 0.0f },		// Red
			  { 0.0f, 1.0f, 0.0f },		// Green
			  { 1.0f, 1.0f, 0.0f },		// Yellow
			  { 0.0f, 0.0f, 1.0f },		// Blue
			  { 1.0f, 0.0f, 1.0f },		// Magenta
			  { 0.0f, 1.0f, 1.0f }		// Cyan
			};


  // Set the current OpenGL context...
  if (!initialized)
  {
    rotation[0] = 45.0f;
    rotation[1] = 45.0f;
    rotation[2] = 45.0f;
    rate[0]     = 1.0f;
    rate[1]     = 1.0f;
    rate[2]     = 1.0f;
    initialized = true;
  }


  // Use the current bounding rectangle for the cube window...
  width  = rect.size.width;
  height = rect.size.height;

  // Clear the window...
  glViewport(0, 0, width, height);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Setup the matrices...
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    aspectRatio = (GLfloat)width / (GLfloat)height;
    
    if(width <= height)
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
  glRotatef(rotation[0], 1.0f, 0.0f, 0.0f);
  glRotatef(rotation[1], 0.0f, 1.0f, 0.0f);
  glRotatef(rotation[2], 0.0f, 0.0f, 1.0f);

  // Draw the cube...
  glEnable(GL_DEPTH_TEST);

  glBegin(GL_QUADS);

  for (i = 0; i < 6; i ++)
  {
    glColor3fv(colors[i]);
    for (j = 0; j < 4; j ++)
      glVertex3fv(corners[sides[i][j]]);
  }

  glEnd();

  // Draw lines coming out of the cube...
  glColor3f(1.0f, 1.0f, 1.0f);

  glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, -1.5f);
    glVertex3f(0.0f, 0.0f, 1.5f);

    glVertex3f(-1.5f, 0.0f, 0.0f);
    glVertex3f(1.5f, 0.0f, 0.0f);

    glVertex3f(0.0f, 1.5f, 0.0f);
    glVertex3f(0.0f, -1.5f, 0.0f);
  glEnd();


  // Swap the front and back buffers...
  [[self openGLContext]flushBuffer];
}


//
// 'acceptsFirstResponder()' ...
//

- (BOOL)acceptsFirstResponder
{
  return (YES);
}


- (BOOL) becomeFirstResponder
{
  return (YES);
}


- (BOOL) resignFirstResponder
{
  return (YES);
}


//
// 'initWithFrame()' - Initialize the cube.
//

- (id)initWithFrame:(NSRect)frameRect
{
  NSOpenGLPixelFormat	*pf;


  // Get the pixel format and return a new cube window from it...
  pf   = [Cube basicPixelFormat];
  self = [super initWithFrame: frameRect pixelFormat: pf];

  return (self);
}


//
// 'awakeFromNib()' - Do stuff once the UI is loaded from the NIB file...
//

- (void)awakeFromNib
{
  // Set initial values...
  initialized = false;
  
  // Start cube rotating
  [self drawRect: [self bounds]];

  // Start the timer running...
  timer = [NSTimer timerWithTimeInterval:(0.05f) target:self 
           selector:@selector(idle:) userInfo:nil repeats:YES];
  [[NSRunLoop currentRunLoop]addTimer:timer forMode:NSDefaultRunLoopMode];
  [[NSRunLoop currentRunLoop]addTimer:timer forMode:NSEventTrackingRunLoopMode];
}

@end

