#include "Camera.h"

#include "Vector.h"
#include "SpriteSheet.h"

void Camera::update(int _width, int _height, Vector_2d player)
{
	width = _width;
	height = _height;
	pos.x = static_cast<int>(player.x) - width / 2 + SpriteSheet::texture_size / 2;
	pos.y = static_cast<int>(player.y) - height / 2 + SpriteSheet::texture_size / 2;
}