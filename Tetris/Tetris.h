#pragma once
#include <vector>
#include "Globals.h"

/// <summary>
/// This class handles the falling Tetris.
/// </summary>
class Tetris
{
	unsigned char rotation;
	unsigned char color;
	std::vector<Position> blocks;

public:
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="iShape">Number of a color taken from color vector in main.cpp.</param>
	/// <param name="matrix">The matrix used for generating the game box.</param>
	Tetris(unsigned char iColor, const std::vector<std::vector<unsigned char>>& matrix);
	/// <summary>
	/// Get the color of the Tetris.
	/// </summary>
	/// <returns>Returns the value of the color parameter.</returns>
	unsigned char getColor();
	/// <summary>
	/// Get the position of the blocks that builds the Tetris. 
	/// </summary>
	/// <returns>Returns a vector of positions for each block that builds the Tetris.</returns>
	std::vector<Position> getBlocks();
	/// <summary>
	/// Makes the Tetris fall faster.
	/// </summary>
	/// <param name="matrix">The matrix used for generating the game box.</param>
	/// <returns>Returns true if the block can go down an extra step.</returns>
	bool down(const std::vector<std::vector<unsigned char>>& matrix);
	/// <summary>
	/// Creates the next block at starting position.
	/// </summary>
	/// <param name="nextShape">The positions for the building blocks of the next Tetris.</param>
	/// <param name="iMatrix">The matrix used for generating the game box.</param>
	/// <returns>Returns false if there is a Tetris at the starting point.</returns>
	bool reset(std::vector<Position> nextShape, const std::vector<std::vector<unsigned char>>& iMatrix);
	/// <summary>
	/// Drops the Tetris to the bottom.
	/// </summary>
	/// <param name="iMatrix">The matrix used for generating the game box.</param>
	void drop(const std::vector<std::vector<unsigned char>>& iMatrix);
	/// <summary>
	/// Makes the Tetris go left.
	/// </summary>
	/// <param name="iMatrix">The matrix used for generating the game box.</param>
	void left(const std::vector<std::vector<unsigned char>>& iMatrix);
	/// <summary>
	/// Makes the Tetris go right.
	/// </summary>
	/// <param name="iMatrix">The matrix used for generating the game box.</param>
	void right(const std::vector<std::vector<unsigned char>>& iMatrix);
	/// <summary>
	/// Rotates the tetris counter-clockwise.
	/// </summary>
	/// <param name="iMatrix">The matrix used for generating the game box.</param>
	void rotate(const std::vector<std::vector<unsigned char>>& iMatrix);
	/// <summary>
	/// Puts the Tetris in the matrix.
	/// </summary>
	/// <param name="iMatrix">The matrix used for generating the game box.</param>
	void updateMatrix(std::vector<std::vector<unsigned char>>& iMatrix);
	/// <summary>
	/// Displays where the Tetris is currently falling to.
	/// </summary>
	/// <param name="iMatrix">The matrix used for generating the game box.</param>
	/// <returns>Returns a vector of positions that is used to generate the endpoint of the Tetris.</returns>
	std::vector<Position> holoEnd(const std::vector<std::vector<unsigned char>>& iMatrix);
	/// <summary>
	/// Generates the Tetris.
	/// </summary>
	/// <param name="iColor">Number of a color taken from color vector in main.cpp</param>
	/// <param name="x">X position where the Tetris should be generated.</param>
	/// <param name="y">Y position where the Tetris should be generated.</param>
	/// <returns>Returns a vector with the positions for the building blocks of the next Tetris. </returns>
	std::vector<Position> generate(unsigned char iColor, char x, char y);
	
};

