#include <stdafx.h>
#include <Game/Game.h>

int main()
{
	std::srand(static_cast<unsigned int>(std::time(0)));

	Game game;
	game.run();

	return 0;
}

