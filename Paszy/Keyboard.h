#pragma once

#include <SDL3/SDL.h>

#include "ButtonStates.h"

enum KeysType
{
	W,
	A,
	D,
	MAX_KEYS
};

class Keyboard
{
	ButtonStates buttons[MAX_KEYS];
public:
	ButtonStates operator()(KeysType key);
	void update(SDL_Event& event);
	void reset();
};

