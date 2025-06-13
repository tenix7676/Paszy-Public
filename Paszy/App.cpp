#include "App.h"

#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"

#include <string>
#include <iostream>

using namespace std;

#include "FPS.h"
#include "Map.h"
#include "Texture.h"
#include "Player.h"
#include "SpriteSheet.h"
#include "State.h"
#include "CollisionSystem.h"
#include "AudioSystem.h"
#include "AppleEnemy.h"
#include "Bush.h"
#include "WormBlock.h"
#include "EnemyAnt.h"

SDL_Window* window;

void SDLCALL logMessage(void* userdata, int category, SDL_LogPriority priority, const char* message)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error :(", message, window);
}

bool App::init()
{
	if(!SDL_CreateWindowAndRenderer(m_window_title.c_str(), m_window_width, m_window_height, SDL_WINDOW_RESIZABLE, &m_window, &m_renderer))
	{
		SDL_Log("Couldn't create a window and renderer, error: %s.\n", SDL_GetError());
		return false;
	}

	window = m_window;

	SDL_SetLogOutputFunction(logMessage, NULL);

	if(!TTF_Init())
	{
		SDL_Log("Couldn't create a window and renderer, error: %s.\n", SDL_GetError());
		return false;
	}

	if(!loadFont())
	{
		SDL_Log("Couldn't load font.\n");
		return false;
	}

	if(!loadCurrentLevel())
	{
		SDL_Log("Couldn't load map.\n");
		return false;
	}

	if(!m_sprite_sheet.load(m_renderer))
	{
		SDL_Log("Couldn't load textures, sprite_sheet.png.\n");
		return false;
	}

	if(!AudioSystem::init())
	{
		SDL_Log("Couldn't initialize AudioSystem.\n");
		return false;
	}
	if(!AudioSystem::loadAll())
	{
		SDL_Log("Couldn't load audio files.\n");
		return false;
	}

	AudioSystem::setSoundVolume(20); // 20% volume

	SDL_SetRenderDrawColor(m_renderer, 153, 217, 234, 255);
	SDL_SetRenderScale(m_renderer, rendering_scale, rendering_scale);


	Entity::setMapRef(&m_map);
	Enemy::setPlayerRef(&m_player);
	EnemySpawner::setPlayerAndEnemiesRef(&m_player, &enemies);
	loadEntities();
	
	initMenu();

	return true;
}

bool App::loadFont()
{
	font = TTF_OpenFont("5highfont.ttf", 16);
	if(font == NULL)
	{
		SDL_Log("Couldn't load \"%s\".\n", "5highfont.ttf");
		return false;
	}
	else
		return true;
}

bool App::loadCurrentLevel()
{
	bool succ = m_map.load("levels/level" + to_string(current_level) + ".txt");
	
	if(!succ)
	{
		SDL_Log("Couldn't load \"%s\".\n", (string("level") + to_string(current_level) + string(".txt")).c_str());
	}

	m_map.getPlayerPos(m_player.pos);
	return succ;
}


void App::run()
{
	Uint64 start = SDL_GetPerformanceCounter();
	if(current_state==GAME)
	{

	m_player.update_actions(m_keyboard);
	m_player.updateVelocity();
	char collided_tile_hor, collided_tile_ver;
	m_player.handleCollision(CollisionSystem::handleCollision(m_player, m_map, collided_tile_hor, collided_tile_ver));
	if(collided_tile_hor == '^' or collided_tile_ver == '^')
		setStateGameOver();
	else if(collided_tile_hor == '*' or collided_tile_ver == '*')
		setStateLevelWin();

	//CollisionSystem::checkWin(m_player, m_map, current_state);
	updateEntities();
	m_player.updatePosition();

	m_camera.update(m_window_width / rendering_scale, m_window_height / rendering_scale, m_player.pos);
	
	//cout << "SCALE: " << rendering_scale << '\n';

	/*if(m_player.actions[JUMP])
		m_player.pos.x = 80;*/

	//cout << "Player: " << m_player.pos.x << ' ' << m_player.pos.y << '\n';
	//cout << "Camera: " << m_camera.pos.x << ' ' << m_camera.pos.y << '\n';
	//cout << "\n\n\nm_keyboard(A).down " << m_keyboard(A).down << '\n';
	//cout << "\nm_keyboard(A).held " << m_keyboard(A).held << '\n';
	//cout << "\nm_keyboard(A).up   " << m_keyboard(A).up << '\n';
	}

	renderAll();

	FPS::DelayTillFPS(start);
}

//void App::removeEntity(Entity* entity) {
//	entities.erase(
//		std::remove(entities.begin(), entities.end(), entity), entities.end()
//	);
//}
//void App::removeEntity(Entity* entity) {
//	entities.erase(
//		std::remove(entities.begin(), entities.end(), entity), entities.end()
//	);
//}

void App::render(int x, int y, TextureCode texture_code)
{
	m_sprite_sheet.render(m_renderer,
		x - m_camera.pos.x,
		y - m_camera.pos.y,
		texture_code);
}

void App::renderText(string text_, int x, int y)
{
	SDL_FRect dest;
	SDL_FRect source;
	source.x = 0;
	source.y = 0;
	dest.x = x;
	dest.y = y - 6;


	SDL_Surface* text = TTF_RenderText_Solid(font, text_.c_str(), 0, SDL_Color(255, 255, 255, 255));
	SDL_Texture* texture = nullptr;
	if(text) {
		texture = SDL_CreateTextureFromSurface(m_renderer, text);
		dest.w = text->w;
		dest.h = text->h;
		source.w = text->w;
		source.h = text->h;

		SDL_DestroySurface(text);
	}
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
	SDL_RenderTexture(m_renderer, texture, NULL, &dest);
}

void App::renderTextCentered(string text_, int x, int y)
{
	SDL_FRect dest;
	SDL_FRect source;
	source.x = 0;
	source.y = 0;


	SDL_Surface* text = TTF_RenderText_Solid(font, text_.c_str(), 0, SDL_Color(255, 255, 255, 255));
	SDL_Texture* texture = nullptr;
	if(text) {
		texture = SDL_CreateTextureFromSurface(m_renderer, text);
		dest.w = text->w;
		dest.h = text->h;
		source.w = text->w;
		source.h = text->h;

		SDL_DestroySurface(text);
	}

	dest.x = x - source.w / 2;
	dest.y = y - (source.h) / 2 - 2;
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
	SDL_RenderTexture(m_renderer, texture, NULL, &dest);
}

void App::renderTextCenteredX(string text_, int x, int y)
{
	SDL_FRect dest;
	SDL_FRect source;
	source.x = 0;
	source.y = 0;


	SDL_Surface* text = TTF_RenderText_Solid(font, text_.c_str(), 0, SDL_Color(255, 255, 255, 255));
	SDL_Texture* texture = nullptr;
	if(text) {
		texture = SDL_CreateTextureFromSurface(m_renderer, text);
		dest.w = text->w;
		dest.h = text->h;
		source.w = text->w;
		source.h = text->h;

		SDL_DestroySurface(text);
	}

	dest.x = x - source.w / 2;
	dest.y = y - 6;
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
	SDL_RenderTexture(m_renderer, texture, NULL, &dest);
}

void App::renderTextCenteredY(string text_, int x, int y)
{
	SDL_FRect dest;
	SDL_FRect source;
	source.x = 0;
	source.y = 0;


	SDL_Surface* text = TTF_RenderText_Solid(font, text_.c_str(), 0, SDL_Color(255, 255, 255, 255));
	SDL_Texture* texture = nullptr;
	if(text) {
		texture = SDL_CreateTextureFromSurface(m_renderer, text);
		dest.w = text->w;
		dest.h = text->h;
		source.w = text->w;
		source.h = text->h;

		SDL_DestroySurface(text);
	}

	dest.x = x;
	dest.y = y - source.h / 2 - 2;
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
	SDL_RenderTexture(m_renderer, texture, NULL, &dest);
}


void App::renderAll()
{
	SDL_RenderClear(m_renderer);
	if(current_state == GAME)
	{

		renderEnemies();
		renderPlayer();
		renderMap();
	}
	else if(current_state == MENU)
	{
		updateMenuPos();
		/*for(auto r : menu_buttons)
		{
			SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
			SDL_RenderRect(m_renderer, &r);
			SDL_SetRenderDrawColor(m_renderer, 255, 255, 0, 255);
		}*/
		renderMenu();
	}
	else if(current_state == GAME_OVER)
	{
		renderGameOver();
	}
	else if(current_state == LEVEL_WIN)
	{
		renderLevelWin();
	}
	else if(current_state == WIN)
	{
		renderWin();
	}
	SDL_RenderPresent(m_renderer);
}


void App::renderPlayer()
{
	render(m_player.pos.x, m_player.pos.y, PLAYER);
}

void App::renderEnemies()
{
	for (Enemy* e : enemies) {
		render(e->pos.x, e->pos.y, e->textureCode);
	}
}

void App::renderMap()
{
	for(int y{ 0 }; y < m_map.getHeight(); ++y)
	{
		for(int x{ 0 }; x < m_map.getWidth(); ++x)
		{
			render(x * SpriteSheet::texture_size,
				y * SpriteSheet::texture_size,
				m_map.getTextureAt(x, y));
		}
	}
}

void App::renderGameOver()
{
	if(deaths == 0) renderTextCentered("LEVEL OVER " + to_string(deaths + 1) + " death", m_window_width / rendering_scale / 2, m_window_height / rendering_scale / 2);
	else			renderTextCentered("LEVEL OVER " + to_string(deaths + 1) + " deaths", m_window_width / rendering_scale / 2, m_window_height / rendering_scale / 2);
}

void App::renderLevelWin()
{
	renderTextCentered("You won level " + to_string(current_level), m_window_width / rendering_scale / 2, m_window_height / rendering_scale / 2 - 7);
	if(kills == 1) renderTextCentered("With " + to_string(kills) + " kill", m_window_width / rendering_scale / 2, m_window_height / rendering_scale / 2 );
	else           renderTextCentered("With " + to_string(kills) + " kills", m_window_width / rendering_scale / 2, m_window_height / rendering_scale / 2 );
	if(deaths == 1)renderTextCentered("With " + to_string(deaths) + " death", m_window_width / rendering_scale / 2, m_window_height / rendering_scale / 2 + 7);
	else           renderTextCentered("With " + to_string(deaths) + " deaths", m_window_width / rendering_scale / 2, m_window_height / rendering_scale / 2 + 7);

}

void App::renderWin()
{
	renderTextCentered("You won Paszy!", m_window_width / rendering_scale / 2, m_window_height / rendering_scale / 2 - 7);
	if(total_kills == 1) renderTextCentered("With " + to_string(total_kills) + " kill total", m_window_width / rendering_scale / 2, m_window_height / rendering_scale / 2);
	else                 renderTextCentered("With " + to_string(total_kills) + " kills total", m_window_width / rendering_scale / 2, m_window_height / rendering_scale / 2);
	if(total_deaths == 1)renderTextCentered("With " + to_string(total_deaths) + " death total", m_window_width / rendering_scale / 2, m_window_height / rendering_scale / 2 + 7);
	else                 renderTextCentered("With " + to_string(total_deaths) + " deaths total", m_window_width / rendering_scale / 2, m_window_height / rendering_scale / 2 + 7);
}

void App::initMenu()
{
	menu_buttons[PLAY].w = 15;
	menu_buttons[PLAY].h = 5;

	menu_buttons[QUIT].w = 15;
	menu_buttons[QUIT].h = 5;
}

void App::renderMenu()
{
	renderText("PLAY", menu_buttons[PLAY].x, menu_buttons[PLAY].y);
	renderText("QUIT", menu_buttons[QUIT].x, menu_buttons[QUIT].y);
}
void App::updateMenuPos()
{
	const int FONT_HEIGHT_PXL = 5;
	int y0 = m_window_height / rendering_scale / 2 - FONT_HEIGHT_PXL * MAX_MENU_BUTTONS / 2;

	for(int i{ 0 }; i < MAX_MENU_BUTTONS; ++i)
	{
		menu_buttons[i].x = m_window_width / rendering_scale / 2 - menu_buttons[i].w / 2;
		menu_buttons[i].y = y0 + i * (FONT_HEIGHT_PXL + 1) - menu_buttons[i].h / 2;
	}
}


bool App::isPointInRect(SDL_FRect rect, float x, float y)
{
	return
		rect.x < x / rendering_scale and x / rendering_scale < rect.x + rect.w
		and
		rect.y < y / rendering_scale and y / rendering_scale < rect.y + rect.h;
}


bool App::handleEvents()
{
	SDL_Event event{};
	while(SDL_PollEvent(&event))
	{
		m_keyboard.reset();
		m_mouse.reset();

		m_keyboard.update(event);
		m_mouse.update(event);

		//cout << "mouse_xy: " << m_mouse.x << ", " << m_mouse.y << "mouse down: " << m_mouse(LMB).down << endl;
		//cout << m_mouse.scrolling << m_mouse.scrolling_up << m_mouse.scrolling_down << endl;

		if(event.type == SDL_EVENT_QUIT)
			return false;
		if(event.type == SDL_EVENT_WINDOW_RESIZED)
			SDL_GetWindowSize(m_window, &m_window_width, &m_window_height);
		if(m_mouse.scrolling) {
			if(m_mouse.scrolling_up) {
				rendering_scale += ZOOMING_SPEED;
				if(rendering_scale > MAXIMAL_RENDERING_SCALE and MAXIMAL_RENDERING_SCALE != 0)
					rendering_scale = MAXIMAL_RENDERING_SCALE;
			}
			if(m_mouse.scrolling_down) {
				rendering_scale -= ZOOMING_SPEED;
				if(rendering_scale < MINIMAL_RENDERING_SCALE and MINIMAL_RENDERING_SCALE != 0)
					rendering_scale = MINIMAL_RENDERING_SCALE;
			}
			SDL_SetRenderScale(m_renderer, rendering_scale, rendering_scale);
		}
		if(current_state == GAME)
		{
			return true;
		}
		else
		{
			if(current_state == MENU)
			{
				if(m_mouse(LMB).down and isPointInRect(menu_buttons[PLAY], m_mouse.x, m_mouse.y))
				{
					current_state = GAME;
				}
				else if(m_mouse(LMB).down and isPointInRect(menu_buttons[QUIT], m_mouse.x, m_mouse.y))
				{
					return false;
				}
			}
			else if(current_state == GAME_OVER)
			{
				if(m_mouse(LMB).down)
				{
					m_map.getPlayerPos(m_player.pos);
					deleteEntities(); loadEntities();
					++deaths;
					current_state = GAME;
				}
			}
			else if(current_state == LEVEL_WIN)
			{
				if(current_level != MAX_LEVELS)
				{
					//cout << "mouse_xy: " << m_mouse.x << ", " << m_mouse.y << "mouse down: " << m_mouse(LMB).down << endl;
					//cout << m_mouse(LMB).down << endl;
					if(m_mouse(LMB).down)
					{
						++current_level;
						loadCurrentLevel();
						resetLevelKillsDeaths();
						current_state = GAME;
					}
				}
				else
				{
					if(m_mouse(LMB).down)
						current_state = WIN;
				}
			}
		}
	}

	return true;
}


void App::updateEntities() {
	for (Enemy* e : enemies) {
		if (CollisionSystem::isOnEdge(*e, m_map)) e->onEdge();
		e->update();
		e->handleCollision(CollisionSystem::handleCollision(*e, m_map));
		
		auto dir = CollisionSystem::playerEntitycollision(m_player, *e);

		if (dir.down)
		{
			double playerBottom = m_player.pos.y + m_player.hitboxOffsetY + m_player.hitboxHeight - 1.0;
			double enemyBottom = e->pos.y + e->hitboxOffsetY + e->hitboxHeight - 1.0;
			double lowerEnemyHeight = e->hitboxHeight * 7 / 8; // 20% of enemy height

			if (playerBottom <= enemyBottom - lowerEnemyHeight) {
				// Player killed enemy
				killEnemy(e);
				AudioSystem::playSound(SoundId::KILL);
			}
			else {
				cout << "almost\n";
		}
		}
		else if(dir.right or dir.left or dir.up)
		{
			setStateGameOver();
		}
		e->updatePosition();
	}
	
	for (EnemySpawner* e : enemySpawners) {
		e->update();
	}
}

void App::loadEntities()
{
	for (int i = 0; i < m_map.getHeight(); i++) {
		for (int j = 0; j < m_map.getWidth(); j++) {
			char tile = m_map.getTile(j, i);
			if(tile=='A')
			{
				AppleEnemy* apple = new AppleEnemy;
				apple->setPositionFromMap(j, i);
				enemies.push_back(apple);
			}
			else if(tile=='a')
			{
				EnemyAnt* ant = new EnemyAnt;
				ant->setPositionFromMap(j, i);
				enemies.push_back(ant);
			}
			else if(tile=='6')
			{

			}
			else if (tile == '7')
			{

			}
			else if(tile == 'B')
			{
				Bush* bush = new Bush();
				bush->setPositionFromMap(j, i);
				enemySpawners.push_back(bush);
			}
			else if (tile == 'W')
			{
				WormBlock* block = new WormBlock;
				block->setPositionFromMap(j, i);
				enemySpawners.push_back(block);
			}
		}
	}
}

void App::setStateGameOver() {
	AudioSystem::playSound(SoundId::GAMEOVER);
	current_state = GAME_OVER;
	kills = 0;
}

void App::setStateLevelWin() {
	AudioSystem::playSound(SoundId::LEVEL_WIN);
	current_state = LEVEL_WIN;
	total_deaths += deaths;
	total_kills += kills;
}

void App::resetLevelKillsDeaths()
{
	deaths = 0;
	kills = 0;
}

void App::deleteEntities()
{
	for (Enemy* e : enemies) {
		delete e;
	}
	enemies.clear();
	for (EnemySpawner* e : enemySpawners) {
		delete e;
	}
	enemySpawners.clear();
}
void App::free()
{
	deleteEntities();
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
}

void App::close()
{
	free();
	SDL_Quit();
}
Map& App::getMap() {
	return m_map;
}

void App::killEnemy(Enemy* en) {
	auto it = std::find(enemies.begin(), enemies.end(), en);
	if (it != enemies.end()) {
		enemies.erase(it);
		delete en;
	}
	++kills;
}

App::App()
{
	init();
}

App::~App()
{
	close();
}