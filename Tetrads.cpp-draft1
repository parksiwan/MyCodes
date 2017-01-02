#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "res_path.h"
#include "cleanup.h"

const short TYPE = 7;
const short ROTATION = 4;
const short HORIZONTAL = 5;
const short VERTICAL = 5;

// Type : Square = 0, I = 1, L = 2, L-mirr = 3, N = 4, N-mirr = 5, T = 6
// Rotation : clockwise (0->1->2->3)
char pieces[TYPE][ROTATION][HORIZONTAL][VERTICAL] =
{
	// Square block
	{
		{
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '2', '1', '0' },
			{ '0', '0', '1', '1', '0' },
			{ '0', '0', '0', '0', '0' }
		},
		{
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '2', '1', '0' },
			{ '0', '0', '1', '1', '0' },
			{ '0', '0', '0', '0', '0' }
		},
		{
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '2', '1', '0' },
			{ '0', '0', '1', '1', '0' },
			{ '0', '0', '0', '0', '0' }
		},
		{
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '2', '1', '0' },
			{ '0', '0', '1', '1', '0' },
			{ '0', '0', '0', '0', '0' }
		}
	},
	// I block
	{
		{
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '0', '0', '0' },
			{ '0', '1', '2', '1', '1' },
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '0', '0', '0' }
		},
		{
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '1', '0', '0' },
			{ '0', '0', '2', '0', '0' },
			{ '0', '0', '1', '0', '0' },
			{ '0', '0', '1', '0', '0' }
		},
		{
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '0', '0', '0' },
			{ '1', '1', '2', '1', '0' },
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '0', '0', '0' }
		},
		{
			{ '0', '0', '1', '0', '0' },
			{ '0', '0', '1', '0', '0' },
			{ '0', '0', '2', '0', '0' },
			{ '0', '0', '1', '0', '0' },
			{ '0', '0', '0', '0', '0' }
		}
	},
	// L block
	{
		{
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '1', '0', '0' },
			{ '0', '0', '2', '0', '0' },
			{ '0', '0', '1', '1', '0' },
			{ '0', '0', '0', '0', '0' }
		},
		{
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '0', '0', '0' },
			{ '0', '1', '2', '1', '0' },
			{ '0', '1', '0', '0', '0' },
			{ '0', '0', '0', '0', '0' }
		},
		{
			{ '0', '0', '0', '0', '0' },
			{ '0', '1', '1', '0', '0' },
			{ '0', '0', '2', '0', '0' },
			{ '0', '0', '1', '0', '0' },
			{ '0', '0', '0', '0', '0' }
		},
		{
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '0', '1', '0' },
			{ '0', '1', '2', '1', '0' },
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '0', '0', '0' }
		}
	},
	// L-mirrored block
	{
		{
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '1', '0', '0' },
			{ '0', '0', '2', '0', '0' },
			{ '0', '1', '1', '0', '0' },
			{ '0', '0', '0', '0', '0' }
		},
		{
			{ '0', '0', '0', '0', '0' },
			{ '0', '1', '0', '0', '0' },
			{ '0', '1', '2', '1', '0' },
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '0', '0', '0' }
		},
		{
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '1', '1', '0' },
			{ '0', '0', '2', '0', '0' },
			{ '0', '0', '1', '0', '0' },
			{ '0', '0', '0', '0', '0' }
		},
		{
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '0', '0', '0' },
			{ '0', '1', '2', '1', '0' },
			{ '0', '0', '0', '1', '0' },
			{ '0', '0', '0', '0', '0' }
		}
	},
	// N block
	{
		{
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '0', '1', '0' },
			{ '0', '0', '2', '1', '0' },
			{ '0', '0', '1', '0', '0' },
			{ '0', '0', '0', '0', '0' }
		},
		{
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '0', '0', '0' },
			{ '0', '1', '2', '0', '0' },
			{ '0', '0', '1', '1', '0' },
			{ '0', '0', '0', '0', '0' }
		},
		{
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '1', '0', '0' },
			{ '0', '1', '2', '0', '0' },
			{ '0', '1', '0', '0', '0' },
			{ '0', '0', '0', '0', '0' }
		},
		{
			{ '0', '0', '0', '0', '0' },
			{ '0', '1', '1', '0', '0' },
			{ '0', '0', '2', '1', '0' },
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '0', '0', '0' }
		}
	},
	// N-mirrored block
	{
		{
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '1', '0', '0' },
			{ '0', '0', '2', '1', '0' },
			{ '0', '0', '0', '1', '0' },
			{ '0', '0', '0', '0', '0' }
		},
		{
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '2', '1', '0' },
			{ '0', '1', '1', '0', '0' },
			{ '0', '0', '0', '0', '0' }
		},
		{
			{ '0', '0', '0', '0', '0' },
			{ '0', '1', '0', '0', '0' },
			{ '0', '1', '2', '0', '0' },
			{ '0', '0', '1', '0', '0' },
			{ '0', '0', '0', '0', '0' }
		},
		{
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '1', '1', '0' },
			{ '0', '1', '2', '0', '0' },
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '0', '0', '0' }
		}
	},
	// T block
	{
		{
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '1', '0', '0' },
			{ '0', '0', '2', '1', '0' },
			{ '0', '0', '1', '0', '0' },
			{ '0', '0', '0', '0', '0' }
		},
		{
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '0', '0', '0' },
			{ '0', '1', '2', '1', '0' },
			{ '0', '0', '1', '0', '0' },
			{ '0', '0', '0', '0', '0' }
		},
		{
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '1', '0', '0' },
			{ '0', '1', '2', '0', '0' },
			{ '0', '0', '1', '0', '0' },
			{ '0', '0', '0', '0', '0' }
		},
		{
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '1', '0', '0' },
			{ '0', '1', '2', '1', '0' },
			{ '0', '0', '0', '0', '0' },
			{ '0', '0', '0', '0', '0' }
		}
	}
};

typedef struct clips 
{
	SDL_Rect clip[25];
	short color[25];
}tetrads;

//Screen attributes
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

/*
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message too
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(std::ostream& os, const std::string& msg) 
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}
/*
* Loads an image into a texture on the rendering device
* @param file The image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren) 
{
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr) 
		logSDLError(std::cout, "LoadTexture");
	
	return texture;
}
/*
* Draw an SDL_Texture to an SDL_Renderer at some destination rect
* taking a clip of the texture if desired
* @param tex The source texture we want to draw
* @param rend The renderer we want to draw too
* @param dst The destination rectangle to render the texture too
* @param clip The sub-section of the texture to draw (clipping rect)
*		default of nullptr draws the entire texture
*/
void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, SDL_Rect dst, SDL_Rect* clip = nullptr) 
{
	SDL_RenderCopy(ren, tex, clip, &dst);
}
/*
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height and taking a clip of the texture if desired
* If a clip is passed, the clip's width and height will be used instead of the texture's
* @param tex The source texture we want to draw
* @param rend The renderer we want to draw too
* @param x The x coordinate to draw too
* @param y The y coordinate to draw too
* @param clip The sub-section of the texture to draw (clipping rect)
*		default of nullptr draws the entire texture
*/
void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, SDL_Rect* clip = nullptr) 
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	if (clip != nullptr) 
	{
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else 
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	
	renderTexture(tex, ren, dst, clip);
}

int main(int argc, char** argv) 
{
	tetrads tetrad;

	//Start up SDL and make sure it went ok
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}

	//Setup our window and renderer
	SDL_Window* window = SDL_CreateWindow("Lesson 5", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) 
	{
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) 
	{
		logSDLError(std::cout, "CreateRenderer");
		cleanup(window);
		SDL_Quit();
		return 1;
	}
	//const std::string resPath = getResourcePath("C:\\Users\\siwan\\Documents\\Visual Studio 2015\\Projects\\SDL_TEST\\SDL_TEST\\");
	SDL_Texture* back_image = loadTexture("white_piece.png", renderer);
	SDL_Texture* image = loadTexture("green_piece.png", renderer);
	//const std::string resPath = getResourcePath("Lesson5");
	//SDL_Texture *image = loadTexture(resPath + "image.png", renderer);
	if (image == nullptr || back_image == nullptr) 
	{
		cleanup(image, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	//iW and iH are the clip width and height
	//We'll be drawing only clips so get a center position for the w/h of a clip
	int iW = 20, iH = 20;
	int x = SCREEN_WIDTH / 2 - iW / 2;
	int y = SCREEN_HEIGHT / 2 - iH / 2;
	int count = 0;
	//Setup the clips for our image
	
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (pieces[2][0][i][j] == '1' || pieces[2][0][i][j] == '2')
			{
				tetrad.color[count] = 2;
			}
			else
			{
				tetrad.color[count] = 0;
			}
			tetrad.clip[count] = { x + j * iW, y + i * iH, iW, iH };
			count++;
		}
	}
	
	//Since our clips our uniform in size we can generate a list of their
	//positions using some math (the specifics of this are covered in the lesson)
	/*for (int i = 0; i < 4; ++i) {
		clips[i].x = i / 2 * iW;
		clips[i].y = i % 2 * iH;
		clips[i].w = iW;
		clips[i].h = iH;
	}*/
	//Specify a default clip to start with
	int useClip = 0;

	SDL_Event e;
	bool quit = false;
	while (!quit) {
		//Event Polling
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			//Use number input to select which clip should be drawn
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_LEFT:
					for (int i = 0; i < 25; i++)
					{
						tetrad.clip[i].x -= 20;
					}
					break;
				case SDLK_RIGHT:
					for (int i = 0; i < 25; i++)
					{
						tetrad.clip[i].x += 20;
					}
					break;
				case SDLK_DOWN:
					for (int i = 0; i < 25; i++)
					{
						tetrad.clip[i].y += 10;
					}
					break;
				case SDLK_ESCAPE:
					quit = true;
					break;
				default:
					break;
				}
			}
		}
		for (int i = 0; i < 25; i++)
		{
			tetrad.clip[i].y += 10;
		}
		
		//Rendering
		SDL_RenderClear(renderer);
		//Draw the image
		for (int i = 0; i < 25; i++)
		{
			if (tetrad.color[i] == 0)
				SDL_RenderCopy(renderer, back_image, NULL, &tetrad.clip[i]);
			else
				SDL_RenderCopy(renderer, image, NULL, &tetrad.clip[i]);
		}
			
		
		//Update the screen
		SDL_RenderPresent(renderer);
		SDL_Delay(150);
	}
	//Clean up
	cleanup(image, renderer, window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}
