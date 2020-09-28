#include"Game.h"



int main()
{
	Game* game = new Game();
	if (game->Initialized("hello world ImGui ", 1280, 720))
	{
		game->Run();
	}

	return 0;
}