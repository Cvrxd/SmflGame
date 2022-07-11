#include"stdafx.h"
#include"Game.h"

int main()
{
	std::srand(static_cast<unsigned int>(std::time(0)));

	std::cout << sizeof(GameState);

	Game game;
	game.run();

	return 0;
}

