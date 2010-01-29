#ifndef GAME_FRAMEWORK_H
#define GAME_FRAMEWORK_H

#include <string>
#include "Shape.h"
#include "Random.h"

#if defined( __WIN32__ ) || defined( _WIN32 )
  #include <windows.h>
  #include "glut.h"
#elif defined( __APPLE_CC__ )
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

#define NBR_SHAPES 10
#define DEF_WIDTH 1000
#define DEF_HEIGHT 750
#define WIDTH_RATIO 4.0
#define HEIGHT_RATIO 3.0
#define DEF_POSITION_X 100
#define DEF_POSITION_Y 100
#define DEF_TITLE "GameFramework"

class GameFramework
{
public:
	GameFramework( int argc, char* argv[] );
	~GameFramework(void);

	static void setInstance( GameFramework * framework );
	static void renderSceneWrapper();
	static void resizeWindowWrapper( GLsizei w, GLsizei h );
	static void timerFunctionWrapper( int value );
	static void mouseClickWrapper( int mouseButton, int mouseState,
								int mouseXPos, int mouseYPos );

	void startFramework();
	void run();

	virtual void renderScene();
	virtual void setTitle( std::string t);
	virtual void setWindowSize( int width, int height );
	virtual void resizeWindow( GLsizei w, GLsizei h );
	virtual void timerFunction( int value );
	virtual void mouseClick( int mouseButton, int mouseState,
							int mouseXPos, int mouseYPos);

private:
	int width, height;
	GLfloat width_ratio, height_ratio;
    Shape shapes[NBR_SHAPES];
    std::string title;

	int findMouseHit(GLfloat mouseX, GLfloat mouseY);
	void shapeToEdgeCollision( Shape &s );

};

static GameFramework * instance;

#endif
