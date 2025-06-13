#pragma once
#include "Entity.h"
#include <vector>

class Player;
class Enemy;
class EnemySpawner : public Entity
{
protected:
	static Player* playerRef;
	static std::vector<Enemy*>* enemiesRef;

	bool enemySpawned = false;
public:
	static void setPlayerAndEnemiesRef(Player* player, std::vector<Enemy*>* enemies);
	virtual void update();
	virtual bool isPlayerCovered() = 0;
};