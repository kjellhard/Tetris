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
	std::vector<Position> curr = blocks;
	int xMax, xMin, yMax, yMin;
	xMax = -(COLUMNS * 2);
	xMin = COLUMNS * 2;
	yMax = -(ROWS * 2);
	yMin = ROWS * 2;

	for (Position& p : curr)
	{
		if (p.x > xMax)
			xMax = p.x;
		if (p.x < xMin)
			xMin = p.x;
		if (p.y > yMax)
			yMax = p.y;
		if (p.y < yMin)
			yMin = p.y;
	}

	int xMean = ((xMax + xMin) / 2);
	int yMean = ((yMax + yMin) / 2);

	std::cout << "x/y mean: " << xMean << ", " << yMean << '\n';

	int shiftX = 0;
	int shiftY = 0;

	if (clockwise) {

		for (Position& p : curr)
		{
			std::cout << "Old X/Y: " << p.x << ", " << p.y << '\n';
			//std::cout << "Mean X/Y: " << xMean << ", " << yMean << '\n';
			int prevY = p.y;
			if (p.x >= xMean)
			{
				p.y = yMean + p.x - xMean;

				if (prevY >= yMean)
					p.x = xMean - prevY + yMean;
				else
					p.x = xMean + yMean - prevY;
			}

			else
			{
				p.y = yMean - xMean + p.x;

				if (prevY >= yMean)
					p.x = xMean - prevY + yMean;
				else if (prevY < yMean)
					p.x = xMean + yMean - prevY;
			}

			//std::cout << "New X/Y: " << p.x << ", " << p.y << '\n';

			if ((xMax - xMin) >= (yMax - yMin))
				p.x++;
			if (p.x == COLUMNS)
				shiftX++;

			if (p.x > COLUMNS - 1 && shiftX < (p.x - (COLUMNS - 1)))
				shiftX = p.x - (COLUMNS - 1);
			if (p.x < 0 && shiftX >(p.x))
				shiftX = p.x;

			if (p.y > yMin && shiftY < (p.y - yMin))
				shiftY = p.y - yMin;
			if (p.y < 0 && shiftY < (0 - p.y))
				shiftY = p.y;
		}
	}
	else
	{
		for (Position& p : curr)
		{
			//std::cout << "Old X/Y: " << p.x << ", " << p.y << '\n';
			//std::cout << "Mean X/Y: " << xMean << ", " << yMean << '\n';
			int prevY = p.y;
			if (p.x >= xMean)
			{
				p.y = yMean - p.x + xMean;

				if (prevY >= yMean)
					p.x = xMean + prevY - yMean;
				else
					p.x = xMean - yMean + prevY;
			}

			else
			{
				p.y = yMean + xMean - p.x;

				if (prevY >= yMean)
					p.x = xMean + prevY - yMean;
				else if (prevY < yMean)
					p.x = xMean - yMean + prevY;
			}

			//std::cout << "New X/Y: " << p.x << ", " << p.y << '\n';

			if (p.x > COLUMNS - 1 && shiftX < (p.x - (COLUMNS - 1)))
				shiftX = p.x - (COLUMNS - 1);
			else if (p.x < 0 && shiftX > (p.x))
				shiftX = p.x;

			if (p.y > yMin && shiftY < (p.y - yMin))
				shiftY = p.y - yMin;
			if (p.y < 0 && shiftY < (0 - p.y))
				shiftY = p.y;

		}
	}

	if (shiftX != 0)
	{
		if (shiftY != 0)
		{
			for (Position& p : curr)
			{
				p.x -= shiftX;
				p.y += 2 - shiftY;
				
			}
		}
		else
		{
			for (Position& p : curr)
			{
				p.x -= shiftX;

			}
		}
	}
	else if (shiftY != 0)
	{
		for (Position& p : curr)
		{
			p.y += 2 - shiftY;
		}
	}

	for (Position& p : curr)
	{
		if (iMatrix[p.x][p.y] != 0)
			return;
	}

	blocks = curr;
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
