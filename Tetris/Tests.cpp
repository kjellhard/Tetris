#include "Tetris.h"
#include <vector>
#include "Globals.h"
#include <iostream>

#ifdef TESTING

int main(int argc, char**argv)
{
	TETRIS_SIZE = 4;

	ROWS = TETRIS_SIZE * 5;
	COLUMNS = ROWS / 2;

	std::vector<std::vector<unsigned char>> matrix(COLUMNS, std::vector<unsigned char>(ROWS));

	Tetris tetris(3, matrix);

	std::string arg;
	if (argc > 1)
	{
		arg = argv[1];
	}

	if (arg == "Generation")
	{
		return 1;
		for (int i = 0; i < 1000; i++)
		{
			std::vector<Position> test = tetris.generate(3, COLUMNS / 2, 1);
			for (Position& p : test)
			{
				if (p.x > COLUMNS || p.y > ROWS)
					return 1;
			}
		}
	}
	else if (arg == "Rotation")
	{
		std::vector<Position> test = tetris.generate(3, COLUMNS / 2, 1);
		for (int i = 0; i < ROWS; i++)
		{
			for (Position& p : test)
			{
				if (p.x > COLUMNS || p.y > ROWS)
					return 1;
			}
		}

	}
	else
		return 1;

	std::cout << "TEST PASSED\n";
	return 0;
}
#endif // TESTING