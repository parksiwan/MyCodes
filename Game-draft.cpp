#include <iostream>
#include "Game.h"

Game::Game(short** tetrad, short x, short y)
{
	for (int i = x; i < FIELD_H; i++)
	{
		for (int j = y; j < FIELD_V; j++)
			field_[i][j] = tetrad[i][j];
	}
}

Game::~Game()
{

}

void Game::checkBoundary()
{

}
