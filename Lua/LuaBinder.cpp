#include "LuaBinder.h"
#include "../System/Game.h"
#include "../System/State.h"
#include "../Input/Mouse.h"
#include "../Input/Keyboard.h"
#include <iostream>

using namespace luabind;
using namespace std;

void print(const std::string& str)
{
	cout << str << endl;
}

LuaBinder::LuaBinder()
{
	luaState = luaL_newstate();
	luaL_openlibs(luaState);
}

LuaBinder::~LuaBinder()
{
	lua_close(luaState);
}

void LuaBinder::bind()
{
	open(luaState);
	module(luaState)[
		def("print", &print),

		def("mouseButtonPressed", &Mouse::isButtonPressed),
		class_<Mouse>("Mouse")
		.enum_("Button")
		[
			value("Left", Mouse::Left),
			value("Right", Mouse::Right),
			value("Middle", Mouse::Middle)
		],

		def("keyPressed", &Keyboard::isKeyPressed),
		class_<Keyboard>("Keyboard")
		.enum_("Key")
		[
			value("Left", Keyboard::Left),
			value("Right", Keyboard::Right),
			value("Up", Keyboard::Up),
			value("Down", Keyboard::Down),
			value("Escape", Keyboard::Escape)
		],

		def("Game", &Game::getInstance),
		class_<Game>("")
		.def("run", (void(Game::*)(State*))&Game::run)
		.def("run", (void(Game::*)(State*, int, int))&Game::run)
		.def("run", (void(Game::*)(State*, int, int, const std::string&))&Game::run)
		.def("quit", &Game::quit)
		.def("changeState", &Game::changeState),

		class_<State, State_wrapper>("State")
		.def(constructor<>())
		.def("init", &State::init)
		.def("update", &State::update, &State_wrapper::default_update)
		.def("draw", &State::draw, &State_wrapper::default_draw)
		.def("cleanUp", &State::cleanUp)
		.def("add", (void(State::*)(Sprite*))&State::add),

		class_<sf::Sprite>(""),
		class_<Sprite_wrapper>("")
		.def("update", &Sprite_wrapper::update)
		.def("collide", &Sprite_wrapper::collide)
		.def("draw", &Sprite_wrapper::draw)
		.def("default_update", &Sprite_wrapper::default_update)
		.def("default_collide", &Sprite_wrapper::default_collide)
		.def("default_draw", &Sprite_wrapper::default_draw),
			
		class_<Sprite, sf::Sprite, Sprite_wrapper>("Sprite")
		.def(constructor<>())
		.def("update", &Sprite::update, &Sprite_wrapper::default_update)
		.def("collide", &Sprite::collide, &Sprite_wrapper::default_collide)
		.def("draw", &Sprite::draw, &Sprite_wrapper::default_draw)
		.def("move", &Sprite::move)
		.def("setPosition", (void(Sprite::*)(float, float))&Sprite::setPosition)
		.def("setTexture", &Sprite::setTexture)
		.property("x", &Sprite::getX, &Sprite::setX)
		.property("y", &Sprite::getY, &Sprite::setY)
		.property("depth", &Sprite::getDepth, &Sprite::setDepth)
		.property("type", &Sprite::getType, &Sprite::setType)

	];
}

int LuaBinder::loadScripts()
{
	auto ret = luaL_dofile(luaState, "main.lua");
	if (ret != 0)
	{
		cout << lua_tostring(luaState, -1) << endl;
		return 0;
	}
	else
		return 1;
}