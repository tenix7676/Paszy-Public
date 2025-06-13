#include "Enemy.h"
#include "Player.h"

Player* Enemy::playerRef = nullptr;

Enemy::Enemy() 
{
	vel.x = direction * speed;
	vel.y = 0;
 }

void Enemy::handleCollision(CollisionDirection dir)
{
	if (dir.left or dir.right) {
		changeDirection();
	}
}

void Enemy::updateVelocity()
{
	handleGravity();
	if (isOnEdge) {
		changeDirection();
		isOnEdge = false;
	}

	vel.x = direction * speed;
}
void Enemy::handleGravity() {
	if (vel.y > 0)
		vel.y += GRAV_DOWN;
	else
		vel.y += GRAV_UP;
}

void Enemy::update()
{
	updateVelocity();
}

void Enemy::setPlayerRef(Player* player) 
{
	playerRef = player;
}

void Enemy::updatePlayerDistance() 
{

	playerDistance.x = abs(playerRef->pos.x - pos.x);
	playerDistance.y = abs(playerRef->pos.y - pos.y);
}

void Enemy::changeDirection()
{
	direction = -direction;
}

void Enemy::onEdge()
{
	isOnEdge = true;
}