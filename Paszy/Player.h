#pragma once

#include "Keyboard.h"
#include "Entity.h"

enum Action
{
	RIGHT,
	LEFT,
	JUMP,
	MAX_ACTIONS
};


class Player : public Entity
{
private:
	const double JUMP_VEL = 1 - 1.0/8;
	const int MAX_JUMPS = 1;
	int jumps = 1;
	const double LEFTRIGHT_VEL = 1 - 1.0/4;
	const double GRAV_UP = 34 / 1024.0;
	const double GRAV_DOWN = 1.625 * GRAV_UP;
	const double DRAG = 1.0 / 2.0;
	const double MINIMAL_VEL = DRAG;
	bool alreadyPlayed = false;
	void reset_actions();
public:
	Player();
	bool actions[MAX_ACTIONS] = {};
	void update_actions(Keyboard keyboard);
	void updateVelocity();
	void handleCollision(CollisionDirection side) override;
	void onEdge() override;
};
