#include <iostream>
#include <SDL_image.h>
#include "Tetrads.h"

Tetrads::Tetrads(int type, int rotation) {
	curX_ = 3;                                       //x coordination of far-left of "tetrad_"
	curY_ = (-1) * startingRow[type][rotation][0];   //y coordination of first row from bottom that is not value of '0'
	type_ = type;
	rotation_ = rotation;
	
	for (int i = 0; i < HORIZONTAL; i++)
		for (int j = 0; j < VERTICAL; j++)
			tetrad_[i][j] = tetrads[type_][rotation_][i][j];
	
	downEdge_ = edgeLine[type_][rotation_][0];
	leftEdge_ = edgeLine[type_][rotation_][1];
	rightEdge_ = edgeLine[type_][rotation_][2];
	upEdge_ = edgeLine[type_][rotation_][3];
}

Tetrads::~Tetrads() {

}

void Tetrads::pollEvents(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				curX_ -= 1;
				direction_ = LEFT;
				break;
			case SDLK_RIGHT:
				curX_ += 1;
				direction_ = RIGHT;
				break;
			case SDLK_UP:
				if (rotation_ == 3)
					rotation_ = 0;
				else
					rotation_ += 1;
				break;
			case SDLK_DOWN:
				if (rotation_ == 0)
					rotation_ = 3;
				else
					rotation_ -= 1;
				break;
			case SDLK_SPACE:
				//drop down
				curY_ += 1;
				direction_ = DDOWN;
				break;
			case SDLK_ESCAPE:
				ended_ = true;
				break;
		}
	} 
}

void Tetrads::movedownTedrads() {
	curY_ += 1;
	direction_ = DOWN;
}

void Tetrads::updateTedrads() {
	for (int i = 0; i < HORIZONTAL; i++)
		for (int j = 0; j < VERTICAL; j++)
			tetrad_[i][j] = tetrads[type_][rotation_][i][j];
	
	downEdge_  = edgeLine[type_][rotation_][0];
	leftEdge_  = edgeLine[type_][rotation_][1];
	rightEdge_ = edgeLine[type_][rotation_][2];
	upEdge_    = edgeLine[type_][rotation_][3];
}

bool Tetrads::isEnded() {
	if (ended_ == true || curY_ == 20)
		return true;

	return false;
}

int Tetrads::getCurrentX() {
	return curX_;
}

int Tetrads::getCurrentY() {
	return curY_;
}
