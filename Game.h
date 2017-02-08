//
//Header file : Game.h
//Purpose     : Declaration of Game class 
//Features    : This class is core of the game. The game is played on this class and controlled 
//              by this class. All the game rules and counting scores are performed by this class'
//              member functions.
//
#ifndef GAME_H
#define GAME_H

#include "Tetrads.h"

//F_HEIGHT : height of game field
//F_WIDTH  : width of game field
//T_HEIGHT : height of tetrad array
//T_WIDTH  : width of tetrad array
const short F_HEIGHT = 20;
const short F_WIDTH = 10;
const short T_HEIGHT = 5;
const short T_WIDTH = 5;

//lines_                    : accumulated number of rows(lines) completed
//scores_                   : score of game, calculated by 'lines_'
//level_                    : level of game, default is 1
//scoringRows_              : number of rows(lines) completed and to be counted as scores
//field_[F_HEIGHT][F_WIDTH] : game field 10 X 20 array
class Game {
	//Board class can accesse and change variables in Game class
	friend class Board;
public:
	Game(int level);
	
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
