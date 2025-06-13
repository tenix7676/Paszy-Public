#include "Entity.h"
#include "Map.h"

Map* Entity::mapRef = nullptr;

void Entity::setMapRef(Map* map)
{
	mapRef = map;
}
Point Entity::getMapPos() 
{
	Point mapPos(pos / static_cast<double>(SpriteSheet::texture_size));
	return mapPos;
}

Point Entity::getMapPos(Vector_2d somePos) 
{
	Point mapPos(somePos / static_cast<double>(SpriteSheet::texture_size));
	return mapPos;
}

Vector_2d Entity::getRightFoot()
{
	Vector_2d footPos;
	footPos.x = pos.x + SpriteSheet::texture_size - 1.0;
	footPos.y = pos.y + SpriteSheet::texture_size - 1.0;
	return footPos;
}
Vector_2d Entity::getLeftFoot()
{
	Vector_2d footPos;
	footPos.x = pos.x;
	footPos.y = pos.y + SpriteSheet::texture_size - 1.0;
	return footPos;
}

void Entity::setPositionFromMap(int tile_x, int tile_y)
{
	pos.x = tile_x * SpriteSheet::texture_size;
	pos.y = tile_y * SpriteSheet::texture_size;
}
void Entity::updatePosition()
{
	pos.y += vel.y;
	pos.x += vel.x;
}
void Entity::handleCollision(CollisionDirection side) {}
/*
void Entity::render(App* app)
{
	app->render(pos.x, pos.y, texture_code);
}
*/

/*
Entity::Entity(App* app) : app(app) {
	map = &app->getMap();
	app->addEntity(this);
}
Entity::~Entity() {
	app->removeEntity(this);
}
*/