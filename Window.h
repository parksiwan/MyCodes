#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <SDL.h>

enum INPUT_MESSAGE { NOTHING = 0, START = 1, EXIT = 2, RESTART = 3 };
const int W_WIDTH = 800;
const int W_HEIGHT = 600;

class Window {
public:
	Window(const std::string& title, int width, int height);
	~Window();
	
	void pollEvents(SDL_Event& event);
	void clear() const;
	inline bool isClosed() const { return closed_; }
	int getInputMessage();

private:
	std::string title_;
	int width_ = W_WIDTH;
	int height_ = W_HEIGHT;
	bool closed_ = false;
	int inputMessage_ = 0;
	SDL_Window* window_ = nullptr;

protected:
	SDL_Renderer* renderer_ = nullptr;
};

#endif
