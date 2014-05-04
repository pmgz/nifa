#pragma once

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "luabind/luabind.hpp"

using namespace luabind;

class LuaBinder
{
private:
	lua_State* luaState;
public:
	LuaBinder();
	~LuaBinder();
	void bind();
	int loadScripts();
};

