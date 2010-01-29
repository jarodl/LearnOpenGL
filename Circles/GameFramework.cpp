#include "GameFramework.h"

GameFramework::GameFramework( int argc, char* argv[] )
{
	title = DEF_TITLE;
	width = DEF_WIDTH;
	height = DEF_HEIGHT;
	width_ratio = WIDTH_RATIO;
	height_ratio = HEIGHT_RATIO;
    glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );
	glutInitWindowPosition( DEF_POSITION_X, DEF_POSITION_Y );
	glutInitWindowSize( width, height );
}

GameFramework::~GameFramework(void)
{
}

//////////////////////////////
// Wrapper functions
//////////////////////////////

void GameFramework::setInstance(GameFramework * framework)
{
	instance = framework;
}

void GameFramework::renderSceneWrapper()
{
	instance->renderScene();
}

void GameFramework::resizeWindowWrapper(GLsizei w, GLsizei h)
{
	instance->resizeWindow(w, h);
}

void GameFramework::timerFunctionWrapper( int value )
{
	instance->timerFunction( value );
}

void GameFramework::mouseClickWrapper( int mouseButton, int mouseState,
								int mouseXPos, int mouseYPos )
{
	instance->mouseClick( mouseButton, mouseState, mouseXPos, mouseYPos );
}


//////////////////////////////
// Class methods
//////////////////////////////

void GameFramework::startFramework()
{
	glutCreateWindow( title.c_str() );

	float x, y, r;

	for (int i = 0; i < NBR_SHAPES; i++)
	{
		Shape s;
        r = s.getRadius();
		x = Random::GenerateRandomNumber( -1.0 + r, 1.0 - r );
		y = Random::GenerateRandomNumber( -1.0 + r, 1.0 - r );
		s.setPosition( x, y );
		shapes[i] = s;
	}

	glutDisplayFunc( renderSceneWrapper );
	glutReshapeFunc( resizeWindowWrapper );
	glutMouseFunc( mouseClickWrapper );
	glutTimerFunc( 50, timerFunctionWrapper, 1 );
}

void GameFramework::run()
{
	glutMainLoop();
}

void GameFramework::renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT);

	// Display each polygon, applying its spin as needed. //
	for (int i = 0; i < NBR_SHAPES; i++)
		shapes[i].draw();

	glutSwapBuffers();
}

void GameFramework::setTitle( std::string t )
{
	title = t;
}

void GameFramework::setWindowSize( int w, int h )
{
	width = w;
	height = h;
}

void GameFramework::resizeWindow( GLsizei w, GLsizei h )
{
	glViewport(0, 0, w, h);
	width = w;
	height = h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
	{
		width_ratio = 2.0;
		height_ratio = 2.0 * (GLfloat)h / (GLfloat)w;
        glOrtho(-1.0, 1.0, -1.0 * (GLfloat)h / (GLfloat)w, (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	}
    else
	{
		width_ratio = 2.0 * (GLfloat)w / (GLfloat)h;
		height_ratio = 2.0;
        glOrtho(-1.0 * (GLfloat)w / (GLfloat)h, (GLfloat)w / (GLfloat)h, -1.0, 1.0, -10.0, 10.0);
	}
    glMatrixMode(GL_MODELVIEW);
}

void GameFramework::timerFunction( int value )
{
	for ( int i = 0; i <= NBR_SHAPES; i++ )
	{
		// shape to shape collision
		for ( int j = i + 1; j < NBR_SHAPES; j++ )
			if (shapes[i].colliding(shapes[j]))
				shapes[i].resolveCollision(shapes[j]);

        shapes[i].position += shapes[i].velocity;
        shapeToEdgeCollision( shapes[i] );
		
	}

	glutPostRedisplay();
	glutTimerFunc(50, timerFunctionWrapper, 1);
}

void GameFramework::mouseClick( int mouseButton, int mouseState,
								int mouseXPos, int mouseYPos )
{
	GLfloat x = width_ratio * mouseXPos / width - 0.5 * width_ratio;
	GLfloat y = 0.5 * height_ratio - (height_ratio * mouseYPos / height);
	int index = findMouseHit( x, y );
	if ((mouseState == GLUT_DOWN) && (index >= 0))
	{
	}
}

//////////////////////////////
// private methods
//////////////////////////////

/* Function to traverse the star list until the current star contains the */
/* current mouse position, whereupon that star's index is returned. If no */
/* such star exists, an appropriate dummy index (-1) is returned.         */
int GameFramework::findMouseHit(GLfloat mouseX, GLfloat mouseY)
{
	for (int i = 0; i < NBR_SHAPES; i++)
	{
		// Rather than determining whether the mouse-click occured precisely within the
		// shape's boundaries, this function merely checks whether the click is within
		// 90% of the distance between the shape's center and any of its tip vertices.
		if (sqrt(pow(mouseX - shapes[i].position.x, 2)+ pow(mouseY - shapes[i].position.y, 2)) < 
				0.9 * shapes[i].getRadius())
			return i;
	}
	return -1;
}

/* Function to adjust the position of the parameterized polygon to ensure */
/* that the polygon remains inside the boundaries of the display window.  */
void GameFramework::shapeToEdgeCollision( Shape &s )
{
	bool tooHigh, tooLow, tooLeft, tooRight;
	float r = s.getRadius();

	// Determine whether polygon exceeds window boundaries. //
	tooHigh = tooLow = tooLeft = tooRight = false;
	if (s.position.x + r >= width_ratio/2.0)
		tooRight = true;
	else if (s.position.x - r <= -width_ratio/2.0)
		tooLeft = true;
	if (s.position.y  + r >= height_ratio/2.0)
		tooHigh = true;
	else if (s.position.y - r <= -height_ratio/2.0)
		tooLow = true;

	// Adjust position if window bounds exceeded. //
	if (tooRight)
	{
		s.velocity.x *= -1.0;
		s.position.x = width_ratio/2.0 - r;
	}
	else if (tooLeft)
	{
		s.velocity.x *= -1.0;
		s.position.x = -width_ratio/2.0 + r;
	}
	if (tooHigh)
	{
		s.velocity.y *= -1.0;
		s.position.y = height_ratio/2.0 - r;
	}
	else if (tooLow)
	{
		s.velocity.y *= -1.0;
		s.position.y = -height_ratio/2.0 + r;
	}
}
