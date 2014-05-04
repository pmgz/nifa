#include "Mouse.h"
#include "../System/Game.h"

Mouse::Mouse()
{
}


Mouse::~Mouse()
{
}

bool Mouse::isButtonPressed(Button button)
{
	if (Game::focus)
		return super::isButtonPressed(button);
	else
		return false;
}