#ifndef GAME_H
#define GAME_H

const short FIELD_H = 5;
const short FIELD_V = 5;

class Game
{
public:
	Game(short** tetrad, short x, short y, short type);
	~Game();
	void checkBoundary();

private:
	short field_[FIELD_H][FIELD_V] = { { 0 } };
};

#endif
