#include "Keyboard.h"
#include "../System/Game.h"

Keyboard::Keyboard()
{
}


Keyboard::~Keyboard()
{
}

bool Keyboard::isKeyPressed(Key key)
{
	if (Game::focus)
		return super::isKeyPressed(key);
	else
		return false;
}
