#ifndef TETRADS_H
#define TETRADS_H

#include <iostream>

const short TYPE = 7;
const short ROTATION = 4;
const short HORIZONTAL = 5;
const short VERTICAL = 5;

class Tetrads 
{
	friend class Game;
public:
	Tetrads(int type, int rotation);
	~Tetrads();

	void pollEvents(SDL_Event& event);
	void movedownTedrads();
	void updateTedrads();
	inline bool isEnded() { return ended_; }
private:
	int curX_, curY_;
	int type_, rotation_;       //type_ : type of tetrads, rotation_ : value of 4 different rotation
	short tetrad_[HORIZONTAL][VERTICAL] = { { 0 } };
	bool ended_ = false;

};

#endif
