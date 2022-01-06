#include <random>
#include <vector>
#include "Globals.h"
#include "Tetris.h"
#include <iostream>

Tetris::Tetris(unsigned char iColor, const std::vector<std::vector<unsigned char>>& matrix) :
	rotation(0), color(iColor), blocks(generate(iColor, COLUMNS / 2, 1))
{

}

unsigned char Tetris::getColor()
{
	return color;
}

std::vector<Position> Tetris::getBlocks()
{
	return blocks;
}

bool Tetris::down(const std::vector<std::vector<unsigned char>>& iMatrix)
{
	for (Position& p : blocks)
	{
		if (p.y + 1 == ROWS)
			return false;
		if (iMatrix[p.x][p.y + +1] > 0)
			return false;
	}

	for (Position& p : blocks)
	{
		p.y++;
	}
	return true;
}

bool Tetris::reset(std::vector<Position> nextShape, const std::vector<std::vector<unsigned char>>& iMatrix)
{
	rotation = 0;

	blocks = nextShape;

	for (Position& p : blocks)
	{
		if (iMatrix[p.x][p.y] > 0)
			return false;
	}
	
	return true;
}

void Tetris::drop(const std::vector<std::vector<unsigned char>>& iMatrix)
{
	
	blocks = holoEnd(iMatrix);
}

void Tetris::left(const std::vector<std::vector<unsigned char>>& iMatrix)
{
	for (Position& p : blocks)
	{
		if (p.x - 1 < 0)
			return;

		if (p.y < 0)
			continue;
		else if (iMatrix[p.x - 1][p.y] > 0)
			return;
	}

	for (Position& p : blocks)
		p.x--;
}

void Tetris::right(const std::vector<std::vector<unsigned char>>& iMatrix)
{
	for (Position& p : blocks)
	{
		if (p.x + 1 == COLUMNS)
			return;

		if (p.y < 0)
			continue;
		else if (iMatrix[p.x + 1][p.y] > 0)
			return;
	}

	for (Position& p : blocks)
		p.x++;
}

void Tetris::rotate(bool clockwise, const std::vector<std::vector<unsigned char>>& iMatrix)
{

}

void Tetris::updateMatrix(std::vector<std::vector<unsigned char>>& iMatrix)
{
	for (Position& p : blocks)
	{
		if (p.y < 0)
			continue;
		iMatrix[p.x][p.y] = 1 + color;
	}
}

std::vector<Position> Tetris::holoEnd(const std::vector<std::vector<unsigned char>>& iMatrix)
{
	bool dropDown = true;
	unsigned char moves = 0;
	std::vector<Position> endPos = blocks;

	while (dropDown)
	{
		moves++;
		for (Position& p : blocks)
		{
			if (moves + p.y == ROWS)
			{
				dropDown = false;
				break;
			}

			if (p.y + moves < 0)
				continue;
			else if (iMatrix[p.x][p.y + moves] > 0)
			{
				dropDown = false;
				break;
			}
		}
	}

	for (Position& p : endPos)
		p.y += moves - 1;
	
	return endPos;
}

std::vector<Position> Tetris::generate(unsigned char iColor, char x,  char y)
{

	color = iColor;
	std::vector<Position> output;

	output.push_back({x, y});

	std::random_device randomDevice;
	std::default_random_engine randomEngine(randomDevice());
	std::vector<Position> availablePos;
	std::vector<std::vector<int>> allPos(TETRIS_SIZE * 2 - 1, std::vector<int>(TETRIS_SIZE * 2 - 1, 0));

	int minY = 0;

	int x1 = TETRIS_SIZE - 1, y1 = TETRIS_SIZE - 1;

	allPos[x1][y1] = 1;

	for (unsigned char i = 1; i < TETRIS_SIZE; i++)
	{
		if (allPos[x1 + 1][y1] < 1)
		{
			availablePos.push_back({ x1 + 1, y1 });
			allPos[x1+1][y1] += 1;
		}
		if (allPos[x1 - 1][y1] < 1)
		{
			availablePos.push_back({ x1 - 1, y1 });
			allPos[x1-1][y1] += 1;
		}
		if (allPos[x1][y1 + 1] < 1)
		{
			availablePos.push_back({ x1 , y1 + 1 });
			allPos[x1][y1+1] += 1;

		}
		if (allPos[x1][y1 - 1] < 1)
		{
			availablePos.push_back({ x1 , y1 - 1});
			allPos[x1][y1-1] += 1;
		}

		/*auto it = availablePos.begin();
		while (it != std::end(availablePos));
		{
			for (Position& p : output)
			{
				std::cout << static_cast<int>(p.x) <<" "<< static_cast<int>(p.y)<<"..."<< static_cast<int>((*it).x)<< static_cast<int>((*it).y) << "<- some x, y \n";
				if (*it == p)
				{
					availablePos.erase(it);
				}
			}
			it++;
		}*/


		std::uniform_int_distribution<size_t> dist(0, availablePos.size() - 1);
		size_t nextPos = dist(randomEngine);
		x1 = availablePos[nextPos].x;
		y1 = availablePos[nextPos].y;

		//std::cout << "x: " << static_cast<int>(x1) << " y: " << static_cast<int>(y1) << '\n';
		//std::cout << "Actual x: " << static_cast<int>(availablePos[nextPos].x + x - TETRIS_SIZE) << " Actual y: " << static_cast<int>(availablePos[nextPos].y + y - TETRIS_SIZE) << '\n';
		availablePos[nextPos].x += x - TETRIS_SIZE + 1;
		availablePos[nextPos].y += y - TETRIS_SIZE + 1;
		if (availablePos[nextPos].y < minY)
			minY = availablePos[nextPos].y;
		output.push_back(availablePos[nextPos]);

		availablePos.erase(availablePos.begin() + nextPos);
	}

	if (minY < 0)
	{
		for (Position& p : output)
			p.y -= minY;
	}
	blocks = output;
	return output;
}
