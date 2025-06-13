#pragma once
#include "Entity.h"

class Player;
class Enemy : public Entity
{
	const double GRAV_UP = 15 / 1024.0;
	const double GRAV_DOWN = 0.7 * GRAV_UP;
protected:
	int direction = 1; // 1: right, -1: left
	double speed = 0.5;
	Vector_2d playerDistance;
	static Player* playerRef;
	bool isOnEdge;
public:
	Enemy();
	void handleCollision(CollisionDirection side) override;
	void updateVelocity();
	void handleGravity();
	static void setPlayerRef(Player* player);
	void updatePlayerDistance();
	virtual void update();
	void changeDirection();
	void onEdge() override;
};