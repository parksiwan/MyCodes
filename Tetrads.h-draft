#ifndef TETRADS_H
#define TETRADS_H

#include <iostream>

const short TYPE = 7;
const short ROTATION = 4;
const short HORIZONTAL = 5;
const short VERTICAL = 5;

class Tetrads 
{
public:
	Tetrads(int x, int y, int type, int rotation);
	~Tetrads();

	void pollEvents(SDL_Event& event);
	void moveDown();
	void rotateDown();

private:
	int curX_, curY_;
	int type_, rotation_;       //type_ : type of tetrads, rotation_ : value of 4 different rotation
	short tetrad_[HORIZONTAL][VERTICAL] = { { 0 } };

};

#endif
