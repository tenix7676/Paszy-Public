#include "EnemyAnt.h"
#include "Player.h"

EnemyAnt::EnemyAnt() {
	textureCode = ANT;
	hitboxHeight = 5.0;
	hitboxOffsetY = 3.0;
	speed = 0.4;
}

Vector_2d EnemyAnt::getPlayerPos() {
	return playerRef->pos;
}

#include <iostream>
bool EnemyAnt::isPlayerInRange() { 
	if(playerDistance.x <= enrageDistanceX && playerDistance.y <= enrageDistanceY) {
		//std::cout << "Player is in range of the ant. RANGE: (" << playerDistance.x << ", " << playerDistance.y << ')' << std::endl;
		return true;
	}
	return false;
}

void EnemyAnt::update() {
	franesSinceLastJump++;
	updatePlayerDistance();
	
	if (isPlayerInRange()) {
		pursuit = true;
	}
	else {
		pursuit = false;
	}

	if (pursuit) {
		pursuitPlayer();
	} else {
		updateVelocity();
	}
}

void EnemyAnt::pursuitPlayer() {
	Vector_2d playerPos = getPlayerPos();
	if (playerPos.x > pos.x) {
		direction = 1;
	}
	else {
		direction = -1;
	}
	handleGravity();

	vel.x = direction * speed;
}

void EnemyAnt::handleCollision(CollisionDirection side) {
	if(side.left || side.right) {
		if (pursuit) {
			if(playerPos.y <= pos.y) {
				// Player is below the ant, jump
				tryToJump();
			}
		}
		else {
			changeDirection();
		}
	}
}

void EnemyAnt::tryToJump() {
	if (franesSinceLastJump > JUMP_COOLDOWN) {
		vel.y -= JUMP_VEL;
		franesSinceLastJump = 0;
	}
}