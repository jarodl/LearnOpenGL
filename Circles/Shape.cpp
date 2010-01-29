#include "Shape.h"

Shape::Shape(void)
{
	setPosition( 0, 0 );
	Initialize();
}

Shape::Shape( float x, float y )
{
	setPosition( x, y );
	Initialize();
}

Shape::~Shape(void)
{
}

void Shape::setPosition( float x, float y )
{
	position = Vector2D( x, y );
}


void Shape::setRadius( float r )
{
	radius = r;
}

void Shape::setMass( float m )
{
	mass = m;
}

float Shape::getRadius() const
{
	return radius;
}

float Shape::getX() const
{
	return position.x;
}

float Shape::getY() const
{
	return position.y;
}

Vector2D Shape::getVelocity() const
{
	return velocity;
}

float Shape::getMass() const
{
	return mass;
}

Vector2D Shape::getPosition() const
{
	return position;
}

void Shape::draw()
{
	GLfloat ex, why;
	ex = position.x;
	why = position.y;

	glColor3fv(color);
	glBegin(GL_LINE_LOOP);
		for ( int j = 0; j < 360; j++ )
		{
			ex += radius * sin( j * PI_OVER_180);
			why += radius * cos( j * PI_OVER_180);
			glVertex2f(ex, why);
			ex = position.x;
			why = position.y;
		}
	glEnd();

}

bool Shape::colliding( Shape & shape )
{
	float xd = getX() - shape.getX();
	float yd = getY() - shape.getY();

	float sumRadius = getRadius() + shape.getRadius();
	float sqrRadius = sumRadius * sumRadius;

	float distSqr = (xd * xd) + (yd * yd);

	if (distSqr <= sqrRadius)
		return true;

	return false;
}

void Shape::resolveCollision( Shape & shape )
{
	Vector2D delta = position - shape.position;
	float d = delta.Length();
	Vector2D mtd = delta * ( ( ( getRadius() + shape.getRadius() ) - d ) / d );

	float im1 = 1 / getMass();
	float im2 = 1 / shape.getMass();
	
	// speed
	Vector2D v = velocity - shape.velocity;
	float vn = v * (mtd.Normalize());

	// intersecting but moving away
	if ( vn > 0.0f ) return;

	// impulse
	float i = (-(1.0f + RESTITUTION) * vn ) / ( im1 + im2 );
	Vector2D impulse = mtd * i;

	// momentum
	velocity += impulse * im1;
	shape.velocity -= impulse * im1;

}

// private methods

void Shape::Initialize()
{
    color[0] = COLORS[DEF_COLOR][0];
    color[1] = COLORS[DEF_COLOR][1];
    color[2] = COLORS[DEF_COLOR][2];
	mass = MASS;
    radius = DEF_RADIUS;

	// random velocity, and pulse. inc.
	float xv = Random::GenerateRandomNumber(VELOCITY_LB, VELOCITY_UB);
	float yv = Random::GenerateRandomNumber(VELOCITY_LB, VELOCITY_UB);
	velocity = Vector2D(xv, yv);
}
