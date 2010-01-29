#ifndef SHAPE_H
#define SHAPE_H

#include "Vector2D.h"
#include "Random.h"

#if defined( __WIN32__ ) || defined( _WIN32 )
  #include <windows.h>
  #include "glut.h"
#elif defined( __APPLE_CC__ )
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

#define RESTITUTION   0.742
#define PI_OVER_180   0.0174532925f
#define NBR_COLORS    6
#define DEF_COLOR     3 // red
#define MASS          1.0
#define DEF_RADIUS    0.08
#define VELOCITY_LB   -0.050
#define VELOCITY_UB   0.050

const float COLORS[NBR_COLORS][3] = { { 0.4, 0.9, 0.9 }, // Cyan
								    { 0.4, 0.4, 0.9 },   // Blue
								    { 0.9, 0.0, 0.6 },   // Violet
								    { 0.9, 0.4, 0.4 },   // Red
								    { 0.9, 0.7, 0.4 },   // Orange
								    { 0.9, 0.9, 0.4 } }; // Yellow

class Shape
{
public:
	Vector2D position;
	Vector2D velocity;

	Shape(void);
	Shape(float x, float y);
	~Shape(void);

	void setPosition( float x, float y );
	void setRadius( float r );
	void setMass( float m );

	float getRadius() const;
	float getX() const;
	float getY() const;
	Vector2D getVelocity() const;
	float getMass() const;
	Vector2D getPosition() const;

	virtual void draw();
	bool colliding( Shape & shape );
	void resolveCollision ( Shape & shape );

protected:
	float radius;
	float mass;
	float color[3];
	
	void Initialize();

};
#endif
