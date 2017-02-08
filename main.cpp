//
//Source file : main.cpp
//Purpose     : main program starting 
//Features    : Starts & operates game by declaring relevant classes and member functions
//
#include <time.h>
#include <windows.h>
#include <SDL.h>
#include "Window.h" 
#include "Tetrads.h"
#include "Board.h"
#include "Game.h"

//the values mean time(ms). The smaller, the faster.
const int FALLING_SPEED[] = { 250, 200, 150, 100, 50 };

//handles events for two targets that are 'Window' and 'Tetrads'
//@param window    : reference varaible to class Window
//@param Tetrads   : pointer variable to class Tatrads
bool pollEvents(Window& window, Tetrads* Tetrads) {
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		window.pollEvents(event);
		Tetrads->pollEvents(event);
		return true;
	} else
		return false;
}

//shows input message box where user can input
//@param label1    : label "Board"
//@param label2    : label "Level"
//@param label3    : label "Score"
//@param label4    : label "Lines"
//@param label5    : label "Next"
//@param label6    : label instruction 1
//@param label7    : label instruction 2
//@param lSubBoard : left SubBoard
//@param mBoard    : main Board
//@param iMessage1 : starting message 1
//@param iMessage2 : starting message 2
int messageBoard(Window& window, Board& label1, Board& label2, Board& label3, 
	             Board& label4, Board& label5, Board& label6, Board& label7,
	              Board& lSubBoard, Board& mBoard, Board& iMessage1, Board& iMessage2) {
	SDL_Event event;
	bool gotMessage = false;
	int inputMessage = NOTHING;
	
	while (!gotMessage) {
		label1.draw();      //label "Board"
		label2.draw();      //label "Level"
		label3.draw();      //label "Score"
		label4.draw();      //label "Lines"
		label5.draw();      //label "Next"
		label6.draw();      //label instruction 1
		label7.draw();      //label instruction 2
		lSubBoard.draw();   //left SubBoard

		mBoard.draw();      //main Board
		iMessage1.draw();   //starting message 1
		iMessage2.draw();   //starting message 2
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
//@param type       : type of tetrad
//@param rotation   : one of the rotated shapes of tetrad
//@param tetrad[][] : 5x5 array holding tetrad information
void getTetrad(int type, int rotation, short tetrad[][VERTICAL]) {
	for (int i = 0; i < HORIZONTAL; i++)
		for (int j = 0; j < VERTICAL; j++)
			tetrad[i][j] = tetrads[type][rotation][i][j];
}

int main(int argc, char* args[]) {
	int curType, nextType, type;
	short nTetrad[HORIZONTAL][VERTICAL] = { { 0 } };
	Window window("AIT Tetris", W_WIDTH, W_HEIGHT);
	Game* tGame = new Game(1);
	Board gameBoard(window, 20, 20, 300, 200, pieceImage, tGame);    //Display board and tetrads

	Board mainBoard(window, 200, 400, 300, 200, 255, 255, 255, 1);   //Display game main board
	Board labelBoard(window, 50, 50, 350, 150, "AIT TETRIS");        //Title Label above the main board
	Board labelLevel(window, 150, 50, 600, 200, "LEVEL");            //"Level" label inside the sub-board
	Board labelScore(window, 150, 50, 600, 250, "SCORE");            //"Score" label inside the sub-board
	Board labelLines(window, 150, 50, 600, 300, "LINES");            //"Lines" label inside the sub-board

	Board labelInstruction1(window, 150, 50, 600, 500, "<- : left / -> : right");  //Instruction label
	Board labelInstruction2(window, 150, 50, 600, 550, "UP/DOWN : rotation");      //Instruction label

	Board startingMessage1(window, 150, 50, 340, 300, "PLAY GAME");             //message box
	Board startingMessage2(window, 150, 50, 310, 330, "s(START) / e(EXIT)");    //message box
	Board endingMessage1(window, 150, 50, 340, 300, "GAME ENDS");               //message box
	Board endingMessage2(window, 150, 50, 300, 330, "r(RESTART) / e(EXIT)");    //message box

	Board Level(window, 150, 50, 750, 200);                          //Level value inside the sub-board
	Board Score(window, 150, 50, 750, 250);                          //Score value inside the sub-board
	Board Lines(window, 150, 50, 750, 300);                          //Lines value inside the sub-board

	Board leftSubBoard(window, 100, 100, 100, 200, 255, 255, 255, 1);   //Sub board on the left
	Board labelNext(window, 150, 50, 120, 170, "NEXT");                 //"Next" label above the sub-board
	Board next_Tetrads(window, 20, 20, 90, 190, pieceImage);            //displays next 'tetrad'

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
	while (!window.isClosed()) {
		if (tGame->isEnded()) {
			//When game finishes, it shows message box asking to exit or restart 
			if (messageBoard(window, labelBoard, labelLevel, labelScore, labelLines, labelNext,
				labelInstruction1, labelInstruction2, leftSubBoard, mainBoard,
				endingMessage1, endingMessage2) == EXIT) {
				return 0;
			} else {
				tGame->clearField();
			}
		}
		//When no completed rows exist, a tetrad starts to fall down
		//Otherwise, removing and counting rows are performed inside 'tGame->foundCompletedRows()'
		if (!tGame->foundCompletedRows()) {
			tGame->countScores();                           //counts scores
			tGame->increaseLevel();                         //increase level if required
			//creates a new tetrad 
			if (ptrTetrad == nullptr) {
				nextType = rand() % TYPE;
				getTetrad(nextType, 0, nTetrad);
				type = curType;                             //'type' is 'curType'
				curType = nextType;                         //'nextType' will be 'curType' at next loop
				ptrTetrad = new Tetrads(type, 0);           //A pointer to Tetrads is generated with the 'type'
			}
			//if events happen, process them, otherwise move down the tetrad
			if (pollEvents(window, ptrTetrad))
				ptrTetrad->updateTedrads();
			else
				ptrTetrad->movedownTedrads();
			//----display entities
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
			//----display entities
			//checks movement of moving tetrad and snapshots it for display
			tGame->checkMovement(ptrTetrad);
			tGame->updateGame(ptrTetrad);
			gameBoard.draw(tGame);

			window.clear();
			//falling speed is calculated by checking current level
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
