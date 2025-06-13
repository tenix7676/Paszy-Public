#pragma once

#include <SDL3/SDL.h>

namespace FPS
{
	const Uint64 TICKS_PER_SECOND{ SDL_GetPerformanceFrequency() };
	const int FPS{ 60 };

	void DelayTillFPS(Uint64 start);
}