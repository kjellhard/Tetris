#pragma once 
constexpr unsigned char SCREEN_RESIZE = 3;
constexpr unsigned char MOVE_SPEED = 4;
constexpr unsigned char SOFT_DROP_SPEED = 4;
constexpr unsigned char CLEAR_EFFECT_DURATION = 4;
constexpr unsigned char LINES_TO_INCREASE_SPEED = 2;

extern unsigned char BLOCK_SIZE;
extern unsigned TETRIS_SIZE;
extern unsigned char COLUMNS;
extern unsigned char ROWS;

constexpr unsigned short FRAME_DURATION = 16667;

struct Position
{
	int x;
	int y;
	
	Position(const Position& p) : x(p.x), y(p.y) {};

	Position(int iX, int iY) : x(iX), y(iY) {};


	bool operator==(Position& p)
	{
		if ((x == p.x) && (y == p.y))
			return true;
		else
			return false;
	}
};