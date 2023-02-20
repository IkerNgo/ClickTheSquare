#include "Game.h"

int main()
{
	//Init srand
	srand(static_cast<unsigned>(time(NULL)));

	//Init game engine
	Game game;

	while (game.running() && !game.getEndGame())
	{
		//Update
		game.update();
		

		//Render
		game.render();

	}



	return 0;
}