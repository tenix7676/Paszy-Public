#include "EnemySpawner.h"
#include "Player.h"

Player* EnemySpawner::playerRef = nullptr;
std::vector<Enemy*>* EnemySpawner::enemiesRef = nullptr;

void EnemySpawner::setPlayerAndEnemiesRef(Player* player, std::vector<Enemy*>* enemies)
{
	playerRef = player;
	enemiesRef = enemies;
}
void EnemySpawner::update() {}