#include "Keyboard.h"

#include <iostream>
using namespace std;

void Keyboard::update(SDL_Event& event)
{
	if (event.type == SDL_EVENT_KEY_DOWN && event.key.repeat == 0)
	{
		if (event.key.key == SDLK_W)
		{
			buttons[W].down = true;
			buttons[W].held = true;
		}
		if (event.key.key == SDLK_D)
		{
			buttons[D].down = true;
			buttons[D].held = true;
		}
		if (event.key.key == SDLK_A)
		{

			buttons[A].down = true;
			buttons[A].held = true;
		}
	}
	if (event.type == SDL_EVENT_KEY_UP)
	{
		if (event.key.key == SDLK_W)
		{
			buttons[W].up = true;
			buttons[W].held = false;
		}
		if (event.key.key == SDLK_D)
		{
			buttons[D].up = true;
			buttons[D].held = false;
		}
		if (event.key.key == SDLK_A)
		{


			buttons[A].up = true;
			buttons[A].held = false;
		}

	}
	/*if (event.type == SDL_EVENT_KEY_DOWN && event.key.repeat == 0)
	{
		switch (event.key.key)
		{
		case SDLK_W:
			buttons[W].down = true;
			buttons[W].held = true;
			break;
		case SDLK_D:
			buttons[D].down = true;
			buttons[D].held = true;
			break;
		case SDLK_A:
			buttons[A].down = true;
			buttons[A].held = true;
			break;
		default:     break;
		}
	}
	if (event.type == SDL_EVENT_KEY_UP)
	{
		switch (event.key.key)
		{
		case SDLK_W:
			buttons[W].up = true;
			buttons[W].held = false;
			break;
		case SDLK_D:
			buttons[D].up = true;
			buttons[D].held = false;
			break;
		case SDLK_A:
			buttons[A].up = true;
			buttons[A].held = false;
			break;
		default:     break;
		}
	}*/
}

void Keyboard::reset()
	{
		for (int i{ 0 }; i < MAX_KEYS; ++i)
		{
			buttons[i].down = false;
			buttons[i].up = false;
		}
	}

ButtonStates Keyboard::operator()(KeysType key)
{
	return buttons[key];
}