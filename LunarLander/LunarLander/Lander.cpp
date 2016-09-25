#include "Lander.h"
#include "AniSprite.h"
#include "Bitmap.h"
#include "random.h"
#include <GL/glut.h>

Lander::Lander(Bitmap* spriteSheet, int width, int height)
{
	posX = rnd(width/10, width - (width/10));
	posY = height - 50;

	sprite = new AniSprite(posX, posY, spriteSheet, 2, 1);
	sprite->setReferencePixel(20, 25);
	sprite->setUpdatemode(UPDATEONASK);
	sprite->setDrawmode(NOFLIP);

	dx = 0.0;
	dy = 0.0;

	fuel = 10;
	fuelBurn = 0.05;

	isUsingFuel = false;

	landerState = INFLIGHT;
}

void Lander::draw()
{
	sprite->draw();
}

void Lander::move()
{
	sprite->move(dx, dy);
}

void Lander::nextCell()
{
	sprite->nextCell();
}

void Lander::burnFuel()
{
	fuel -= fuelBurn;
	if (fuel <= 0)
	{
		fuelBurn = 0;
		fuel = 0.0;
	}
}

int Lander::getLanderWidth()
{
	return sprite->getWidth();
}

int Lander::getLanderHeight()
{
	return sprite->getHeight();
}