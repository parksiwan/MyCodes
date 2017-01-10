#ifndef BOARD_H
#define BOARD_H

#include "Window.h"
#include "Game.h"
#include <string>

const short SB_HEIGHT = 5;
const short SB_WIDTH = 5;
const short TETRAD_TYPE = 7;
const short RGB = 3;
const std::string colorImage[TETRAD_TYPE + 1] =
{
	// Square block = light blue
	"blue_piece.png",
	// I block = yellow
	"green_piece.png",
	// L block = viloet
	"red_piece.png",
	// L-mirrored block = green
	"yellow_piece.png",
	// N block = grey + blank
	"brown_piece.png",
	// N-mirrored block = grey
	"ruby_piece.png",
	// T block = red
	"darkgreen_piece.png",
	//background = white
	"white_piece.png"
};

class Board : public Window 
{
public:
	Board(const Window& window, int w, int h, int x, int y, int r, int g, int b, int a);   //Normal rectangle shape
	Board(const Window& window, int w, int h, int x, int y, int option);                   //Labels
	Board(const Window& window, int w, int h, int x, int y, const std::string& imagePath); //Next Tetrad
	Board(const Window& window, int w, int h, int x, int y, const std::string& imagePath, Game* g);  //Game field
	~Board();

	void draw();
	void draw(short tt[][SB_WIDTH]);
	void draw(Game* g);

private:
	int w_, h_;
	int x_, y_;
	int r_, g_, b_, a_;
	int option_ = 0;
	SDL_Surface* label_ = nullptr;
	SDL_Texture* texture_ = nullptr;
};

#endif
