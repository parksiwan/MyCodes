#ifndef GAME_H
#define GAME_H

#include "Tetrads.h"

const short FIELD_H = 20;
const short FIELD_V = 10;
const short TETRAD_H = 5;
const short TETRAD_V = 5;

class Game
{
public:
	Game(short level);
	~Game();
	void checkBoundary();
	void updateGame(Tetrads* tts, short x, short y, short startRow);

private:
	int lines_;
	int scores_;
	short level_;
	short field_[FIELD_H][FIELD_V] = { { 0 } };
};

#endif
