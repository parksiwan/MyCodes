//
//Header file : Tetrad.h
//Purpose     : Declaration of Tetrad class and array data holding tetrads shape and position
//Features    : Creates, moves and terminates a tetrad within the game field
//
#ifndef TETRADS_H
#define TETRADS_H

#include <iostream>
#include "SDL.h"

//type of direction that a tetrad can take. 'DDOWN' is for 'drop down'
enum MOVING_DIRECTION { DOWN = 1, LEFT = 2, RIGHT = 3, DDOWN = 4 };

// Type       : Square = 0, I = 1, L = 2, L-mirr = 3, N = 4, N-mirr = 5, T = 6
// Rotation   : clockwise (0->1->2->3) / anti-clockwise(0->3->2->1)
// HORIZONTAL : horizontal size of tetrads array
// VERTICAL   : vertical size of tetrads array
// When a tetrad moves, the whole 5x5 array moves together
const short TYPE = 7;
const short ROTATION = 4;
const short HORIZONTAL = 5;
const short VERTICAL = 5;

//4 dimensional array holding all possible types of shapes for all possible types of tetrads
//array positions making tetrad shapes have 1, otherwise 0
const short tetrads[TYPE][ROTATION][HORIZONTAL][VERTICAL] =
{
	// Square block
	{
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 0, 0, 0 }
		}
	},
	// I block
	{
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 1, 1, 1 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 1, 1, 1, 1, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		}
	},
	// L block
	{
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 1, 1, 0 },
			{ 0, 1, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 1, 1, 1, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		}
	},
	// L-mirrored block
	{
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 0, 0, 0 },
			{ 0, 1, 1, 1, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 1, 1, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 0, 0, 0 }
		}
	},
	// N block
	{
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 0, 1, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		}
	},
	// N-mirrored block
	{
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 0, 0, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		}
	},
	// T block
	{
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 1, 1, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 1, 1, 1, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		}
	}
};

//starting row of 5x5 tetrad which starts to be displayed at the top field.
const short startingRow[TYPE][ROTATION][1] =
{
	// Square block
	{
		{ 3 },{ 3 },{ 3 },{ 3 }
	},
	// I block
	{
		{ 2 },{ 4 },{ 2 },{ 3 }
	},
	// L block
	{
		{ 3 },{ 3 },{ 3 },{ 2 }
	},
	// L-mirrored block
	{
		{ 3 },{ 2 },{ 3 },{ 3 }
	},
	// N block
	{
		{ 3 },{ 3 },{ 3 },{ 2 }
	},
	// N-mirrored block
	{
		{ 3 },{ 3 },{ 3 },{ 2 }
	},
	// T block
	{
		{ 3 },{ 3 },{ 3 },{ 2 }
	}
};

//Most outer row or column of each tetrad in 5x5 array. 
//It includes down, left, right and up side of each tetrad
const short edgeLine[TYPE][ROTATION][4] =
{
	// Square block
	{
		{ 3, 2, 3, 2 },{ 3, 2, 3, 2 },{ 3, 2, 3, 2 },{ 3, 2, 3, 2 }
	},
	// I block
	{
		{ 2, 1, 4, 2 },{ 4, 2, 2, 1 },{ 2, 0, 3, 2 },{ 3, 2, 2, 0 }
	},
	// L block
	{
		{ 3, 2, 3, 1 },{ 3, 1, 3, 2 },{ 3, 1, 2, 1 },{ 2, 1, 3, 1 }
	},
	// L-mirrored block
	{
		{ 3, 1, 2, 1 },{ 2, 1, 3, 1 },{ 3, 2, 3, 1 },{ 3, 1, 3, 2 }
	},
	// N block
	{
		{ 3, 2, 3, 1 },{ 3, 1, 3, 2 },{ 3, 1, 2, 1 },{ 2, 1, 3, 1 }
	},
	// N-mirrored block
	{
		{ 3, 2, 3, 1 },{ 3, 1, 3, 2 },{ 3, 1, 2, 1 },{ 2, 1, 3, 1 }
	},
	// T block
	{
		{ 3, 2, 3, 1 },{ 3, 1, 3, 2 },{ 3, 1, 2, 1 },{ 2, 1, 3, 1 }
	}
};

//curX_, curY_                              : current coordination values of top-left corner of 5x5 array
//direction_                                : direction where a tetrad moves 1:down, 2:left, 3:right
//type_                                     : type of tetrads
//rotation_                                 : 4 different rotation
//downEdge_, leftEdge_, rightEdge_, upEdge_ : current outer points of each face of a tatrad 
//tetrad_[HORIZONTAL][VERTICAL]             : 5x5 array holding a shape of a tetrad 
//ended_                                    : flag indicating expiration of a tetrad 
class Tetrads {
	//Game class can accesse and change variables in Tetrads class
	friend class Game;
public:
	Tetrads(int type, int rotation);
	
	void pollEvents(SDL_Event& event);
	void movedownTedrads();
	void updateTedrads();
	bool isEnded();

private:
	int curX_, curY_;
	int direction_ = 0;         //1:down, 2:left, 3:right
	int type_, rotation_;       //type_ : type of tetrads, rotation_ : value of 4 different rotation
	int downEdge_, leftEdge_, rightEdge_, upEdge_;
	short tetrad_[HORIZONTAL][VERTICAL] = { { 0 } };
	bool ended_ = false;
};

#endif
