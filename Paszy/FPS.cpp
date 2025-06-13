#include "FPS.h"

#include <SDL3/SDL.h>

namespace FPS
{
	void DelayTillFPS(Uint64 start)
	{
		Uint64 end = SDL_GetPerformanceCounter();
		while(end - start < TICKS_PER_SECOND / FPS)
		{
			end = SDL_GetPerformanceCounter();
		}
	}
}