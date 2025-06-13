#include "CollisionSystem.h"

#include "CollisionDirection.h"
#include "Enemy.h"
#include "Map.h"
#include "Player.h"
#include "State.h"


bool tilesCollide(Vector_2d box1, Vector_2d box2)
{
	int size = SpriteSheet::texture_size;
	// are the sides of one rectangle touching the other?
	return (box1.x + size > box2.x &&    // r1 right edge past r2 left
		box1.x < box2.x + size &&        // r1 left edge past r2 right
		box1.y + size > box2.y &&        // r1 top edge past r2 bottom
		box1.y < box2.y + size);         // r1 bottom edge past r2 top
}

bool tilesCollide(Vector_2d box1, Vector_2d box2,
	double hitboxWidth1, double hitboxHeight1, double offsetX1, double offsetY1,
	double hitboxWidth2, double hitboxHeight2, double offsetX2, double offsetY2
) {
	// are the sides of one rectangle touching the other?
	return 
		box1.x + offsetX1 + hitboxWidth1 > box2.x + offsetX2 &&		// r1 right edge past r2 left
		box1.x + offsetX1 < box2.x + offsetX2 + hitboxWidth2 &&     // r1 left edge past r2 right
		box1.y + offsetY1 + hitboxHeight1 > box2.y + offsetY2 &&	// r1 top edge past r2 bottom
		box1.y + offsetY1 < box2.y + offsetY2 + hitboxHeight2;		// r1 bottom edge past r2 top
}

CollisionDirection CollisionSystem::handleHorizontalCollision(Entity& entity, Map& map) {
	CollisionDirection dir;
	int tile_size = SpriteSheet::texture_size;

	//Check 3 boxes to the right of the player for collisions
	if (entity.vel.x > 0)
	{
		for (int y{ -1 }; y <= 1; ++y)
		{
			Point box_pos{ entity.getMapPos() };
			box_pos.x += 1;
			box_pos.y += y;
			if (map.isSolidAtMAPCOORDS(box_pos))
			{
				box_pos *= tile_size;

				Vector_2d next_pos = entity.pos;
				next_pos.x += entity.vel.x;

				if (tilesCollide(box_pos, next_pos))
				{
					entity.pos.x = box_pos.x - tile_size;
					//entity.pos.x -= entity.vel.x;
					entity.vel.x = 0;
					dir.right = true;
				}
			}
		}
	}
	//Check 3 boxes to the left of the player for collisions
	if (entity.vel.x < 0)
	{
		for (int y{ -1 }; y <= 1; ++y)
		{
			Point box_pos{ entity.getMapPos() };
			box_pos.x -= 1;
			box_pos.y += y;
			if (map.isSolidAtMAPCOORDS(box_pos))
			{
				box_pos *= tile_size;

				Vector_2d next_pos = entity.pos;
				next_pos.x += entity.vel.x;

				if (tilesCollide(box_pos, next_pos))
				{
					entity.pos.x = box_pos.x + tile_size;
					//entity.pos.x -= entity.vel.x;
					entity.vel.x = 0;
					dir.left = true;
				}
			}
		}
	}
	return dir;
}

CollisionDirection CollisionSystem::handleVerticalCollision(Entity& entity, Map& map) {
	CollisionDirection dir;

	int tile_size = SpriteSheet::texture_size;
	//Check 3 boxes under player for collisions
	if (entity.vel.y > 0)
	{
		for (int x{ -1 }; x <= 1; ++x)
		{
			Point box_pos{ entity.getMapPos() };
			box_pos.x += x;
			box_pos.y += 1;

			if (map.isSolidAtMAPCOORDS(box_pos))
			{
				box_pos *= tile_size;

				Vector_2d next_pos = entity.pos;
				next_pos.y += entity.vel.y;

				if (tilesCollide(box_pos, next_pos))
				{
					entity.pos.y = box_pos.y - tile_size;
					//entity.pos.y -= entity.vel.y;
					entity.vel.y = 0;
					dir.down = true;
				}
			}
		}
	}
	//Check 3 boxes over player for collisions
	if (entity.vel.y < 0)
	{
		for (int x{ -1 }; x <= 1; ++x)
		{
			Point box_pos{ entity.getMapPos() };
			box_pos.x += x;
			box_pos.y -= 1;

			if (map.isSolidAtMAPCOORDS(box_pos))
			{
				box_pos *= tile_size;

				Vector_2d next_pos = entity.pos;
				next_pos.y += entity.vel.y;

				if (tilesCollide(box_pos, next_pos))
				{
					entity.pos.y = box_pos.y + tile_size;
					//entity.pos.y -= entity.vel.y;
					entity.vel.y = 0;
					dir.up = true;
				}
			}
		}
	}
	return dir;
}

CollisionDirection CollisionSystem::handleCollision(Entity& entity, Map& map)
{
	CollisionDirection verticalDir = handleVerticalCollision(entity, map);
	CollisionDirection horizontalDir = handleHorizontalCollision(entity, map);
	
	return CollisionDirection{ verticalDir.up, verticalDir.down, horizontalDir.left, horizontalDir.right };
}

bool CollisionSystem::isOnEdge(Entity& e, Map& map) 
{
	Vector_2d nextPos = e.pos + e.vel;
	double nextRightStep = e.pos.x + SpriteSheet::texture_size - 1;
	double nextLeftStep = e.pos.x;

	if (e.vel.x > 0) {
		return !map.isSolidAt(nextRightStep, e.pos.y + SpriteSheet::texture_size);
	}
	else if (e.vel.x < 0) {
		return !map.isSolidAt(nextLeftStep, e.pos.y + SpriteSheet::texture_size);
	}
	else {
		return false;
	}
}

void CollisionSystem::checkWin(Player& player, Map& map, State& state)
{
	Point mapPos = player.getMapPos();
	char tile = map.getTile(mapPos.x, mapPos.y);
	if (tile == '*') state = State::LEVEL_WIN;
}

CollisionDirection CollisionSystem::playerEntitycollision(Player& player, Entity& entity)
{
	CollisionDirection dir;
	//int tile_size = SpriteSheet::texture_size;

	Vector_2d next_pos_player = player.pos;
	Vector_2d next_pos_entity = entity.pos;

	next_pos_player.x += player.vel.x;
	next_pos_entity.x += entity.vel.x;

	double playerHitboxWidth = player.hitboxWidth;
	double playerHitboxHeight = player.hitboxHeight;
	double playerOffsetX = player.hitboxOffsetX;
	double playerOffsetY = player.hitboxOffsetY;
	double entityHitboxWidth = entity.hitboxWidth;
	double entityHitboxHeight = entity.hitboxHeight;
	double entityOffsetX = entity.hitboxOffsetX;
	double entityOffsetY = entity.hitboxOffsetY;

	if (tilesCollide(next_pos_player, next_pos_entity, 
		playerHitboxWidth, playerHitboxHeight, playerOffsetX, playerOffsetY,
		entityHitboxWidth, entityHitboxHeight, entityOffsetX, entityOffsetY
	)) {
		if (player.vel.x >= 0) dir.right = true;
		if (player.vel.x <= 0) dir.left = true;
	}

	next_pos_player = player.pos;
	next_pos_entity = entity.pos;

	next_pos_player.y += player.vel.y;
	next_pos_entity.y += entity.vel.y;
	if (tilesCollide(next_pos_player, next_pos_entity,
		playerHitboxWidth, playerHitboxHeight, playerOffsetX, playerOffsetY,
		entityHitboxWidth, entityHitboxHeight, entityOffsetX, entityOffsetY
	)) {
		if (player.vel.y >= 0) dir.down = true;
		if (player.vel.y <= 0) dir.up = true;
	}

	return dir;
}

CollisionDirection CollisionSystem::handleHorizontalCollision(Player& player, Map& map, char& collided_tile) {
	CollisionDirection dir;
	int tile_size = SpriteSheet::texture_size;

	collided_tile = '\0';

	//Check 3 boxes to the right of the player for collisions
	if (player.vel.x > 0)
	{
		for (int y{ -1 }; y <= 1; ++y)
		{
			Point box_pos{ player.getMapPos() };
			box_pos.x += 1;
			box_pos.y += y;

			box_pos *= tile_size;

			Vector_2d next_pos = player.pos;
			next_pos.x += player.vel.x;

			if(tilesCollide(box_pos, next_pos))
			{
				if(map.isSolidAtMAPCOORDSForPlayer(box_pos / tile_size))
				{
					player.pos.x = box_pos.x - tile_size;
					//player.pos.x -= player.vel.x;
					player.vel.x = 0;
					dir.right = true;
				}
				if(map.getTile(box_pos / tile_size) != '`')
				{
					collided_tile = map.getTile(box_pos / tile_size);
					//cout << "Tile: " << collided_tile << endl;
				}
			}
		}
	}
	//Check 3 boxes to the left of the player for collisions
	if (player.vel.x < 0)
	{
		for (int y{ -1 }; y <= 1; ++y)
		{
			Point box_pos{ player.getMapPos() };
			box_pos.x -= 1;
			box_pos.y += y;

			box_pos *= tile_size;

			Vector_2d next_pos = player.pos;
			next_pos.x += player.vel.x;

			if(tilesCollide(box_pos, next_pos))
			{
				if(map.isSolidAtMAPCOORDSForPlayer(box_pos / tile_size))
				{
					player.pos.x = box_pos.x + tile_size;
					//player.pos.x -= player.vel.x;
					player.vel.x = 0;
					dir.left = true;
				}
				if(map.getTile(box_pos / tile_size) != '`')
				{
					collided_tile = map.getTile(box_pos / tile_size);
					//cout << "Tile: " << collided_tile << endl;
				}
			}
		}
	}
	return dir;
}

CollisionDirection CollisionSystem::handleVerticalCollision(Player& player, Map& map, char& collided_tile) {
	CollisionDirection dir;

	collided_tile = '\0';

	int tile_size = SpriteSheet::texture_size;
	//Check 3 boxes under player for collisions
	if (player.vel.y > 0)
	{
		for (int x{ -1 }; x <= 1; ++x)
		{
			Point box_pos{ player.getMapPos() };
			box_pos.x += x;
			box_pos.y += 1;

			box_pos *= tile_size;

			Vector_2d next_pos = player.pos;
			next_pos.y += player.vel.y;

			if(tilesCollide(box_pos, next_pos))
			{
				if(map.isSolidAtMAPCOORDSForPlayer(box_pos / tile_size))
				{
					player.pos.y = box_pos.y - tile_size;
					player.vel.y = 0;
					dir.down = true;
				}
				if(map.getTile(box_pos / tile_size) != '`')
				{
					collided_tile = map.getTile(box_pos / tile_size);
					//cout << "Tile: " << collided_tile << endl;
				}
			}
		}
	}
	//Check 3 boxes over player for collisions
	if (player.vel.y < 0)
	{
		for (int x{ -1 }; x <= 1; ++x)
		{
			Point box_pos{ player.getMapPos() };
			box_pos.x += x;
			box_pos.y -= 1;

			box_pos *= tile_size;

			Vector_2d next_pos = player.pos;
			next_pos.y += player.vel.y;

			if(tilesCollide(box_pos, next_pos))
			{
				if(map.isSolidAtMAPCOORDSForPlayer(box_pos / tile_size))
				{
					player.pos.y = box_pos.y + tile_size;
					//player.pos.y -= player.vel.y;
					player.vel.y = 0;
					dir.up = true;
				}
				if(map.getTile(box_pos / tile_size) != '`')
				{
					collided_tile = map.getTile(box_pos / tile_size);
					//cout << "Tile: " << collided_tile << endl;
				}
			}
		}
	}
	return dir;
}

CollisionDirection CollisionSystem::handleCollision(Player& player, Map& map, char& collided_tile_hor, char& collied_tile_ver)
{
	CollisionDirection verticalDir = handleVerticalCollision(player, map, collied_tile_ver);
	CollisionDirection horizontalDir = handleHorizontalCollision(player, map, collided_tile_hor);

	return CollisionDirection{ verticalDir.up, verticalDir.down, horizontalDir.left, horizontalDir.right };
}