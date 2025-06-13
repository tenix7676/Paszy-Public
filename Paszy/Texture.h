#pragma once

#include "SDL3/SDL.h"

#include <string>

#include "SpriteSheet.h"

class Texture
{
private:
	SDL_Texture* m_texture = nullptr;
	int m_width, m_height;
public:
	void free();
	bool load(SDL_Renderer* renderer, std::string texture_path = "sprite_sheet.png");
	void getXYClip(TextureCode texture_code, int& x, int& y);
	SDL_FRect getTextureClip(TextureCode texture_code);
	void render(SDL_Renderer* renderer, int x, int y, TextureCode texture_code);

	~Texture();
};