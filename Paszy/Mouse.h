#pragma once

#include <SDL3/SDL.h>

#include "ButtonStates.h"

enum MouseButtonsType
{
	LMB,
	RMB,
	MMB,
	MAX_MOUSE_BUTTONS
};

class Mouse
{
	ButtonStates buttons[MAX_MOUSE_BUTTONS];
public:
	float x, y;
	bool scrolling_up, scrolling_down, scrolling;
	ButtonStates operator()(MouseButtonsType key);
	void update(SDL_Event& event);
	void reset();
};

