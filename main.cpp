#include <time.h>
#include <windows.h>
#include <SDL.h>
#include "Window.h"
#include "Tetrads.h"
#include "Board.h"
#include "Game.h"

enum FALLING_SPEED { VERY_SLOW = 400, SLOW = 40, MODERATE = 30, FAST = 20, VERY_FAST = 10 };

bool pollEvents(Window& window, Tetrads* Tetrads) 
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) 
	{
		Tetrads->pollEvents(event);
		window.pollEvents(event);
		return true;
	} 
	else
		return false;
}

void startBoard(Window window)
{
	Board label_init(window, 50, 50, 330, 250, 6);
	Board label_finish(window, 50, 50, 330, 250, 7);
	Board label_start(window, 50, 50, 320, 300, 8);
	Board label_restart(window, 50, 50, 320, 300, 9);
	Board label_exit(window, 50, 50, 420, 300, 10);
}

int main(int argc, char* args[]) 
{
	short curType, nextType, type;
	Window window("AIT Tetris", 800, 600);
	
	Board gameBoard(window, 200, 400, 300, 200, 255, 255, 255, 1);      //Display game main board
	Board labelBoard(window, 50, 50, 300, 100, 1);                      //Label above the main board

	Board rightSubBoard(window, 50, 50, 300, 100, 1);
	Board labelLevel(window, 150, 50, 600, 200, 2);
	Board labelScore(window, 150, 50, 600, 250, 3);
	Board labelLines(window, 150, 50, 600, 300, 4);

	Board leftSubBoard(window, 100, 100, 100, 200, 255, 255, 255, 1);  //Sub board on the left
	Board labelNext(window, 150, 50, 120, 170, 5);

	Game Tetris(1);
	srand(time(NULL));
	curType = rand() % TYPE;
	while (!window.isClosed())
	{
		nextType = rand() % TYPE;
		type = curType;              //Always curType will be 'type'
		curType = nextType;          //nextType will be curType at next loop
		Tetrads* ptrTetrad = new Tetrads(type, 0);

		//Tetrads next_Tetrads(20, 20, 130, 230, "green_piece.png", 5, 0);
		//Tetrads Tetrads(window, 40, 40, 300, 200, 1,1,1,1);
		//Tetrads Tetrads(20, 20, 300, 200, "darkgreen_piece.png", 1, 0);

		while (!ptrTetrad->isEnded())
		{
			if (pollEvents(window, ptrTetrad) == true)
			{
				ptrTetrad->updateTedrads();
			}
			else
			{
				ptrTetrad->movedownTedrads();
			}

			next_Tetrads.draw();
			labelBoard.draw();
			gameBoard.draw();

			labelLevel.draw();
			labelScore.draw();
			labelLines.draw();
			labelNext.draw();
			leftSubBoard.draw();
			window.clear();
			Sleep(400);
		}
	}
	return 0;
}
