#include "WormBlock.h"
#include "EnemyWorm.h"
#include "Player.h"
#include "AudioSystem.h"

void WormBlock::update() {
	if (enemySpawned) return; // Prevent multiple spawns
	if (playerUnderneath()) {
		spawnWorm();
	}
}

void WormBlock::spawnWorm() {
	EnemyWorm* worm = new EnemyWorm();
	worm->pos = pos;
	enemiesRef->push_back(worm);
	enemySpawned = true;
}

bool WormBlock::playerUnderneath() {
	Vector_2d playerFootR = playerRef->getRightFoot();
	Vector_2d playerFootL = playerRef->getLeftFoot();

	if (getMapPos(playerFootR).x == getMapPos().x || getMapPos(playerFootL).x == getMapPos().x)
	{
		double playerY = playerRef->pos.y;
		double selfBottomY = getLeftFoot().y + 1;
		if (playerY < selfBottomY) return false;
		if (playerY - selfBottomY < vertivalDetectionRange) {
			return true;
		}
	}
	return false; 
}

bool WormBlock::isPlayerCovered()
{
	// tu dokoñczyæ
	return false;
}
void WormBlock::onEdge() {}