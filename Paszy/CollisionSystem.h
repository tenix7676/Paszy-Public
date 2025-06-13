#pragma once
#include "CollisionDirection.h"

class Entity;
class Enemy;
class Map;
class Player;
enum State;

class CollisionSystem
{
public:
	static CollisionDirection handleHorizontalCollision(Entity& entity, Map& map);
	static CollisionDirection handleVerticalCollision(Entity& entity, Map& map);
	static CollisionDirection handleCollision(Entity& entity, Map& map);
	static bool isOnEdge(Entity& e, Map& map);
	static void checkWin(Player& player, Map& map, State& state);
	static CollisionDirection playerEntitycollision(Player& player, Entity& entity);
	static CollisionDirection handleHorizontalCollision(Player& player, Map& map, char& collided_tile);
	static CollisionDirection handleVerticalCollision(Player& player, Map& map, char& collided_tile);
	static CollisionDirection handleCollision(Player& player, Map& map, char& collided_tile_hor, char& collied_tile_ver);
};