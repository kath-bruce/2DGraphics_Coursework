#ifndef LANDER_H
#define LANDER_H

#include "AniSprite.h"
#include "Bitmap.h"

enum LanderState
{
	CRASHED, LANDEDSAFELY, INFLIGHT
};

class Lander
{
public:
	Lander(Bitmap* spriteSheet, int width, int height);
	void draw();
	void nextCell();
	void move();
	float getPosX() { return posX; };
	void setPosX(float newPosX) { posX = newPosX; };
	float getPosY() { return posY; };
	void setPosY(float newPosY) { posY = newPosY; };
	float getDX() { return dx; };
	void setDX(float newDX) { dx = newDX; };
	float getDY() { return dy; };
	void setDY(float newDY) { dy = newDY; };
	float getFuel() { return fuel; };
	void setFuel(float newFuel) { fuel = newFuel; };
	float getFuelBurn() {return fuelBurn;};
	void setFuelBurn(float newFuelBurn) {fuelBurn = newFuelBurn;};
	bool IsUsingFuel() { return isUsingFuel; };
	void setIsUsingFuel(bool fuelUsage) { isUsingFuel = fuelUsage; };
	LanderState getLanderState() { return landerState; };
	void setLanderState(LanderState newLanderState) { landerState = newLanderState; };
	int getLanderWidth();
	int getLanderHeight();
	void burnFuel();
private:
	AniSprite* sprite;
	float posX, posY, dx, dy;
	float fuel, fuelBurn;
	bool isUsingFuel;
	LanderState landerState;
};

#endif
