#include <conio.h>
#include <iostream>
#include <vector>
#include <string>
#include "SDL.h"

#include "GameManager.h"
#undef main

using namespace std;

int main(int args, char* argv[])
{
	GameManager game(1280, 720);

	//Run game loop
	game.GameLoop();
}