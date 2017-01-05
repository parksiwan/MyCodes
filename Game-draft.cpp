#include <iostream>
#include "Game.h"

Game::Game(short level)
{
	level_ = level;
	lines_ = 0;
	scores_ - 0;
	for (int i = 0; i < FIELD_H; i++)
	{
		for (int j = 0; j < FIELD_V; j++)
			field_[i][j] = 0;
	}
}

Game::~Game()
{

}

void Game::checkBoundary()
{

}

void Game::updateGame(Tetrads* tts, short x, short y, short startRow)
{
	for (int i = startRow; i < TETRAD_H; i++)
	{
		for (int j = 0; j < TETRAD_V; j++)
			field_[x + i][y + j] = tts->tetrad_[i][j];
	}
}
