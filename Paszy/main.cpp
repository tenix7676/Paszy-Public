#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

#include "App.h"

int main(int argc, char** argv)
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	App app;
	while(app.handleEvents())
	{
		app.run();
	}

	return 0; 
}