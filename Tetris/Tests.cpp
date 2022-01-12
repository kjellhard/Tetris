#include "Tetris.h"
#include <vector>
#include "Globals.h"

int main()
{
	TETRIS_SIZE = 4;

	ROWS = TETRIS_SIZE * 5;
	COLUMNS = ROWS / 2;

	std::vector<std::vector<unsigned char>> matrix(COLUMNS, std::vector<unsigned char>(ROWS));

	Tetris tetris(3, matrix);

	return 0;
}