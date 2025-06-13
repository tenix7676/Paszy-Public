#pragma once

#include <string>

enum TextureCode
{
	AIR,
	PLAYER,
	APPLE,
	PLATFORM,
	SPIKE,
	ANT,
	WORM,
	WORM_BLOCK,
	BUSH,
	WIN_BLOCK,
	NUM_TEXTURES
};

namespace SpriteSheet
{
	const int texture_size{ 8 }; // 8x8 pixels
}