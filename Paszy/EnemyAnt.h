#pragma once
#include "Enemy.h"

class EnemyAnt : public Enemy
{
	bool pursuit = false; // If true, the ant is pursuing the player
	double enrageDistanceX = 5.0 * SpriteSheet::texture_size; // Distance at which the ant will start pursuing the player
	double enrageDistanceY = 1.0 * SpriteSheet::texture_size;
	const double JUMP_VEL = .48;

	const int JUMP_COOLDOWN = 150; // Cooldown for jumping in frames
	int franesSinceLastJump = 0; // Frames since the last jump

	Vector_2d playerPos; // Position of the pla

public:
	EnemyAnt();
	Vector_2d getPlayerPos();

	bool isPlayerInRange();

	void update() override;
	void pursuitPlayer();
	void handleCollision(CollisionDirection side) override;
	void tryToJump();
};