//
//Header file : Board.h
//Purpose     : Declaration of Board class
//Features    : This class is involved in displaying all the entities on the window screen
//              This class inherits from Window class
//
#ifndef BOARD_H
#define BOARD_H

#include "Window.h"
#include "Game.h"
#include <string>

//SB_HEIGHT   : height of sub board
//SB_WIDTH    : width of sub board
//TETRAD_TYPE : number of types for tetrads
//pieceImage  : image file name used to make tetrads
const short SB_HEIGHT = 5;
const short SB_WIDTH = 5;
const short TETRAD_TYPE = 7;
const std::string pieceImage = "tpiece.png";

//w_             : width of an entity to be drawn
//h_             : height of an entity to be drawn;
//x_, y_         : coordinition of top-left position of the entity
//r_, g_, b_, a_ : color information of the entity
//label_         : pointer to SDL_Surface struct
//texture_       : pointer to SDL_Texture struct
class Board : public Window {
public:
	Board(const Window& window, int w, int h, int x, int y, int r, int g, int b, int a);             //Normal rectangle shape
	Board(const Window& window, int w, int h, int x, int y, char* label);                            //Labels
	Board(const Window& window, int w, int h, int x, int y);                                         //Displayed number values
	Board(const Window& window, int w, int h, int x, int y, const std::string& imagePath);           //Next Tetrad
	Board(const Window& window, int w, int h, int x, int y, const std::string& imagePath, Game* g);  //Game field
	~Board();

	void draw();
	void draw(short tt[][SB_WIDTH]);
	void draw(Game* g);
	void display(int values);

private:
	int w_, h_;
	int x_, y_;
	int r_, g_, b_, a_;
	SDL_Surface* label_ = nullptr;
	SDL_Texture* texture_ = nullptr;
};

#endif
