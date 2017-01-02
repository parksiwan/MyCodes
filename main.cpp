#include <windows.h>
#include <SDL.h>
#include "Window.h"
#include "Tetrads.h"
#include "Board.h"

enum FALLING_SPEED { VERY_SLOW = 400, SLOW = 40, MODERATE = 30, FAST = 20, VERY_FAST = 10 };

bool pollEvents(Window& window, Tetrads& Tetrads) 
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) 
	{
		Tetrads.pollEvents(event);
		window.pollEvents(event);
		return true;
	} 
	else
		return false;
}

int main(int argc, char* args[]) 
{
	Window window("AIT Tetris", 800, 600);
	//Tetrads Tetrads(window, 120, 120, 100, 100, "res/camera.png");
	Board game_board(window, 200, 400, 300, 200, 255, 255, 255, 1);      //Display game main board
	//Board label_init(window, 50, 50, 330, 250, 6);
	//Board label_finish(window, 50, 50, 330, 250, 7);
	//Board label_start(window, 50, 50, 320, 300, 8);
	//Board label_restart(window, 50, 50, 320, 300, 9);
	//Board label_exit(window, 50, 50, 420, 300, 10);
	
	Board label_level(window, 150, 50, 600, 200, 2);
	Board label_score(window, 150, 50, 600, 250, 3);
	Board label_lines(window, 150, 50, 600, 300, 4);
	Board label_next(window, 150, 50, 120, 170, 5);

	Board left_sub_board(window, 100, 100, 100, 200, 255, 255, 255, 1);  //Sub board on the left
	Board label_board(window, 50, 50, 300, 100, 1);                      //Label above the main board
	
	Tetrads next_Tetrads(window, 20, 20, 130, 230, "green_piece.png", 5, 0);
	//Tetrads Tetrads(window, 40, 40, 300, 200, 1,1,1,1);
	Tetrads Tetrads(window, 20, 20, 300, 200, "darkgreen_piece.png", 1, 0);

	while (!window.isClosed()) 
	{
		//Tetrads.rotateDown();
		label_board.draw();
		game_board.draw();
		//label_init.draw();
		//label_finish.draw();
		//label_start.draw();
		//label_restart.draw();
		//label_exit.draw();

		label_level.draw();
		label_score.draw();
		label_lines.draw();
		label_next.draw();
		left_sub_board.draw();

		next_Tetrads.draw();
		//Tetrads.draw();
		if (pollEvents(window, Tetrads) == true)
		{
			//window.clear();
			Tetrads.draw();
			window.clear();
			continue;
		}
		else
		{
			Tetrads.moveDown();
			Tetrads.draw();
			window.clear();
		}
		Sleep(400);
	}

	return 0;
}
