#pragma once
#include "State.h"
#include "../Util/Singleton.h"
#include <string>
#include <SFML/Graphics.hpp>

class Game : public Singleton<Game>
{
protected:
	State* currentState;
	State* nextState;
	sf::RenderWindow *window;
	sf::Time dt;
	bool stateChanged;

private:
	void switchState();

public:
	static float deltaTime;
	static bool focus;
	static bool gameEnded;

	void run(State* state);
	void run(State* state, int width, int height);
	void run(State* state, int width, int height, const std::string& title);

	void changeState(State* state);

	void quit();

	sf::RenderWindow* getWindow();
};

