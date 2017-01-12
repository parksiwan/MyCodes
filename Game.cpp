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

void Game::checkMovement(Tetrads* tts)
{
	switch (tts->direction_)
	{
		case DOWN:

		case LEFT:

		case RIGHT:

	}

}

void Game::updateGame(Tetrads* tts)
{
	//Clear game field before updating new position of the falling tetrad
	for (int i = 0; i < F_HEIGHT; i++)
		for (int j = 0; j < F_WIDTH; j++)
			if (field_[i][j] != 9)
				field_[i][j] = 0;
	//'firstRow' is first displayed row of 5x5 tetrad
	int firstRow;
	if (tts->curY_ < 0)
		firstRow = (-1) * tts->curY_;
	else
		firstRow = 0;

	for (int i = firstRow; i < T_HEIGHT; i++)
	{
		for (int j = 0; j < T_WIDTH; j++)
			if (tts->curY_ + i <= 19)
				field_[tts->curY_ + i][tts->curX_ + j] = tts->tetrad_[i][j];
	}
}
