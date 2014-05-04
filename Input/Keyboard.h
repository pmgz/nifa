#pragma once
#include <SFML\Window\Keyboard.hpp>
class Keyboard : public sf::Keyboard
{
public:
	typedef sf::Keyboard super;
	Keyboard();
	~Keyboard();
	static bool isKeyPressed(Key key);
};

