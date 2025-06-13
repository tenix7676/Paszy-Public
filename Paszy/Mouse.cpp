#include "Mouse.h"

#include <iostream>
using namespace std;

void Mouse::update(SDL_Event& event)
{
	if(SDL_EVENT_MOUSE_MOTION) SDL_GetMouseState(&x, &y);
	if(event.type == SDL_EVENT_MOUSE_WHEEL) {
		if(event.wheel.y > 0) scrolling_up = true;
		if(event.wheel.y < 0) scrolling_down = true;
		scrolling = true;
	}
	if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
	{
		if(event.button.button == SDL_BUTTON_LEFT)
		{
			buttons[LMB].down = true;
			buttons[LMB].held = true;
		}
		if(event.button.button == SDL_BUTTON_RIGHT)
		{
			buttons[RMB].down = true;
			buttons[RMB].held = true;
		}
		if(event.button.button == SDL_BUTTON_MIDDLE)
		{

			buttons[MMB].down = true;
			buttons[MMB].held = true;
		}
	}
	if(event.type == SDL_EVENT_MOUSE_BUTTON_UP)
	{
		if(event.button.button == SDL_BUTTON_LEFT)
		{
			buttons[LMB].up = true;
			buttons[LMB].held = false;
		}
		if(event.button.button == SDL_BUTTON_RIGHT)
		{
			buttons[RMB].up = true;
			buttons[RMB].held = false;
		}
		if(event.button.button == SDL_BUTTON_MIDDLE)
		{
			buttons[MMB].up = true;
			buttons[MMB].held = false;
		}

	}
}

void Mouse::reset()
{
	scrolling = false;
	scrolling_down = false;
	scrolling_up = false;
	for(int i{ 0 }; i < MAX_MOUSE_BUTTONS; ++i)
	{
		buttons[i].down = false;
		buttons[i].up = false;
	}
}

ButtonStates Mouse::operator()(MouseButtonsType key)
{
	return buttons[key];
}