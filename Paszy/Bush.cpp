#include "Bush.h"
#include "Player.h"
#include "AppleEnemy.h"
#include "Map.h"
#include <iostream>

void Bush::updatePlayerDistance()
{
	playerDistance.x = abs(playerRef->pos.x - pos.x);
	playerDistance.y = abs(playerRef->pos.y - pos.y);
}

void Bush::update() {
	if (enemySpawned) return; // Prevent multiple spawns
	updatePlayerDistance();

	if (playerDistance.x < activationRangeX) {
		int playerMapY = getMapPos(playerRef->getLeftFoot()).y;
		int selfMapY = getMapPos().y;
		for (int i = -1; i <= 0; i++) {
			checkedIfPlayerCoveredCoordY = selfMapY + i;
			if (playerMapY == selfMapY + i) {
				if (!isPlayerCovered()) {
					spawnApple();
					//std::cout << "playerDistance.x to apple:" << playerDistance.x << std::endl;
				}
			}
		}
	}
}

void Bush::spawnApple() {
	AppleEnemy* apple = new AppleEnemy();
	apple->pos = pos;
	enemiesRef->push_back(apple);
	enemySpawned = true;
}

bool Bush::isPlayerCovered()
{
	if (playerDistance.x <= static_cast<double>(SpriteSheet::texture_size)) return false;
	
	int playerMapPosX = playerRef->getMapPos().x;
	int selfMapPosX = getMapPos().x;

	if (playerMapPosX < selfMapPosX) {
		for (int i = playerMapPosX + 1; i <= selfMapPosX - 1; i++) {
			if (mapRef->isSolidAtMAPCOORDS(i, checkedIfPlayerCoveredCoordY)) return true;
		}
	}
	else if (playerMapPosX > selfMapPosX) {
		for (int i = selfMapPosX + 1; i <= playerMapPosX - 1; i++) {
			if (mapRef->isSolidAtMAPCOORDS(i, checkedIfPlayerCoveredCoordY)) return true;
		}
	}
	return false;
}

void Bush::onEdge() {}