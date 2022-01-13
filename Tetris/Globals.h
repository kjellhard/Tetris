#pragma once 
/// <summary>
/// Resizes the screen.
/// </summary>
constexpr unsigned char SCREEN_RESIZE = 3;
/// <summary>
/// Vertical move speed.
/// </summary>
constexpr unsigned char MOVE_SPEED = 4;
/// <summary>
/// Horisontal move speed.
/// </summary>
constexpr unsigned char SOFT_DROP_SPEED = 4;
/// <summary>
/// Duration of clear effect.
/// </summary>
constexpr unsigned char CLEAR_EFFECT_DURATION = 8;
/// <summary>
/// Number of lines to clear before increasing fall speed.
/// </summary>
constexpr unsigned char LINES_TO_INCREASE_SPEED = 2;

/// <summary>
/// Size of the SFML blocks.
/// </summary>
extern unsigned char BLOCK_SIZE;
/// <summary>
/// Size of the Tetris.
/// </summary>
extern unsigned TETRIS_SIZE;
/// <summary>
/// Number of columns.
/// </summary>
extern unsigned char COLUMNS;
/// <summary>
/// Number of rows.
/// </summary>
extern unsigned char ROWS;
/// <summary>
/// Frame duration.
/// </summary>
constexpr unsigned short FRAME_DURATION = 16667;

/// <summary>
/// Struct for X and Y positions.
/// </summary>
struct Position
{
	/// <summary>
	/// X position.
	/// </summary>
	int x;
	/// <summary>
	/// Y position.
	/// </summary>
	int y;
	
	/// <summary>
	/// Constructor using an instance of this struct.
	/// </summary>
	/// <param name="p">Instance of this struct</param>
	Position(const Position& p) : x(p.x), y(p.y) {};

	/// <summary>
	/// Constructor using X and Y positions.
	/// </summary>
	Position(int iX, int iY) : x(iX), y(iY) {};

	/// <summary>
	/// Checks if both X and Y positions are the same.
	/// </summary>
	bool operator==(Position& p)
	{
		if ((x == p.x) && (y == p.y))
			return true;
		else
			return false;
	}
};