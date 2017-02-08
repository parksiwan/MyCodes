//
//Source file : Board.cpp
//Purpose     : Definition of member functions of Board class 
//Features    : Creates different type of boards to display on the window
//
#include "Board.h"
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

//Constructor for normal rectangle shape entity
//@param w_             : width of an entity to be drawn
//@param h_             : height of an entity to be drawn;
//@param x_, y_         : coordinition of top-left position of the entity
//@param r_, g_, b_, a_ : color information of the entity
Board::Board(const Window& window, int w, int h, int x, int y, int r, int g, int b, int a) : Window(window) {
	w_ = w;
	h_ = h;
	x_ = x;
	y_ = y;
	r_ = r;
	g_ = g;
	b_ = b;
	a_ = a;
}

//Constructor for label entity
//@param w_         : width of an entity to be drawn
//@param h_         : height of an entity to be drawn;
//@param x_, y_     : coordinition of top-left position of the entity
//@param label      : char pointer for text label
Board::Board(const Window& window, int w, int h, int x, int y, char* label) : Window(window) {
	w_ = w;
	h_ = h;
	x_ = x;
	y_ = y;
	
	TTF_Font* font = nullptr;   //opens font style and sets size
	SDL_Color color = { 0, 0, 0 };

	try {
		font = TTF_OpenFont("C:\\Windows\\Fonts\\Arial.ttf", 20);
		if (font == nullptr)
			throw 1;
	} catch (int e) {
		std::cerr << "Font init fail---" << std::endl;
	}

	try {
		label_ = TTF_RenderText_Solid(font, label, color);
		if (!label_)
			throw 1;
	} catch (int e) {
		std::cerr << "Failed to create surface" << std::endl;
	}

	try {
		texture_ = SDL_CreateTextureFromSurface(renderer_, label_);
		if (!texture_)
			throw 1;
	} catch (int e) {
		std::cerr << "Failed to create texture" << std::endl;
	}

	SDL_QueryTexture(texture_, NULL, NULL, &w_, &h_);
}

//Constructor for numbers to be displayed inside window
//@param w_         : width of an entity to be drawn
//@param h_         : height of an entity to be drawn;
//@param x_, y_     : coordinition of top-left position of the enti
Board::Board(const Window& window, int w, int h, int x, int y) : Window(window) {
	w_ = w;
	h_ = h;
	x_ = x;
	y_ = y;
}

//Constructor for image comprising the next tetrad
//@param w_         : width of an entity to be drawn
//@param h_         : height of an entity to be drawn;
//@param x_, y_     : coordinition of top-left position of the enti
//@param imagePath  : string of image file used to make tetrads shape
Board::Board(const Window& window, int w, int h, int x, int y, const std::string& imagePath) : Window(window) {
	w_ = w;
	h_ = h;
	x_ = x;
	y_ = y;
	SDL_Surface* surface;

	try {
		surface = IMG_Load(imagePath.c_str());
		if (!surface)
			throw 1;
	} catch (int e) {
		std::cerr << "Failed to create surface" << std::endl;
	}
		
	try {
		texture_ = SDL_CreateTextureFromSurface(renderer_, surface);
		if (!texture_)
			throw 1;
	} catch (int e) {
		std::cerr << "Failed to create texture" << std::endl;
	}

	SDL_FreeSurface(surface);
}

//Constructor for game field
//@param w_         : width of an entity to be drawn
//@param h_         : height of an entity to be drawn;
//@param x_, y_     : coordinition of top-left position of the enti
//@param imagePath  : string of image file used to make game field
//@param g          : pointer to Game class
Board::Board(const Window& window, int w, int h, int x, int y, const std::string& imagePath, Game* g) : Window(window) {
	w_ = w;
	h_ = h;
	x_ = x;
	y_ = y;
	SDL_Surface* surface;

	try {
		surface = IMG_Load(imagePath.c_str());
		if (!surface)
			throw 1;
	} catch (int e) {
		std::cerr << "Failed to create surface" << std::endl;
	}

	try {
		texture_ = SDL_CreateTextureFromSurface(renderer_, surface);
		if (!texture_)
			throw 1;
	} catch (int e) {
		std::cerr << "Failed to create texture" << std::endl;
	}

	SDL_FreeSurface(surface);
}

//Destructor of Board class. destroy texture and frees surface
Board::~Board() {
	SDL_DestroyTexture(texture_);
	SDL_FreeSurface(label_);
}

//draws normal rectangle shapes
void Board::draw() {
	SDL_Rect board_rect = { x_, y_, w_, h_ };

	if (texture_)
		SDL_RenderCopy(renderer_, texture_, nullptr, &board_rect);
	else {
		SDL_SetRenderDrawColor(renderer_, r_, g_, b_, a_);
		SDL_RenderFillRect(renderer_, &board_rect);
	}
}

//draws a tetrad shapes
void Board::draw(short tt[][SB_WIDTH]) {
	if (texture_) {
		for (int i = 0; i < SB_HEIGHT; i++) {
			for (int j = 0; j < SB_WIDTH; j++) {
				if (tt[i][j] != 0) {
					//each "ttRect" consists of a Tetrad
					SDL_Rect ttRect = { x_ + j * 20, y_ + i * 20, w_, h_ };
					SDL_RenderCopy(renderer_, texture_, nullptr, &ttRect);
				}
			}
		}
	} else {
		SDL_SetRenderDrawColor(renderer_, r_, g_, b_, a_);
	}
}

//draws the game field
void Board::draw(Game* g) {
	if (texture_) {
		for (int i = 0; i < F_HEIGHT; i++) {
			for (int j = 0; j < F_WIDTH; j++) {
				if (g->field_[i][j] != 0) {
					//each "ttRect" consists of a Tetrad
					SDL_Rect ttRect = { x_ + j * 20, y_ + i * 20, w_, h_ };
					SDL_RenderCopy(renderer_, texture_, nullptr, &ttRect);
				}
			}
		}
	} else {
		SDL_SetRenderDrawColor(renderer_, r_, g_, b_, a_);
	}
}

//display number values including scores, lines and level
//@param value    : number values to be displayed on the window screen
void Board::display(int values) {
	TTF_Font* font = nullptr;   //opens font style and sets size
	SDL_Color color = { 0, 0, 0 };
	std::string str_values = std::to_string(values);
	const char* cstr = str_values.c_str();

	try {
		font = TTF_OpenFont("C:\\Windows\\Fonts\\Arial.ttf", 20);
		if (font == nullptr)
			throw 1;
	} catch (int e) {
		std::cerr << "Font init fail---" << std::endl;
	}

	try {
		label_ = TTF_RenderText_Solid(font, cstr, color);
		if (!label_)
			throw 1;
	} catch (int e) {
		std::cerr << "Failed to create surface" << std::endl;
	}

	try {
		texture_ = SDL_CreateTextureFromSurface(renderer_, label_);
		if (!texture_)
			throw 1;
	} catch (int e) {
		std::cerr << "Failed to create texture" << std::endl;
	}

	SDL_QueryTexture(texture_, NULL, NULL, &w_, &h_);

	SDL_Rect board_rect = { x_, y_, w_, h_ };

	if (texture_)
		SDL_RenderCopy(renderer_, texture_, nullptr, &board_rect);
	else {
		SDL_SetRenderDrawColor(renderer_, r_, g_, b_, a_);
		SDL_RenderFillRect(renderer_, &board_rect);
	}
}
