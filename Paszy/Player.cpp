#include "Player.h"

#include "Vector.h"
#include "Point.h"
#include "AudioSystem.h"

#include <iostream>
using namespace std;

Player::Player() {
	textureCode = PLAYER;
	hitboxWidth = 7.0;
	hitboxOffsetX = 1.0;
}

void Player::updateVelocity()
{
	if (vel.y > 0) {
		vel.y += GRAV_DOWN;
		alreadyPlayed = false;
	}
	else {
		vel.y += GRAV_UP;
	}

	//cout << "jumps: " << jumps << '\n';
	//cout << "vel: " << vel.x << ' ' << vel.y << '\n';

	if (actions[JUMP] and jumps < MAX_JUMPS)
	{
		AudioSystem::playSound(SoundId::JUMP);
		vel.y -= JUMP_VEL;
		++jumps;
	}

	if (vel.x >= MINIMAL_VEL)
	{
		vel.x -= DRAG;
	}
	else if (-vel.x >= MINIMAL_VEL)
	{
		vel.x += DRAG;
	}
	if (vel.x < MINIMAL_VEL and -vel.x < MINIMAL_VEL)
	{
		vel.x = 0;
	}

	if (actions[LEFT])
		if (-vel.x < LEFTRIGHT_VEL)
			vel.x = -LEFTRIGHT_VEL;
	if (actions[RIGHT])
		if (vel.x < LEFTRIGHT_VEL)
			vel.x = LEFTRIGHT_VEL;
}
void Player::handleCollision(CollisionDirection dir)
{
	if (dir.down) {
		jumps = 0;
		if (!alreadyPlayed) {
			alreadyPlayed = true;
			AudioSystem::playSound(SoundId::LANDING);
		}
	}
}

void Player::reset_actions()
{
	for (int i{ 0 }; i < MAX_ACTIONS; ++i)
	{
		actions[i] = false;
	}
}

void Player::update_actions(Keyboard keyboard)
{
	reset_actions();

	if (keyboard(W).down)
		actions[JUMP] = true;
	else
		actions[JUMP] = false;

	if (keyboard(D).held)
		actions[RIGHT] = true;

	if (keyboard(A).held)
		actions[LEFT] = true;
}
void Player::onEdge() {}