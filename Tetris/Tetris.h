#include <vector>
#include "Globals.h"

class Tetris
{
	unsigned char rotation;
	unsigned char shape;
	std::vector<Position> blocks;

public:
	Tetris(unsigned char iShape, const std::vector<std::vector<unsigned char>>& matrix);
	bool fall(const std::vector<std::vector<unsigned char>>& matrix);
	bool reset(unsigned char iShape, const std::vector<std::vector<unsigned char>>& iMatrix);
	void down(const std::vector<std::vector<unsigned char>>& iMatrix);
	void left(const std::vector<std::vector<unsigned char>>& iMatrix);
	void right(const std::vector<std::vector<unsigned char>>& iMatrix);
	void rotate(const std::vector<std::vector<unsigned char>>& iMatrix);
	void updateMatrix(std::vector<std::vector<unsigned char>>& iMatrix);
};

