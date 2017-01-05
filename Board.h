#ifndef BOARD_H
#define BOARD_H

#include "Window.h"
#include <string>

class Board : public Window 
{
public:
	Board(const Window& window, int w, int h, int x, int y, int r, int g, int b, int a);
	Board(const Window& window, int w, int h, int x, int y, int option);
	Board(const Window& window, int w, int h, int x, int y, short** field);
	~Board();

	void draw();

private:
	int w_, h_;
	int x_, y_;
	int r_, g_, b_, a_;
	short option_ = 0;
	SDL_Surface* label_ = nullptr;
	SDL_Texture* texture_ = nullptr;
};

#endif
