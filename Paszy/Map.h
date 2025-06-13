#pragma once
#include <string>

#include "SpriteSheet.h"
// ` - air
// P - player
// # - platform
// ^ - spikes
// A - enemy apple
// a - enemy ant
// B - bush
// W - worm block
// * - win block
// d - dirt
// B - bush with apple
// b - bush

#include "Vector.h"
#include "Point.h"

class Map
{
private:
	char** m_map = nullptr;
	int m_width = 0;
	int m_height = 0;
public:
	void free();
	bool load(std::string map_path = "level1.txt");
	void save(std::string map_path);
	void create_empty(int width, int height);

	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
	TextureCode getTextureAt(int tile_x, int tile_y);
	char getTile(int tile_x, int tile_y);
	char getTile(Point tile);
	bool isSolidAt(double world_x, double world_y);
	bool isSolidAtMAPCOORDS(int x, int y);
	bool isSolidAtMAPCOORDS(Point pos);

	bool isSolidAtMAPCOORDSForPlayer(int x, int y);

	bool isSolidAtMAPCOORDSForPlayer(Point pos);

	void getPlayerPos(Vector_2d& player_pos_out);

	Map();
	Map(std::string map_path);
	~Map();
};