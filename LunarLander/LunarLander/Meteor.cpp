#include <GL\glut.h>
#include <cmath>
#include "Meteor.h"
#include "random.h"

Meteor::Meteor(float width, float height)
{
	posX = rnd(-50, width + 50);
	radius = 15;
	posY = height + radius;
	if (posX > width/2)
		dX = -1.0;
	else 
		dX = 1.0;
	dY = -1.0;
}

Meteor::Meteor(float width, float height, float rad)
{
	posX = rnd(-50, width + 50);
	radius = rad;
	posY = height + radius;
	if (posX > width/2)
		dX = -1.0;
	else 
		dX = 1.0;
	dY = -1.0;
}

void Meteor::resetMeteor(float width, float height)
{
	posX = rnd(-50, width + 50);
	posY = height + radius;
	if (posX > width/2)
		dX = -1.0;
	else 
		dX = 1.0;
}

void Meteor::draw()
{
	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_POLYGON);
	const int NPOINTS = 25;
	const float TWOPI = 2 * 3.1415927;
	const float STEP = TWOPI / NPOINTS;
	for (float angle = 0; angle < TWOPI; angle += STEP)
		glVertex2f(posX + radius*cos(angle), posY + radius*sin(angle));
	glEnd();

	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_LINE_LOOP);
	for (float angle = 0; angle < TWOPI; angle += STEP)
		glVertex2f(posX + radius*cos(angle), posY + radius*sin(angle));
	glEnd();
}