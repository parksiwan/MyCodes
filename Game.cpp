//
//Source file : Game.cpp
//Purpose     : Definition of member functions of Game class 
//Features    : Starting & finishing game, checking tetrad's movement & update the snapshot of game
//              before displaying on the screen and removing completed rows and counting scores.
//
#include <iostream>
#include "Game.h"

//Constructor of Game class. Initialise game field 20x10 array and other member variable
//@param level : level of game. starting level is 1 
Game::Game(int level) {
	level_ = level;
	lines_ = 0;
	scores_ = 0;
	scoringRows_ = 0;
	for (int i = 0; i < F_HEIGHT; i++)
		for (int j = 0; j < F_WIDTH; j++)
			field_[i][j] = 0;
}

//Checks a tetrad's movement
//@param tts : pointer to Tetards class. tts is a currently acting tetrad 
void Game::checkMovement(Tetrads* tts) {
	//converts value of tetrad's edge(relative position) into the one on game field (absolute position)
	//(curX, curY) is the position of tetrad[0][0] and each edge value is relative distance from the sides
	//So absolute position can be obtained by adding curX or curY and relevant edges.
	//   0, 0, 0, 0, 0 
	//   0, 0, 1, 0, 0 ----> upedge(1)
	//   0, 0, 1, 1, 0 
	//   0, 0, 1, 0, 0 ----> downedge(3)
	//   0, 0, 0, 0, 0
	//         |  | 
	//    left(2)&right(3)edge each
	//'overlab' is flag variable checking if a tetrad's area overlaps other tedrads or borders
	int downEdge  = tts->curY_ + tts->downEdge_;
	int ddownEdge = tts->curY_ + tts->downEdge_;
	int leftEdge  = tts->curX_ + tts->leftEdge_;
	int rightEdge = tts->curX_ + tts->rightEdge_;
	int upEdge    = tts->curY_ + tts->upEdge_;
	int overlap = 0;
	//tts->tetrad_[][]'s entries having 1 are blocks consisting of tetrad
	//field_[][]'s entries having 9 are blocks being non-active
	//1)if tts->tetrad_[][] * field_[][] == 9, it means overlapping happens
	//2)if each of Edge(downEdge, upEdge, leftEdge, rightEdge) value go beyond border, it means conflicts happens
	//For those cases, move the tetrad back to the previous position
	switch (tts->direction_) {
		case DOWN:
			if (downEdge <= 19 && downEdge > 0)
				for (int i = tts->downEdge_; i >= tts->upEdge_ && overlap == 0; i--)
					for (int j = tts->leftEdge_; j <= tts->rightEdge_ && overlap == 0; j++) 
						if ((tts->tetrad_[i][j] * field_[tts->curY_ + i][tts->curX_ + j]) == 9)
							overlap++;
			//tetrad has reached the bottom or on the other tetrads already exist
			//terminate the tetrad
			if (overlap > 0 || downEdge > 19) {
				tts->ended_ = true;
				tts->curY_--;
			}
			//tetrad has reached the bottom, terminate the tetrad
			if (overlap == 0 && downEdge == 19)
				tts->ended_ = true;
			break;
		case LEFT:
			for (int i = tts->downEdge_; i >= tts->upEdge_ && overlap == 0; i--)
				for (int j = tts->leftEdge_; j <= tts->rightEdge_ && overlap == 0; j++)
					if ((tts->tetrad_[i][j] * field_[tts->curY_ + i][tts->curX_ + j]) == 9)
						overlap++;
			//tetrad has gone beyond left border, so move back to the right
			if (overlap > 0 || leftEdge < 0)
				tts->curX_++;
			break;
		case RIGHT:
			for (int i = tts->downEdge_; i >= tts->upEdge_ && overlap == 0; i--)
				for (int j = tts->leftEdge_; j <= tts->rightEdge_ && overlap == 0; j++)
					if ((tts->tetrad_[i][j] * field_[tts->curY_ + i][tts->curX_ + j]) == 9)
						overlap++;
			//tetrad has gone beyond right border, so move back to the left
			if (overlap > 0 || rightEdge > 9)
				tts->curX_--;
			break;
		case DDOWN:
			int k = 0;
			//keep going down. when it finds the bottom or other tetrad, it stops at 'k' 
			for (k = ddownEdge; k < F_HEIGHT && overlap == 0; k++)
				for (int i = tts->downEdge_; i >= tts->upEdge_ && overlap == 0; i--)
					for (int j = tts->leftEdge_; j <= tts->rightEdge_ && overlap == 0; j++)
						if ((tts->tetrad_[i][j] * field_[k][tts->curX_ + j]) == 9) {
							tts->curY_ = k - tts->downEdge_ - 1;
							overlap++;
						}

			if (overlap == 0) {
				tts->curY_ = k - tts->downEdge_ - 1;
				tts->ended_ = true;
			}
			break;
	}
}

//Update position of a tetrad onto the game field
//@param tts : pointer to Tetards class. tts is a currently acting tetrad 
void Game::updateGame(Tetrads* tts) {
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

	for (int i = firstRow; i < T_HEIGHT; i++) {
		for (int j = 0; j < T_WIDTH; j++)
			if (tts->curY_ + i <= 19)
				if (tts->tetrad_[i][j] != 0)
					//if tetrad_[][] reaches the bottom, 9 is copied to field_[][], otherwise 1 is copied
					if (tts->ended_ == true) 
						field_[tts->curY_ + i][tts->curX_ + j] = tts->tetrad_[i][j] * 9;
					else
						field_[tts->curY_ + i][tts->curX_ + j] = tts->tetrad_[i][j];
	}
}

//'Game::isEnded()' returns true if piles of tetrads reach the top. 
//If the position where a tetrad starts to fall down is filled with any tetrad already, 
//game should be ended cause no more tetrad can fall down
bool Game::isEnded() {
	int count = 0;
	
	for (int i = 3; i < T_WIDTH + 3 && count == 0; i++)
		if (field_[0][i] == 9)
			count++;

	if (count > 0) 
		return true;
	else 
		return false;
}

//returns boolean when a completed row found increasing lines_ and scoringRows_ by 1
//any completed row is immediately removed by 'this->removeCompletedRows()'
bool Game::foundCompletedRows() {
	int sum = 0;
	bool flag = true;

	for (int i = F_HEIGHT - 1; i >= 0 && flag == true; i--) {
		for (int j = 0; j < F_WIDTH; j++)
			sum += field_[i][j];

		//when sum of all the entries of a row equals to 90, the row is completed with tatrad blocks
		if (sum == 90) {
			lines_++;
			scoringRows_++;
			this->removeCompletedRows(i);
			flag = false;
			return true;
		}
		sum = 0;
	}
	return false;
}

//Remove 'row'th row
//@param row : number of row index to be removed
void Game::removeCompletedRows(int row) {
	//for first row, simply remove it by assigning 0 to field_[row][]
	if (row == 0)
		for (int j = 0; j < F_WIDTH; j++)
			field_[row][j] = 0;
	else {
		//for the other cases, after removing 'row'th row, repositioning of all the tetrads above the row should be done
		for (int i = row; i > 0; i--) {
			for (int j = 0; j < F_WIDTH; j++) {
				//upper block([i-1]) is copied to current block([i])
				field_[i][j] = field_[i - 1][j];
				//if lower block is empty, current block should go down more until it reaches bottom or other block
				if (i < F_HEIGHT - 1 && field_[i + 1][j] == 0 && field_[i - 1][j] == 9) {
					int k = i + 1;
					bool isEmpty = true;
					while (k <= F_HEIGHT - 1 && isEmpty) {
						if (field_[k][j] != 0) isEmpty = false;
						else k++;
					}
					//final position([k-1]) is filled with current block([i])
					//current block([i]) is filled with 0
					field_[k - 1][j] = field_[i][j];
					field_[i][j] = 0;
				}
			}
		}
	}
}

//Scores Calculation : weigth(10, 30, 60, 100) * level * number of completed rows
//scoringRows is the number of removed lines at a time
void Game::countScores() {
	int scores = 0;

	if (scoringRows_ == 0)
		scores = 0;
	else if (scoringRows_ == 1)
		scores = 10 * level_ * scoringRows_;
	else if (scoringRows_ == 2)
		scores = 30 * level_ * scoringRows_;
	else if (scoringRows_ == 3)
		scores = 60 * level_ * scoringRows_;
	else if (scoringRows_ >= 4)
		scores = 100 * level_ * scoringRows_;

	//summed scores is assigned to scores_ and scoringRows is initialsed
	scores_ += scores;
	scoringRows_ = 0;
}

//increases games's level based on the scores obtained so far as below
void Game::increaseLevel() {
	if (scores_ >= 2500)
		level_ = 5;
	else if (scores_ >= 1500)
		level_ = 4;
	else if (scores_ >= 1000)
		level_ = 3;
	else if (scores_ >= 500)
		level_ = 2;
	else if (scores_ >= 0)
		level_ = 1;
}

//clears game field for new game
void Game::clearField() {
	for (int i = 0; i < F_HEIGHT; i++)
		for (int j = 0; j < F_WIDTH; j++)
			field_[i][j] = 0;
}

//returns lines completed of game
int Game::getLines() {
	return lines_;
}

//returns scores of game
int Game::getScores() {
	return scores_;
}

//returns level of game
int Game::getLevels() {
	return level_;
}
