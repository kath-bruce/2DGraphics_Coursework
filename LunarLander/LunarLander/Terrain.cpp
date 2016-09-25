#include "Terrain.h"
#include "random.h"
#include <gl/glut.h>
#include <iostream>

using namespace std;

Terrain::Terrain(int height)
{
	numPoints = 50;
	points = new int[numPoints];
	for (int i = 0; i < numPoints; i++)
		points[i] = rnd(height);
}

Terrain::Terrain(int numPoints, int height)
{
	this->numPoints = numPoints;
	points = new int[numPoints];
	for (int i = 0; i < numPoints; i++)
		points[i] = rnd(height);
}

void Terrain::drawTerrain(int width)
{
	int numPoints20 = numPoints * 0.2;
	int numPoints40 = numPoints * 0.4;
	int numPoints60 = numPoints * 0.6;
	int numPoints80 = numPoints * 0.8;

	glColor3f(0.5, 0.5, 0.5);
	glLineWidth(2);
	glBegin(GL_POLYGON);
	glVertex2f(width/2, 0);
	glVertex2f(-100, -100);
	for (int i = 0; i < numPoints; i++)
	{
		int prevPoint = points[i - 1];

		while ((i > numPoints20 && i < numPoints40) ^ (i > numPoints60 && i < numPoints80))
		{
			points[i] = prevPoint;
			glVertex2f((width / numPoints)*i, prevPoint);
			i++;
		}
			glVertex2f((width / numPoints)*i, points[i]);
	}

	glVertex2f(width + 100, -100);
	glEnd();

	glColor3f(0.75, 0.75, 0.75);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-100, -100);
	for (int i = 0; i < numPoints; i++)
	{
		int prevPoint = points[i - 1];

		while ((i > numPoints20 && i < numPoints40) ^ (i > numPoints60 && i < numPoints80))
		{
			points[i] = prevPoint;
			glVertex2f((width / numPoints)*i, prevPoint);
			i++;
		}
			glVertex2f((width / numPoints)*i, points[i]);
	}

	glVertex2f(width + 100, -100);
	glEnd();
}

void Terrain::setPoints(int height)
{
	points = new int[numPoints];
	for (int i = 0; i < numPoints; i++)
		points[i] = rnd(height);
}

bool Terrain::checkCollisionWithPoint(float uppY, float lowY, int pointElement)
{
	if (points[pointElement] < uppY && points[pointElement] > lowY)
		return true;

	return false;
}