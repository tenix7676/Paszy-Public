#pragma once
#include "EnemySpawner.h"

class Bush : public EnemySpawner
{
	Vector_2d playerDistance;
	double activationRangeX = 3.0 * SpriteSheet::texture_size; // Range at which the bush activates (horizontal distance)
	int checkedIfPlayerCoveredCoordY;
public:
	void updatePlayerDistance();
	void update() override;
	void spawnApple();
	void onEdge() override;
	bool isPlayerCovered() override;
};

