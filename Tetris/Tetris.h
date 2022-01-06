#pragma once

class Tetris
{
	unsigned char rotation;
	unsigned char color;
	std::vector<Position> blocks;

public:
	Tetris(unsigned char iShape, const std::vector<std::vector<unsigned char>>& matrix);
	unsigned char getColor();
	std::vector<Position> getBlocks();
	bool down(const std::vector<std::vector<unsigned char>>& matrix);
	bool reset(std::vector<Position> nextShape, const std::vector<std::vector<unsigned char>>& iMatrix);
	void drop(const std::vector<std::vector<unsigned char>>& iMatrix);
	void left(const std::vector<std::vector<unsigned char>>& iMatrix);
	void right(const std::vector<std::vector<unsigned char>>& iMatrix);
	void rotate(bool clockwise, const std::vector<std::vector<unsigned char>>& iMatrix);
	void updateMatrix(std::vector<std::vector<unsigned char>>& iMatrix);

	std::vector<Position> holoEnd(const std::vector<std::vector<unsigned char>>& iMatrix);

	std::vector<Position> generate(unsigned char iColor, char x, char y);
	
};

