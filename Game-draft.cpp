#include <iostream>
#include "Game.h"

Game::Game(int level)
{
	level_ = level;
	lines_ = 0;
	scores_ = 0;
	for (int i = 0; i < F_HEIGHT; i++)
	{
		for (int j = 0; j < F_WIDTH; j++)
			field_[i][j] = 0;
	}
}

Game::~Game()
{

}

void Game::checkBoundary()
{

}

void Game::updateGame(Tetrads* tts)
{
	int firstRow;

	if (tts->curY_ < 0)
		firstRow = (-1) * tts->curY_;
	else
		firstRow = 0;

	for (int i = firstRow; i < T_HEIGHT; i++)
	{
		for (int j = 0; j < T_WIDTH; j++)
			field_[tts->curY_ + i][tts->curX_ + j] = tts->tetrad_[i][j];
	}
}
