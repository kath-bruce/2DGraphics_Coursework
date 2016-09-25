#ifndef TERRAIN_H
#define TERRAIN_H

class Terrain
{
public:
	Terrain(int height);
	Terrain(int numPoints, int height);
	void drawTerrain(int width);
	void setPoints(int height);
	bool checkCollisionWithPoint(float uppY, float lowY, int pointElement);
	void setNumPoints(int numOfPoints) {numPoints = numOfPoints;};
	int getNumPoints() {return numPoints;};
private:
	int numPoints;
	int *points;
};

#endif
