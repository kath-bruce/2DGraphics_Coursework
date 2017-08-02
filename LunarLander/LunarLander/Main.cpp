#include <GL/glut.h>
#include <GL/freeglut.h>
#include "Bitmap.h"
#include "Terrain.h"
#include "Lander.h"
#include "Meteor.h"
#include <sstream>
#include <cmath>

using namespace std;

int interval = 1000 / 60;
int width = 1000;
int height = 768;

int timesPlayed = 0;
int timesWon = 0;
int timesLost = 0;
bool gameOn = true;

const float GRAVITY = 0.01;

Bitmap *background;
Bitmap *landerSprite;
Lander *lander;
Terrain *terrain;
Meteor *meteor;

string float2str(float x) 
{
	stringstream ss;
	ss << x;
	return ss.str( );
}

void drawText(float x, float y, string text) 
{
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(x, y);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)text.c_str());
}

void enable2D(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init()
{
	background = new Bitmap("../LunarLander/space_background.bmp", false);
	terrain = new Terrain(height/3);
	landerSprite = new Bitmap("../LunarLander/landerStrip.bmp", true);
	lander = new Lander(landerSprite, width, height); lander->setFuel(7.5);
	meteor = new Meteor(width, height);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	background->draw(0, 0, width, height);
	terrain->drawTerrain(width);
	lander->draw();
	meteor->draw();
	drawText(10, height - 25, "Fuel: " + float2str(lander->getFuel()));
	drawText(10, height - 35, "DY: " + float2str(lander->getDY()));
	drawText(10, height - 45, "DX: " + float2str(lander->getDX()));
	drawText(10, height - 55, "Total Velocity: " + float2str(hypotf(lander->getDX(), lander->getDY())));

	if (lander->getLanderState() == CRASHED)
		drawText(width/2, height - 25, "Crashed");

	if (lander->getLanderState() == LANDEDSAFELY)
		drawText(width/2, height - 25, "Landed safely");

	if (lander->getFuel() == 0)
		drawText(width/2, height - 35, "No Fuel");

	drawText(width - 200, height - 25, "Times Played: " + float2str(timesPlayed));
	drawText(width - 200, height - 35, "Times Won: " + float2str(timesWon));
	drawText(width - 200, height - 45, "Times Lost: " + float2str(timesLost));
	
	if (timesPlayed > 0)
	{
		float winRate = ((float) timesWon / (float) timesPlayed) * 100;
		drawText(width - 200, height - 55, "Win Rate: " + float2str(winRate) + "%");
	}

	glutPostRedisplay();
}

int checkCollision()
{
	int numPoints20 = terrain->getNumPoints() * 0.2;
	int numPoints40 = terrain->getNumPoints() * 0.4;
	int numPoints60 = terrain->getNumPoints() * 0.6;
	int numPoints80 = terrain->getNumPoints() * 0.8;

	for (int i = 0; i < terrain->getNumPoints(); i++)
	{
		if ((width/terrain->getNumPoints())*i > lander->getPosX() - lander->getLanderWidth()/2 && 
			(width/terrain->getNumPoints())*i < lander->getPosX() + lander->getLanderWidth()/2)
		{
			if (terrain->checkCollisionWithPoint(lander->getPosY() + lander->getLanderHeight()/2, 
				lander->getPosY() - (lander->getLanderHeight()/2) + 10, i))
			{
				if ((i > numPoints20 && i < numPoints40) ^ (i > numPoints60 && i < numPoints80))
					//collision with flat terrain
						return 2;

				//collision with spike
				return 1;
			}
		}
	}

	//no collision
	return 0;
}

void updateLander(bool landed)
{
	if (!landed)
	{
		lander->setDY(lander->getDY() - GRAVITY);
		lander->setPosY(lander->getPosY() + lander->getDY());
	} 

	if (lander->getPosX() < lander->getLanderWidth()/2)
	{
		lander->setDX(0);
		lander->setPosX(lander->getPosX() + 0.5);
	} 
	else if (lander->getPosX() > width - (lander->getLanderWidth()/2) - 10)
	{
		lander->setDX(0);
		lander->setPosX(lander->getPosX() - 0.5);
	}

	if (lander->getDX() > 0)
		lander->setDX(lander->getDX() - 0.01);
	else if (lander->getDX() < 0 )
		lander->setDX(lander->getDX() + 0.01);

	if (landed)
	{
		lander->setDX(0); 
		lander->setDY(0);
	}

	lander->setPosX(lander->getPosX() + lander->getDX());
	lander->move();
}

void updateMeteor()
{
	meteor->setPosX(meteor->getPosX() + meteor->getDX());
	meteor->setPosY(meteor->getPosY() + meteor->getDY());

	if (meteor->getPosY() < -meteor->getRadius())
		meteor->resetMeteor(width, height);
}

void update()
{
	updateMeteor();

	bool landed = false;
	int collisionCheck = checkCollision();

	if (collisionCheck == 1)
	{
		lander->setLanderState(CRASHED);
		if (gameOn)
		{
			timesPlayed++;
			timesLost++;
		}
		gameOn = false;
		landed = true;
	} 
	else if (collisionCheck == 2)
	{
		if (hypotf(lander->getDX(), lander->getDY()) > 1.0)
		{
			lander->setLanderState(CRASHED);
			if (gameOn)
			{
				timesPlayed++;
				timesLost++;
			}
			gameOn = false;
		}
		else if (lander->getLanderState() != CRASHED)
		{
			lander->setLanderState(LANDEDSAFELY);
			if (gameOn)
			{
				timesPlayed++;
				timesWon++;
			}
			gameOn = false;
		}

		landed = true;
	}

	updateLander(landed);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		if (!lander->IsUsingFuel() && lander->getFuel() > 0 && lander->getLanderState() == INFLIGHT)
		{
			lander->nextCell();
			lander->setIsUsingFuel(true);
		}

		lander->setDX(lander->getDX() - lander->getFuelBurn());
		lander->burnFuel();

		break;
	case 'd':
		if (!lander->IsUsingFuel() && lander->getFuel() > 0 && lander->getLanderState() == INFLIGHT)
		{
			lander->nextCell();
			lander->setIsUsingFuel(true);
		}

		lander->setDX(lander->getDX() + lander->getFuelBurn());
		lander->burnFuel();

		break;
	case 'w':
		if (!lander->IsUsingFuel() && lander->getFuel() > 0 && lander->getLanderState() == INFLIGHT)
		{
			lander->nextCell();
			lander->setIsUsingFuel(true);
		}

		lander->setDY(lander->getDY() + lander->getFuelBurn());
		lander->burnFuel();

		break;
	default:
		break;
	}
}

void keyboardUp(unsigned char key, int x, int y)
{
	if (lander->IsUsingFuel())
		lander->nextCell();

	lander->setIsUsingFuel(false);
}

void timer(int value)
{
	update();
	glutTimerFunc(interval, timer, 0);
}

void handle_menu(int item)
{
	switch(item)
	{
	case 1:
		delete background;
		delete lander;
		delete landerSprite;
		delete terrain;
		gameOn = true;
		init();
		break;
	case 0:
		exit(0);
		break;
	default:
		break;
	}
}

void init_menu()
{
	glutCreateMenu(handle_menu);
	glutAddMenuEntry("Restart", 1);
	glutAddMenuEntry("Quit", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(250, 20);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("LUNAR LANDER");
	enable2D(width, height);
	init();
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 0);
	init_menu();
	glutMainLoop();

	//delete pointers
	delete background;
	delete lander;
	delete landerSprite;
	delete terrain;
	delete meteor;
}
