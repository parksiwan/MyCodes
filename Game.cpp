#include <iostream>
#include "Game.h"

Game::Game(int level) {
	level_ = level;
	lines_ = 0;
	scores_ = 0;
	scoringRows_ = 0;
	for (int i = 0; i < F_HEIGHT; i++)
		for (int j = 0; j < F_WIDTH; j++)
			field_[i][j] = 0;
}

Game::~Game()
{

}

//Down  edge = curY_ + tts->downEdge_  (=0)
//Left  edge = curX_ + tts->leftEdge_  (=1)
//Right edge = curX_ + tts->rightEdge_ (=2)
//Up    edge = curY_ + tts->upEdge_    (=3)
void Game::checkMovement(Tetrads* tts) {
	//actual edge of each tetrad
	int downEdge  = tts->curY_ + tts->downEdge_;
	int ddownEdge = tts->curY_ + tts->downEdge_;
	int leftEdge  = tts->curX_ + tts->leftEdge_;
	int rightEdge = tts->curX_ + tts->rightEdge_;
	int upEdge    = tts->curY_ + tts->upEdge_;
	int overlap = 0;
	switch (tts->direction_) {
		case DOWN:
			if (downEdge <= 19 && downEdge > 0)
				for (int i = tts->downEdge_; i >= tts->upEdge_ && overlap == 0; i--)
					for (int j = tts->leftEdge_; j <= tts->rightEdge_ && overlap == 0; j++) 
						if ((tts->tetrad_[i][j] * field_[tts->curY_ + i][tts->curX_ + j]) == 9)
							overlap++;
						
			if (overlap > 0 || downEdge > 19) {
				tts->ended_ = true;
				tts->curY_--;
			}
			if (overlap == 0 && downEdge == 19)
				tts->ended_ = true;
			break;
		case LEFT:
			for (int i = tts->downEdge_; i >= tts->upEdge_ && overlap == 0; i--)
				for (int j = tts->leftEdge_; j <= tts->rightEdge_ && overlap == 0; j++)
					if ((tts->tetrad_[i][j] * field_[tts->curY_ + i][tts->curX_ + j]) == 9)
						overlap++;
			if (overlap > 0 || leftEdge < 0)
				tts->curX_++;
			break;
		case RIGHT:
			for (int i = tts->downEdge_; i >= tts->upEdge_ && overlap == 0; i--)
				for (int j = tts->leftEdge_; j <= tts->rightEdge_ && overlap == 0; j++)
					if ((tts->tetrad_[i][j] * field_[tts->curY_ + i][tts->curX_ + j]) == 9)
						overlap++;
			if (overlap > 0 || rightEdge > 9)
				tts->curX_--;
			break;
		case DDOWN:
			int k = 0;
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
					if (tts->ended_ == true) 
						field_[tts->curY_ + i][tts->curX_ + j] = tts->tetrad_[i][j] * 9;
					else
						field_[tts->curY_ + i][tts->curX_ + j] = tts->tetrad_[i][j];
	}
}

//'Game::isEnded()' returns true if piles of tetrads reach the top. 
//If first top row is filled with any tetrad already, game should be ended cause no more tetrad can fall down
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

//Returns boolean when a completed row found
//Any completed row is immediately removed by 'this->removeCompletedRows()'
bool Game::foundCompletedRows() {
	int sum = 0;
	bool flag = true;

	for (int i = F_HEIGHT - 1; i >= 0 && flag == true; i--) {
		for (int j = 0; j < F_WIDTH; j++)
			sum += field_[i][j];

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
//------------------
//should be enforced 
void Game::removeCompletedRows(int row) {
	if (row == 0)
		for (int j = 0; j < F_WIDTH; j++)
			field_[row][j] = 0;
	else {
		for (int i = row; i > 0; i--)
			for (int j = 0; j < F_WIDTH; j++) {
				field_[i][j] = field_[i - 1][j];
				field_[i - 1][j] = 0;
				if (i < F_HEIGHT - 1 && field_[i + 1][j] == 0 && field_[i][j] == 9) {
					bool isEmpty = true;
					int k;
					for (k = i + 1; k < F_HEIGHT - 1 && isEmpty; k++) {
						if (field_[k][j] == 0) k++;
						else isEmpty = false;
					}
					field_[k][j] = field_[i][j];
					field_[i][j] = 0;
				} 
			}
	}
}

//Scores Calculation : weigth(10, 30, 60, 100) * level * number of completed rows
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

	scores_ += scores;
	scoringRows_ = 0;
}

//'increaseLevel()' increases games's level based on the scores piled up so far as below
void Game::increaseLevel() {
	if (scores_ >= 2500)
		level_ = 5;
	else if (scores_ >= 1500)
		level_ = 4;
	else if (scores_ >= 1000)
		level_ = 3;
	else if (scores_ >= 50)
		level_ = 2;
	else if (scores_ >= 0)
		level_ = 1;
}

//'clearField()' clears game field for new game
void Game::clearField() {
	for (int i = 0; i < F_HEIGHT; i++)
		for (int j = 0; j < F_WIDTH; j++)
			field_[i][j] = 0;
}

int Game::getLines() {
	return lines_;
}

int Game::getScores() {
	return scores_;
}

int Game::getLevels() {
	return level_;
}
