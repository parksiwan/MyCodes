#include <time.h>
#include <windows.h>
#include <SDL.h>
#include "Window.h" 
#include "Tetrads.h"
#include "Board.h"
#include "Game.h"

const int FALLING_SPEED[] = { 250, 200, 150, 100, 50 };

//handles events for two targets that are 'Window' and 'Tetrads'
bool pollEvents(Window& window, Tetrads* Tetrads) {
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		window.pollEvents(event);
		Tetrads->pollEvents(event);
		return true;
	} else
		return false;
}

int messageBoard(Window& window, Board& label1, Board& label2, Board& label3, 
	             Board& label4, Board& label5, Board& label6, Board& label7,
	              Board& lSubBoard, Board& mBoard, Board& iMessage1, Board& iMessage2) {
	SDL_Event event;
	bool gotMessage = false;
	int inputMessage = NOTHING;
	
	while (!gotMessage) {
		label1.draw(); //  labelBoard.draw();
		label2.draw(); //labelLevel.draw();
		label3.draw(); //labelScore.draw();
		label4.draw(); //labelLines.draw();
		label5.draw(); //labelNext.draw();
		label6.draw();
		label7.draw();
		lSubBoard.draw(); // leftSubBoard.draw();

		mBoard.draw(); //mainBoard.draw();
		iMessage1.draw(); //message box
		iMessage2.draw(); //message box
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				inputMessage = EXIT;
				gotMessage = true;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					inputMessage = EXIT;
					gotMessage = true;
					break;
				case SDLK_s:
					inputMessage = START;
					gotMessage = true;
					break;
				case SDLK_r:
					inputMessage = RESTART;
					gotMessage = true;
					break;
				case SDLK_e:
					inputMessage = EXIT;
					gotMessage = true;
					break;
				default:
					break;
				}
			default:
				break;
			}
		}
		window.clear();
	}
	return inputMessage;
}

//select a tetrad and copy it array for display of next tatrad
void getTetrad(int type, int rotation, short tetrad[][VERTICAL]) {
	for (int i = 0; i < HORIZONTAL; i++)
		for (int j = 0; j < VERTICAL; j++)
			tetrad[i][j] = tetrads[type][rotation][i][j];
}

//
//!!!! Exception statement should be implemented!!!!
//
int main(int argc, char* args[]) {
	int curType, nextType, type;
	short nTetrad[HORIZONTAL][VERTICAL] = { { 0 } };
	Window window("AIT Tetris", W_WIDTH, W_HEIGHT);
	Game* tGame = new Game(1);
	Board gameBoard(window, 20, 20, 300, 200, colorImage[0], tGame); //Display board and tetrads

	Board mainBoard(window, 200, 400, 300, 200, 255, 255, 255, 1);   //Display game main board
	Board labelBoard(window, 50, 50, 350, 150, "AIT TETRIS");        //Label above the main board
	Board labelLevel(window, 150, 50, 600, 200, "LEVEL");            //"Level" label inside the sub-board
	Board labelScore(window, 150, 50, 600, 250, "SCORE");            //"Score" label inside the sub-board
	Board labelLines(window, 150, 50, 600, 300, "LINES");            //"Lines" label inside the sub-board

	Board labelInstruction1(window, 150, 50, 600, 500, "<- : left / -> : right");  //"Lines" label inside the sub-board
	Board labelInstruction2(window, 150, 50, 600, 550, "UP/DOWN : rotation");  //"Lines" label inside the sub-board

	Board startingMessage1(window, 150, 50, 340, 300, "PLAY GAME");
	Board startingMessage2(window, 150, 50, 310, 330, "s(START) / e(EXIT)");
	Board endingMessage1(window, 150, 50, 340, 300, "GAME ENDS");
	Board endingMessage2(window, 150, 50, 300, 330, "r(RESTART) / e(EXIT)");

	Board Level(window, 150, 50, 750, 200);                          //Level value inside the sub-board
	Board Score(window, 150, 50, 750, 250);                          //Score value inside the sub-board
	Board Lines(window, 150, 50, 750, 300);                          //Lines value inside the sub-board

	Board leftSubBoard(window, 100, 100, 100, 200, 255, 255, 255, 1);   //Sub board on the left
	Board labelNext(window, 150, 50, 120, 170, "NEXT");                 //"Next" label above the sub-board
	Board next_Tetrads(window, 20, 20, 90, 190, colorImage[0]);         //displays next 'tetrad'

	//If messageBoard() returns EXIT, program terminates
	//For other values like s(START), program continues.
	if (messageBoard(window, labelBoard, labelLevel, labelScore, labelLines, labelNext, 
		             labelInstruction1, labelInstruction2, leftSubBoard, mainBoard,
		             startingMessage1, startingMessage2) == EXIT) {
		return 0;
	}

	Tetrads* ptrTetrad = nullptr;
	srand(time(NULL));
	curType = rand() % TYPE;
	while (!window.isClosed() /*&& !tGame->isEnded()*/ ) {
		if (tGame->isEnded()) {
			if (messageBoard(window, labelBoard, labelLevel, labelScore, labelLines, labelNext,
				labelInstruction1, labelInstruction2, leftSubBoard, mainBoard,
				endingMessage1, endingMessage2) == EXIT) {
				return 0;
			} else {
				tGame->clearField();
			}
		}
		//Modify counting scores
		//When no completed rows exist, a tetrad starts to fall down
		if (!tGame->foundCompletedRows()) {
			tGame->countScores();                     //counts scores
			tGame->increaseLevel();
			if (ptrTetrad == nullptr) {
				nextType = rand() % TYPE;
				getTetrad(nextType, 0, nTetrad);
				type = curType;                                 //'type' is 'curType'
				curType = nextType;                             //'nextType' will be 'curType' at next loop
				ptrTetrad = new Tetrads(type, 0);             //A pointer to Tetrads is generated with the 'type'
			}
			
			if (pollEvents(window, ptrTetrad))
				ptrTetrad->updateTedrads();
			else
				ptrTetrad->movedownTedrads();

			labelBoard.draw();
			labelLevel.draw();
			labelScore.draw();
						
			Level.display(tGame->getLevels());
			Score.display(tGame->getScores());
			Lines.display(tGame->getLines());

			labelInstruction1.draw();
			labelInstruction2.draw();

			labelLines.draw();
			labelNext.draw();
			leftSubBoard.draw();
			next_Tetrads.draw(nTetrad);
			mainBoard.draw();

			tGame->checkMovement(ptrTetrad);
			tGame->updateGame(ptrTetrad);
			gameBoard.draw(tGame);

			window.clear();
			SDL_Delay(FALLING_SPEED[tGame->getLevels() - 1]);
			
			if (ptrTetrad->isEnded()) {
				delete ptrTetrad;
				ptrTetrad = nullptr;
			}
		}
	}
	delete tGame;
	tGame = nullptr;

	return 0;
}
