constexpr unsigned char COLUMNS = 10;
constexpr unsigned char ROWS = 20;
constexpr unsigned char SCREEN_RESIZE = 4;

unsigned char BLOCK_SIZE = 8;
unsigned TETRIS_SIZE = 4;

constexpr unsigned short FRAME_DURATION = 16667;

struct Position
{
	char x;
	char y;
	
	Position(){};

	Position(char iX, char iY) : x(iX), y(iY) {};


	bool operator==(Position p)
	{
		if ((x == p.x) && (y = p.y))
			return true;
		else
			return false;
	}
};