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

void getTetrad(int type, int rotation, short tetrad[][VERTICAL])
{
	for (int i = 0; i < HORIZONTAL; i++)
	{
		for (int j = 0; j < VERTICAL; j++)
			tetrad[i][j] = tetrads[type][rotation][i][j];
	}
}

int main(int argc, char* args[]) 
{
	int curType, nextType, type;
	short nTetrad[HORIZONTAL][VERTICAL] = { { 0 } };
	Window window("AIT Tetris", W_WIDTH, W_HEIGHT);
	Game* tGame = new Game(1);
	Board gameBoard(window, 20, 20, 300, 200, colorImage[0], tGame);    //Display board and tetrads
	
	Board mainBoard(window, 200, 400, 300, 200, 255, 255, 255, 1);      //Display game main board
	Board labelBoard(window, 50, 50, 300, 100, 1);                      //Label above the main board

	Board labelLevel(window, 150, 50, 600, 200, 2);                     //"Level" label inside the sub-board
	Board labelScore(window, 150, 50, 600, 250, 3);                     //"Score" label inside the sub-board
	Board labelLines(window, 150, 50, 600, 300, 4);                     //"Lines" label inside the sub-board

	Board leftSubBoard(window, 100, 100, 100, 200, 255, 255, 255, 1);   //Sub board on the left
	Board labelNext(window, 150, 50, 120, 170, 5);                      //"Next" label above the sub-board

	srand(time(NULL));
	curType = rand() % TYPE;
	while (!window.isClosed())
	{
		nextType = rand() % TYPE;
		getTetrad(nextType, 0, nTetrad);
		Board next_Tetrads(window, 20, 20, 100, 200, colorImage[nextType]);

		type = curType;                                 //'type' is 'curType'
		curType = nextType;                             //'nextType' will be 'curType' at next loop
		Tetrads* ptrTetrad = new Tetrads(type, 0);      //A pointer to Tetrads is generated with the 'type'
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

			ptrTetrad->movedownTedrads();
			tGame->updateGame(ptrTetrad);
						
			labelBoard.draw();
			labelLevel.draw();
			labelScore.draw();
			labelLines.draw();
			labelNext.draw();
			leftSubBoard.draw();
			next_Tetrads.draw(nTetrad);
			mainBoard.draw();

			gameBoard.draw(tGame);

			window.clear();
			Sleep(200);
		}
		if (ptrTetrad != nullptr)
			delete ptrTetrad;
	}
	delete tGame;
	return 0;
}
