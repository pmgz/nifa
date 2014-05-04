#pragma once
#include <SFML/Window/Mouse.hpp>
class Mouse : public sf::Mouse
{
public:
	typedef sf::Mouse super;
	Mouse();
	~Mouse();
	static bool isButtonPressed(Button button);
};

