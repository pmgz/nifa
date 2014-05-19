#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>

float Game::deltaTime;
bool Game::focus = true;
bool Game::gameEnded = false;

void Game::run(State* state, int width, int height, const std::string& title)
{
	stateChanged = false;
	int framerate = 60;
	if (window == nullptr) delete window;
	window = new sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close);
	window->setVerticalSyncEnabled(true);
	window->setFramerateLimit(framerate);
	currentState = state;

	sf::Clock deltaClock;
	while (window->isOpen())
	{
		switchState();
		sf::Event event;
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window->close();
				break;
			case sf::Event::GainedFocus:
				focus = true;
				break;
			case sf::Event::LostFocus:
				focus = false;
				break;
			}
		}
		currentState->update();
		window->clear(sf::Color(255, 255, 255, 255));
		currentState->draw();
		window->display();
		if (stateChanged) currentState->cleanUp();
		dt = deltaClock.restart();
		deltaTime = dt.asSeconds() * framerate;
	}
}

void Game::run(State* state, int width, int height)
{
	run(state, width, height, "Default title");
}

void Game::run(State* state)
{
	run(state, 640, 480, "Default title");
}

void Game::changeState(State* state)
{
	nextState = state;
	stateChanged = true;
}

void Game::switchState()
{
	if (stateChanged) currentState = nextState;
}

sf::RenderWindow* Game::getWindow()
{
	return window;
}

void Game::quit()
{
	window->close();//gameEnded = true;
}