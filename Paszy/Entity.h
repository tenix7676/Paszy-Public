#pragma once

#include "Vector.h"
#include "Point.h"
#include "SpriteSheet.h"
#include "CollisionSystem.h"

class Map;
class Entity
{
protected:
	static Map* mapRef;



public:
	Vector_2d pos;
	Vector_2d vel;
	TextureCode textureCode;
	double hitboxWidth = SpriteSheet::texture_size;
	double hitboxHeight = SpriteSheet::texture_size;
	double hitboxOffsetX = 0.0;
	double hitboxOffsetY = 0.0;

	static void setMapRef(Map* map);
	Point getMapPos();
	Point getMapPos(Vector_2d somePos);
	Vector_2d getRightFoot();
	Vector_2d getLeftFoot();
	void setPositionFromMap(int tile_x, int tile_y);
	void updatePosition();
	virtual void handleCollision(CollisionDirection side);
	virtual void onEdge() = 0;
};