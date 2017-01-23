#include <time.h>
#include <windows.h>
#include <SDL.h>
#include "Window.h"
#include "Tetrads.h"
#include "Board.h"
#include "Game.h"

enum FALLING_SPEED { VERY_SLOW = 200, SLOW = 150, MODERATE = 100, FAST = 50, VERY_FAST = 10 };

//handles events for two targets that are 'Window' and 'Tetrads'
bool pollEvents(Window& window, Tetrads* Tetrads) 
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) 
	{
		window.pollEvents(event);
		Tetrads->pollEvents(event);
		return true;
	} 
	else
		return false;
}

void startBoard(Window window)
{
	//Board label_init(window, 50, 50, 330, 250, "PLAY GAME ?");
	//Board label_finish(window, 50, 50, 330, 250, "GAME ENDS");
	//Board label_start(window, 50, 50, 320, 300, "START");
	//Board label_restart(window, 50, 50, 320, 300, "RESTART");
	//Board label_exit(window, 50, 50, 420, 300, "EXIT");
}

//select a tetrad and copy it array for display of next tatrad
void getTetrad(int type, int rotation, short tetrad[][VERTICAL])
{
	for (int i = 0; i < HORIZONTAL; i++)
		for (int j = 0; j < VERTICAL; j++)
			tetrad[i][j] = tetrads[type][rotation][i][j];
}

//
//!!!! Exception statement should be implemented!!!!
//
int main(int argc, char* args[])
{
	int curType, nextType, type;
	short nTetrad[HORIZONTAL][VERTICAL] = { { 0 } };
	Window window("AIT Tetris", W_WIDTH, W_HEIGHT);
	Game* tGame = new Game(1);
	Board gameBoard   (window, 20, 20, 300, 200, colorImage[0], tGame); //Display board and tetrads

	Board mainBoard   (window, 200, 400, 300, 200, 255, 255, 255, 1);   //Display game main board
	Board labelBoard  (window, 50, 50, 350, 150, "AIT TETRIS");                    //Label above the main board
	Board labelLevel  (window, 150, 50, 600, 200, "LEVEL");                   //"Level" label inside the sub-board
	Board labelScore  (window, 150, 50, 600, 250, "SCORE");                   //"Score" label inside the sub-board
	Board labelLines  (window, 150, 50, 600, 300, "LINES");                   //"Lines" label inside the sub-board
	Board leftSubBoard(window, 100, 100, 100, 200, 255, 255, 255, 1);   //Sub board on the left
	Board labelNext   (window, 150, 50, 120, 170, "NEXT");                   //"Next" label above the sub-board
	Board next_Tetrads(window, 20, 20, 90, 190, colorImage[1]);         //displays next 'tetrad'

	Tetrads* ptrTetrad = nullptr;
	srand(time(NULL));
	curType = rand() % TYPE;
	while (!window.isClosed() && !tGame->isEnded())
	{
		if (tGame->foundCompletedRows())
		{
			tGame->countScores();
		}
		else
		{
			if (ptrTetrad == nullptr)
			{
				nextType = rand() % TYPE;
				getTetrad(nextType, 0, nTetrad);
				type = curType;                                 //'type' is 'curType'
				curType = nextType;                             //'nextType' will be 'curType' at next loop
				ptrTetrad = new Tetrads(type, 0);             //A pointer to Tetrads is generated with the 'type'
			}

			if (pollEvents(window, ptrTetrad) == true)
				ptrTetrad->updateTedrads();
			else
				ptrTetrad->movedownTedrads();

			labelBoard.draw();
			labelLevel.draw();
			labelScore.draw();
			labelLines.draw();
			labelNext.draw();
			leftSubBoard.draw();
			next_Tetrads.draw(nTetrad);
			mainBoard.draw();

			tGame->checkMovement(ptrTetrad);
			tGame->updateGame(ptrTetrad);
			gameBoard.draw(tGame);

			window.clear();
			Sleep(SLOW);

			if (ptrTetrad->isEnded())
			{
				delete ptrTetrad;
				ptrTetrad = nullptr;
			}
		}
	}
	delete tGame;
	tGame = nullptr;
	
	return 0;
}
