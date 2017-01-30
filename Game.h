#ifndef GAME_H
#define GAME_H

#include "Tetrads.h"

const short F_HEIGHT = 20;
const short F_WIDTH = 10;
const short T_HEIGHT = 5;
const short T_WIDTH = 5;

class Game {
	friend class Board;
public:
	Game(int level);
	~Game();
	void checkMovement(Tetrads* tts);
	void updateGame(Tetrads* tts);
	bool isEnded();
	bool foundCompletedRows();
	void removeCompletedRows(int row);
	void countScores();
	void increaseLevel();
	void clearField();
	int getLines();
	int getScores();
	int getLevels();

private:
	int lines_;                                     //accumulated number of rows(lines) completed
	int scores_;                                    //score of game, calculated by 'lines_'
	int level_;                                     //level of game, default is 1
	int scoringRows_;                               //number of rows(lines) completed and to be counted as scores
	short field_[F_HEIGHT][F_WIDTH] = { { 0 } };    //game field 10 X 20 array
};

#endif
