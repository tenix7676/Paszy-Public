#pragma once
#include "EnemySpawner.h"

class WormBlock : public EnemySpawner
{
	const double vertivalDetectionRange = 3.0 * SpriteSheet::texture_size;
public:
	void spawnWorm();
	void update() override;
	bool playerUnderneath();
	bool isPlayerCovered() override;
	void onEdge() override;
};

