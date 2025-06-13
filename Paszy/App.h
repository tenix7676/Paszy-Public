#pragma once
#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"

#include <string>
#include <vector>

#include "Keyboard.h"
#include "Mouse.h"
#include "Map.h"
#include "Texture.h"
#include "Camera.h"
#include "Player.h"
#include "Enemy.h"
#include "SpriteSheet.h"
#include "State.h"

enum MenuButtons
{
	PLAY,
	QUIT,
	MAX_MENU_BUTTONS
};

class EnemySpawner;
class App
{
private:
	std::string m_window_title = "Paszy";
	int m_window_width = 600 * 2;
	int m_window_height = 480 * 2;
	float rendering_scale = 16.0f;
	const float ZOOMING_SPEED = 1.0f;
	const float MINIMAL_RENDERING_SCALE = 1.0f; // 0 for no min
	const float MAXIMAL_RENDERING_SCALE = 0.0f; // 0 for no max 
	int current_level = 0;
	const int MAX_LEVELS = 1;
	int deaths = 0;
	int total_deaths = 0;
	int kills = 0;
	int total_kills = 0;

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	TTF_Font* font;

	Keyboard m_keyboard;
	Mouse m_mouse;
	Map m_map;
	Camera m_camera;

	std::vector<Enemy*> enemies;
	std::vector<EnemySpawner*> enemySpawners; 

	Player m_player;
	Texture m_sprite_sheet;
	State current_state = MENU;
	SDL_FRect menu_buttons[MAX_MENU_BUTTONS];

	bool isPointInRect(SDL_FRect rect, float x, float y);
public:
	App();
	~App();

	bool init();
	void free();
	void run();
	bool handleEvents();
	void close();

	bool loadFont();
	bool loadCurrentLevel();
	//void addEntity(Entity* entity);
	//void removeEntity(Entity* entity);

	void render(int x, int y, TextureCode texture_code);
	void renderText(std::string text, int x, int y);
	void renderTextCentered(std::string text_, int x, int y);
	void renderTextCenteredX(std::string text_, int x, int y);
	void renderTextCenteredY(std::string text_, int x, int y);
	void renderPlayer();
	//void renderEntities();
	void renderMap();
	void renderGameOver();
	void renderLevelWin();
	void renderWin();
	void initMenu();
	void renderMenu();
	void updateMenuPos();
	void renderAll();
	void updateEntities();
	void loadEntities();
	void setStateGameOver();
	void setStateLevelWin();
	void resetLevelKillsDeaths();
	void deleteEntities();
	void renderEnemies();
	Map& getMap();

	void killEnemy(Enemy* en);
};