#include "Tetris.h"
#include "Globals.h"
#include <random>


Tetris::Tetris(unsigned char iShape, const std::vector<std::vector<unsigned char>>& matrix) :
	rotation(0), shape(iShape), blocks(generate(iShape, COLUMNS / 2, 1))
{

}

bool Tetris::fall(const std::vector<std::vector<unsigned char>>& iMatrix)
{
	return true;
}

bool Tetris::reset(unsigned char iShape, const std::vector<std::vector<unsigned char>>& iMatrix)
{
	return true;
}

void Tetris::down(const std::vector<std::vector<unsigned char>>& iMatrix)
{

}

void Tetris::left(const std::vector<std::vector<unsigned char>>& iMatrix)
{

}

void Tetris::right(const std::vector<std::vector<unsigned char>>& iMatrix)
{

}

void Tetris::rotate(const std::vector<std::vector<unsigned char>>& iMatrix)
{

}

void Tetris::updateMatrix(std::vector<std::vector<unsigned char>>& iMatrix)
{
	for (Position& p : blocks)
	{
		if (p.y < 0)
			continue;
		iMatrix[p.x][p.y] = 1 + shape;
	}
}

std::vector<Position> generate(unsigned char iShape,  char x,  char y)
{
	std::vector<Position> output;

	output.push_back({x, y});

	std::random_device randomDevice;
	std::default_random_engine randomEngine(randomDevice());
	

	for (int i = 1; i < TETRIS_SIZE; i++)
	{
		std::vector<Position> availablePos;
		availablePos.push_back({ x + 1, y });
		availablePos.push_back({ x - 1, y });
		availablePos.push_back({ x , y + 1 });
		availablePos.push_back({ x , y - 1});

		auto it = std::begin(availablePos);
		while (it != std::end(availablePos));
		{
			for (Position p2 : output)
			{
				if (*it == p2)
				{
					availablePos.erase(it);
					break;
				}
			}
			it++;
		}
		std::uniform_int_distribution<int> dist(0, availablePos.size() - 1);

		int nextPos = dist(randomEngine);

		output.push_back(availablePos[nextPos]);

	}
	return output;
}
