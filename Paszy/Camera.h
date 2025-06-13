#pragma once

#include "Point.h"
#include "Vector.h"

class Camera
{
public:
	Point pos;
	int width, height;

	void update(int width, int height, Vector_2d player_pos);
};