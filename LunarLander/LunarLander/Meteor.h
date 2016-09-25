#ifndef METEOR_H
#define METEOR_H

class Meteor
{
public:
	Meteor(float width, float height);
	Meteor(float width, float height, float rad);
	void draw();
	void resetMeteor(float width, float height);
	float getPosX() {return posX;};
	void setPosX(float newPosX) {posX = newPosX;};
	float getPosY() {return posY;};
	void setPosY(float newPosY) {posY = newPosY;};
	float getRadius() {return radius;};
	void setRadius(float newRadius) {radius = newRadius;};
	float getDX() {return dX;};
	void setDX(float newDX) {dX = newDX;};
	float getDY() {return dY;};
	void setDY(float newDY) {dY = newDY;};
private:
	float posX, posY, radius, dX, dY;
};

#endif