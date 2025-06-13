#include "Texture.h"

#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"

#include <string>

#include "SpriteSheet.h"


using namespace std;

void Texture::free()
{
	SDL_DestroyTexture(m_texture);
	m_texture = nullptr;
}

bool Texture::load(SDL_Renderer* renderer, string texture_path)
{
	SDL_Surface* surface = IMG_Load(texture_path.c_str());
	if(surface == NULL)
		return false;

	free();

	m_width = surface->w;
	m_height = surface->h;

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	//app.renderer() this is why i dont like classes, 
	//I need to pass objects lefts and right, even tho there's only ever gonna be one App

	SDL_DestroySurface(surface);

	if(texture == NULL)
		return false;

	m_texture = texture;

	SDL_SetTextureScaleMode(m_texture, SDL_SCALEMODE_NEAREST);
	return true;
}

void Texture::getXYClip(TextureCode texture_code, int& x, int& y)
{
	//texture_code == (num_textures_leftright + SpriteSheet::texture_size * num_textures_updown);
	x = texture_code % (m_width / SpriteSheet::texture_size);
	y = texture_code / (m_width / SpriteSheet::texture_size);

	x *= SpriteSheet::texture_size;
	y *= SpriteSheet::texture_size;
}

SDL_FRect Texture::getTextureClip(TextureCode texture_code)
{
	int x, y;
	getXYClip(texture_code, x, y);

	SDL_FRect clip;
	clip.x = x;
	clip.y = y;
	clip.w = SpriteSheet::texture_size;
	clip.h = SpriteSheet::texture_size;

	return clip;
}
void Texture::render(SDL_Renderer* renderer, int x, int y, TextureCode texture_code)
{
	SDL_FRect clip = getTextureClip(texture_code);

	SDL_FRect dstRect = { x, y, clip.w, clip.h };

	SDL_RenderTexture(renderer, m_texture, &clip, &dstRect);
}

Texture::~Texture()
{
	free();
}