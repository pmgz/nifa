#include "stdio.h"
#include <SFML/Graphics.hpp>
#include <time.h>
#include <random>
#include <iostream>
#include "Lua/LuaBinder.h"

using namespace std;

int main(int argc, char* argv[])
{
	srand(time(0));

	LuaBinder luaBinder;
	luaBinder.bind();
	int v = luaBinder.loadScripts();
	//cin >> v;

	return 0;
}

