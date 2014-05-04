#include "stdio.h"
#include <SFML/Graphics.hpp>
#include <time.h>
#include <random>
#include <iostream>
#include <conio.h>
#include "Lua/LuaBinder.h"

using namespace std;

int main(int argc, char* argv[])
{
	srand(time(0));

	LuaBinder luaBinder;
	luaBinder.bind();
	int v = luaBinder.loadScripts();
	if (!v) getch();

	return 0;
}

