#ifndef GAME_H
#define GAME_H

#include "Tetrads.h"

const short F_HEIGHT = 20;
const short F_WIDTH = 10;
const short T_HEIGHT = 5;
const short T_WIDTH = 5;

class Game
{
	friend class Board;
public:
	Game(int level);
	~Game();
	void checkBoundary();
	void updateGame(Tetrads* tts);

private:
	int lines_;
	int scores_;
	int level_;
	short field_[F_HEIGHT][F_WIDTH] = { { 0 } };
};
