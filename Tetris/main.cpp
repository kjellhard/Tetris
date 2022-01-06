#include <SFML/Graphics.hpp>
#include <chrono>
#include "Globals.h"
#include "Tetris.h"


int main()
{
	unsigned int lag = 0;
	unsigned int clearedLines = 0;

	bool gameOver = 0;
	bool fastDrop = 0;
	bool rotate = 0;
	
	unsigned char clearTimer = 0;
	unsigned char fallSpeed = 32;
	unsigned char fallTime = 0;
	unsigned char moveTime = 0;
	unsigned char nextShape;
	unsigned char dropTime = 0;

	std::vector<sf::Color> cell_colors = {
		sf::Color(36, 36, 85),
		sf::Color(0, 219, 255),
		sf::Color(0, 36, 255),
		sf::Color(255, 146, 0),
		sf::Color(255, 219, 0),
		sf::Color(0, 219, 0),
		sf::Color(146, 0, 255),
		sf::Color(219, 0, 0),
		sf::Color(73, 73, 85)
	};

	std::vector<bool> clear_lines(ROWS, 0);

	std::vector<std::vector<unsigned char>> matrix(COLUMNS, std::vector<unsigned char>(ROWS));

	sf::RenderWindow window(sf::VideoMode(BLOCK_SIZE * COLUMNS * SCREEN_RESIZE, BLOCK_SIZE * ROWS * SCREEN_RESIZE), "Tetris", sf::Style::Close);
	sf::Event event;

	//window.setView(sf::View(sf::FloatRect(0, 0, 2 * BLOCK_SIZE * COLUMNS, BLOCK_SIZE * ROWS)));

	std::chrono::time_point<std::chrono::steady_clock> prevTime = std::chrono::steady_clock::now();

	while (window.isOpen())
	{
		unsigned diffTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - prevTime).count();
		lag += diffTime;
		prevTime += std::chrono::microseconds(diffTime);

		while (FRAME_DURATION <= lag)
		{
			lag -= FRAME_DURATION;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
					case sf::Event::Closed:
					{
						window.close();
						break;
					}
					case sf::Event::KeyReleased:
					{
						switch (event.key.code)
						{
							case sf::Keyboard::C:
							case sf::Keyboard::Z:
							{
								rotate = 0;
								break;
							}
						}
					}
				}
			}
		}
		
	}

	return 0;
}