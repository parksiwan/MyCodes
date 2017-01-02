#include "Board.h"
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>

Board::Board(const Window& window, int w, int h, int x, int y, int r, int g, int b, int a) : Window(window)
{
	w_ = w;
	h_ = h;
	x_ = x;
	y_ = y;
	r_ = r;
	g_ = g;
	b_ = b;
	a_ = a;
}

Board::Board(const Window& window, int w, int h, int x, int y, int option) : Window(window)
{
	w_ = w;
	h_ = h;
	x_ = x;
	y_ = y;
	option_ = option;

	TTF_Font* font = nullptr;   //opens font style and sets size
	SDL_Color color = { 0, 0, 0 };

	switch (option_) 
	{
		case 1:
			font = TTF_OpenFont("C:\\Windows\\Fonts\\Arial.ttf", 35);
			label_ = TTF_RenderText_Solid(font, "AIT TETRIS", color);
			break;
		case 2:
			font = TTF_OpenFont("C:\\Windows\\Fonts\\Arial.ttf", 20);
			label_ = TTF_RenderText_Solid(font, "LEVEL", color);
			break;
		case 3:
			font = TTF_OpenFont("C:\\Windows\\Fonts\\Arial.ttf", 20);
			label_ = TTF_RenderText_Solid(font, "SCORE", color);
			break;
		case 4:
			font = TTF_OpenFont("C:\\Windows\\Fonts\\Arial.ttf", 20);
			label_ = TTF_RenderText_Solid(font, "LINES", color);
			break;
		case 5:
			font = TTF_OpenFont("C:\\Windows\\Fonts\\Arial.ttf", 20);
			label_ = TTF_RenderText_Solid(font, "NEXT", color);
			break;
		case 6:
			font = TTF_OpenFont("C:\\Windows\\Fonts\\Arial.ttf", 20);
			label_ = TTF_RenderText_Solid(font, "PLAY GAME ?", color);
			break;
		case 7:
			font = TTF_OpenFont("C:\\Windows\\Fonts\\Arial.ttf", 20);
			label_ = TTF_RenderText_Solid(font, "GAME ENDS", color);
			break;
		case 8:
			font = TTF_OpenFont("C:\\Windows\\Fonts\\Arial.ttf", 20);
			label_ = TTF_RenderText_Solid(font, "START", color);
			break;
		case 9:
			font = TTF_OpenFont("C:\\Windows\\Fonts\\Arial.ttf", 20);
			label_ = TTF_RenderText_Solid(font, "RESTART", color);
			break;
		case 10:
			font = TTF_OpenFont("C:\\Windows\\Fonts\\Arial.ttf", 20);
			label_ = TTF_RenderText_Solid(font, "EXIT", color);
			break;
	}

	if (font == nullptr) 
		std::cerr << "Font init fail" << std::endl;

	if (!label_)
		std::cerr << "Failed to create surface" << std::endl;
	
	texture_ = SDL_CreateTextureFromSurface(renderer_, label_);
	
	if (!texture_)
		std::cerr << "Failed to create texture" << std::endl;
	
	SDL_QueryTexture(texture_, NULL, NULL, &w_, &h_);
}
	
Board::~Board() 
{
	SDL_DestroyTexture(texture_);
	SDL_FreeSurface(label_);
}

void Board::draw() 
{
	SDL_Rect board_rect = { x_, y_, w_, h_ };

	if (texture_)
		SDL_RenderCopy(renderer_, texture_, nullptr, &board_rect);
	else 
	{
		SDL_SetRenderDrawColor(renderer_, r_, g_, b_, a_);
		SDL_RenderFillRect(renderer_, &board_rect);
	}
}
