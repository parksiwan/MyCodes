#ifndef WINDOW_H
#define WINDOW_H

#include <string.h>
#include <SDL.h>

class Window 
{
public:
	Window(const std::string& title, int width, int height);
	~Window();
	
	void pollEvents(SDL_Event& event);
	void clear() const;
	inline bool isClosed() const { return closed_; }

private:
	bool init();

private:
	std::string title_;
	int width_ = 800;
	int height_ = 600;

	bool closed_ = false;

	SDL_Window* window_ = nullptr;

protected:
	SDL_Renderer* renderer_ = nullptr;
};

#endif
