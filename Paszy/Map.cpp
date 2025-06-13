#include "Map.h"

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

#include "SpriteSheet.h"

void Map::free()
{
	for(int y{ 0 }; y < m_height; ++y)
	{
		delete[] m_map[y];
	}

	delete[] m_map;

	m_map = nullptr;
}
bool Map::load(std::string map_path)
{
	ifstream file(map_path);

	if(!file.is_open())
		return false;

	free();

	file >> m_width >> m_height;

	m_map = new char* [m_height];

	for(int y{ 0 }; y < m_height; ++y)
	{
		m_map[y] = new char[m_width];
		for(int x{ 0 }; x < m_width; ++x)
			file >> m_map[y][x];
	}

	return true;
}
void Map::save(std::string map_path)
{
	ofstream file(map_path);

	file << m_width << '\n'
		<< m_height << '\n';

	for(int y{ 0 }; y < m_height; ++y)
	{
		for(int x{ 0 }; x < m_width; ++x)
			file << m_map[y][x];
		file << '\n';
	}
}
void Map::create_empty(int width, int height)
{
	free();

	m_width = width;
	m_height = height;

	m_map = new char* [m_height];

	for(int y{ 0 }; y < m_height; ++y)
	{
		m_map[y] = new char[m_width];
		for(int x{ 0 }; x < m_width; ++x)
			m_map[y][x] = '`';
	}
}

TextureCode charToTextureCode(char character)
{
	switch(character)
	{
	case '`':
		return AIR;
	case 'P':
		return AIR; //make the PLAYER spawn an AIR tile;
	case '#':
		return PLATFORM;
	case '^':
		return SPIKE;
	case 'A':
		return AIR; //make the ENEMY spawn an AIR tile;
	case 'B':
		return BUSH;
	case 'W':
		return WORM_BLOCK;
	case '*':
		return WIN_BLOCK;
	case 'a':
		return AIR;
	case 'd':
		return WORM_BLOCK;
	case 'b':
		return BUSH;
	default:
		cerr << "charToTextureCode() failed: no appropriate code for this char (" << character << ")\n";
		return AIR;
	}
}

TextureCode Map::getTextureAt(int tile_x, int tile_y)
{
	return charToTextureCode(m_map[tile_y][tile_x]);
}
char Map::getTile(int tile_x, int tile_y)
{
	if(tile_x < 0 || tile_x >= m_width || tile_y < 0 || tile_y >= m_height)
		return '`'; // Outside the map everything is air
	return m_map[tile_y][tile_x];
}
char Map::getTile(Point tile)
{
	return getTile(tile.x, tile.y);
}

bool Map::isSolidAt(double world_x, double world_y) {
	int tile_x = static_cast<int>(world_x) / SpriteSheet::texture_size;
	int tile_y = static_cast<int>(world_y) / SpriteSheet::texture_size;

	if (tile_x < 0 || tile_x >= m_width || tile_y < 0 || tile_y >= m_height) 
		return true; // Outside the map everything is solid


	return isSolidAtMAPCOORDS(tile_x,tile_y); // True if texture is one of the solid objects
}

bool Map::isSolidAtMAPCOORDS(int x, int y)
{
	if(x < 0 || x >= m_width || y < 0 || y >= m_height)
		return true; // Outside the map everything is solid

	return m_map[y][x] == '#' or m_map[y][x] == 'd';

}

bool Map::isSolidAtMAPCOORDS(Point pos)
{
	return isSolidAtMAPCOORDS(pos.x, pos.y);
}

bool Map::isSolidAtMAPCOORDSForPlayer(int x, int y)
{
	if(x < 0 || x >= m_width || y < 0 || y >= m_height)
		return true; // Outside the map everything is solid

	return m_map[y][x] == '#' or m_map[y][x] == 'W' or m_map[y][x] == 'd';
}

bool Map::isSolidAtMAPCOORDSForPlayer(Point pos)
{
	return isSolidAtMAPCOORDSForPlayer(pos.x, pos.y);
}

void Map::getPlayerPos(Vector_2d& player_pos)
{
	for (int y{ 0 }; y < m_height; ++y)
		for (int x{ 0 }; x < m_width; ++x)
			if (m_map[y][x] == 'P')
			{
				player_pos.x = SpriteSheet::texture_size * x;
				player_pos.y = SpriteSheet::texture_size * y;
				return;
			}
}

Map::Map()
{
	;
}
Map::Map(std::string map_path)
{
	load(map_path);
}


Map::~Map()
{
	free();
}