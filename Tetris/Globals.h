#pragma once
constexpr unsigned char COLUMNS = 10;
constexpr unsigned char ROWS = 20;
constexpr unsigned char SCREEN_RESIZE = 4;
constexpr unsigned char MOVE_SPEED = 4;
constexpr unsigned char SOFT_DROP_SPEED = 4;
constexpr unsigned char CLEAR_EFFECT_DURATION = 8;
constexpr unsigned char LINES_TO_INCREASE_SPEED = 4;

extern unsigned char BLOCK_SIZE;
extern unsigned TETRIS_SIZE;

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