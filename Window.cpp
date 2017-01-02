#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Window.h"


Window::Window(const std::string& title, int width, int height) 
{
    title_ = title;
	width_ = width;
	height_ = height;
    
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "Failed to initialize SDL" << std::endl;
		closed_ = true;
	}

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		std::cerr << "Failed to initialize SDL" << std::endl;
		closed_ = true;
	}

	if (TTF_Init() != 0)
	{
		std::cerr << "Failed to initialize TTF" << std::endl;
		closed_ = true;
	}

	window_ = SDL_CreateWindow(title_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_, height_, 0);
	if (window_ == nullptr)
	{
		std::cerr << "Failed to create window" << std::endl;
		closed_ = true;
	}

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (renderer_ == nullptr)
	{
		std::cerr << "Failed to create renderer." << std::endl;
		closed_ = true;
	}

	closed_ = false;
}

Window::~Window() 
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Window::pollEvents(SDL_Event& event) 
{
	switch (event.type) 
	{
		case SDL_QUIT:
			closed_ = true;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) 
			{
				case SDLK_ESCAPE:
				closed_ = true;
				break;
			}
		default:
			break;
	}
}

void Window::clear() const 
{
	SDL_RenderPresent(renderer_);       //updates the screen with any rendering performed so far
	SDL_SetRenderDrawColor(renderer_, 0, 0, 200, 255);  //sets the color used for drawing operation
	SDL_RenderClear(renderer_);   //clears rendering target
}
