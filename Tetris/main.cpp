/*!
* Projekt i Programmeringsmetodik
* \author Isak Kjellhard
* \version 1.0
* \date 2022-01-13
* Dynamic Tetris where the number of blocks to create the Tetris can be changed.
*/

#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>
#include "Globals.h"
#include "Tetris.h"
#include "DispText.h"
#include <iostream>
#include <Windows.h>

#pragma execution_character_set( "utf-8" )

#ifndef TESTING


/// <summary>
/// Starts the game.
/// </summary>
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
	unsigned char dropTime = 0;

	std::vector<Position> nextShape;
	unsigned char nextColor;

	std::vector<sf::Color> colors = {
		sf::Color(128, 128, 128),
		sf::Color(0, 255, 255),
		sf::Color(0, 0, 255),
		sf::Color(255, 127, 0),
		sf::Color(255, 255, 0),
		sf::Color(0, 255, 0),
		sf::Color(128, 0, 128),
		sf::Color(255, 0, 0),
		sf::Color(73, 73, 85)
	};

	//SetConsoleOutputCP(CP_UTF8);
	//std::cout << "ANGE ANTAL BLOCK FÖR ATT BYGGA TETRIS: \n";
	//std::cin >> TETRIS_SIZE;

	TETRIS_SIZE = 4;

	ROWS = TETRIS_SIZE * 5;
	COLUMNS = ROWS / 2;

	std::vector<bool> linesToClear(ROWS, 0);

	std::vector<std::vector<unsigned char>> matrix(COLUMNS, std::vector<unsigned char>(ROWS));


	sf::RenderWindow window(sf::VideoMode(2* BLOCK_SIZE * COLUMNS * SCREEN_RESIZE, BLOCK_SIZE * ROWS * SCREEN_RESIZE), "Tetris", sf::Style::Close);
	sf::Event event;

	window.setView(sf::View(sf::FloatRect(0, 0, 2 *  BLOCK_SIZE * COLUMNS, BLOCK_SIZE * ROWS)));

	window.requestFocus();

	std::random_device randomDevice;
	std::default_random_engine randomEngine(randomDevice());
	std::uniform_int_distribution<unsigned short> colorDist(0, 6);
	nextColor = static_cast<unsigned char>(colorDist(randomEngine));

	Tetris tetris(nextColor, matrix);

	nextShape = tetris.generate(nextColor, COLUMNS / 2, 1);


	std::chrono::time_point<std::chrono::steady_clock> prevTime = std::chrono::steady_clock::now();


	//Runs while the window is open.
	while (window.isOpen())
	{
		//Difference between time frames.
		unsigned diffTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - prevTime).count();
		//Add difference to lag.
		lag += diffTime;
		prevTime += std::chrono::microseconds(diffTime);

		//While the lag is more than the maximum allowed frame duration.
		while (FRAME_DURATION <= lag)
		{
			lag -= FRAME_DURATION;

			//Check the different events.
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
							case sf::Keyboard::Down:
							{
								dropTime = 0;
								break;
							}
							case sf::Keyboard::Left:
							case sf::Keyboard::Right:
							{
								moveTime = 0;
								break;
							}
							case sf::Keyboard::Space:
							{
								fastDrop = 0;
								break;
							}
						}
					}
				}
			}

			if (clearTimer == 0)
			{
				//Do stuff based on inputs and stuff.
				if (!gameOver)
				{
					if (!rotate)
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
						{
							rotate = 1;
							tetris.rotate(matrix);
							tetris.rotate(matrix);
							tetris.rotate(matrix);
						}
						else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
						{
							rotate = 1;
							tetris.rotate(matrix);
						}
					}

					if (moveTime == 0)
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
						{
							moveTime = 1;
							tetris.left(matrix);
						}
						else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
						{
							moveTime = 1;
							tetris.right(matrix);
						}
					}
					else
						moveTime = (moveTime + 1) % MOVE_SPEED;

					if (!fastDrop)
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
						{
							fastDrop = true;
							fallTime = fallSpeed;
							tetris.drop(matrix);
						}
					}
					if (dropTime == 0)
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
						{
							if (tetris.down(matrix))
							{
								fallTime = 0;
								dropTime = 1;
							}
						}
					}
					else
						dropTime = (dropTime + 1) % SOFT_DROP_SPEED;


					if (fallSpeed == fallTime)
					{
						//If the Tetris can't move down we have to do stuff before resetting timer.
						if (!tetris.down(matrix))
						{
							tetris.updateMatrix(matrix);

							for (unsigned char i = 0; i < ROWS; i++)
							{
								bool clear = true;
								for (unsigned char j = 0; j < COLUMNS; j++)
								{
									if (matrix[j][i] == 0)
									{
										clear = false;
										break;
									}
								}

								if (clear)
								{
									clearedLines++;
									clearTimer = CLEAR_EFFECT_DURATION;
									linesToClear[i] = 1;

									if (clearedLines % LINES_TO_INCREASE_SPEED == 0)
										fallSpeed = std::max<unsigned char>(SOFT_DROP_SPEED, fallSpeed - 2);
								}
							}

							if (clearTimer == 0)
							{
								gameOver = !tetris.reset(nextShape, matrix);
								if(gameOver)
									std::cout << "LOST OMEGALUL\n";

								nextShape = tetris.generate(nextColor, COLUMNS / 2, 1);
								nextColor = static_cast<unsigned char>(colorDist(randomEngine));
							}
						}
						fallTime = 0;
					}
					else
						fallTime++;
				}

				//Enter to reset when game is over.
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					gameOver = 0;
					fastDrop = 0;
					rotate = 0;
					clearedLines = 0;
					fallSpeed = 32;
					fallTime = 0;
					moveTime = 0;
					dropTime = 0;

					for (std::vector<unsigned char>& m : matrix)
					{
						std::fill(m.begin(), m.end(), 0);
					}
				}
			}

			//Clearing some rows if possible.
			else
			{
				clearTimer--;
				if (clearTimer == 0)
				{
					for (unsigned char i = 0; i < ROWS; i++)
					{
						if (linesToClear[i] == 1)
						{
							for (unsigned char j = 0; j < COLUMNS; j++)
							{
								matrix[j][i] = 0;

								for (unsigned char k = i; k > 0; k--)
								{
									matrix[j][k] = matrix[j][k - 1];
									matrix[j][k - 1] = 0;
								}
							}
						}
					}

					gameOver = !tetris.reset(nextShape, matrix);
					nextShape = tetris.generate(nextColor, COLUMNS / 2, 1);
					nextColor = static_cast<unsigned char>(colorDist(randomEngine));

					std::fill(linesToClear.begin(), linesToClear.end(), 0);
				}
			}

			//Displaying the game
			if (FRAME_DURATION > lag)
			{
				//Fancy stuff for the clear effect.
				unsigned char clearBlockSize = static_cast<unsigned char>(2 * round(.5f * BLOCK_SIZE * (clearTimer / static_cast<float>(CLEAR_EFFECT_DURATION))));

				sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE - 1, BLOCK_SIZE - 1));

				sf::RectangleShape previewBox(sf::Vector2f((TETRIS_SIZE * 2 - 1) * BLOCK_SIZE, (TETRIS_SIZE * 2 - 1) * BLOCK_SIZE) );
				previewBox.setFillColor(sf::Color(0, 0, 0));
				previewBox.setOutlineThickness(-1);
				previewBox.setPosition(BLOCK_SIZE * (COLUMNS + TETRIS_SIZE *.25), BLOCK_SIZE * 2);

				window.clear();

				//Display the matrix.
				for (unsigned char i = 0; i < COLUMNS; i++)
				{
					for (unsigned char j = 0; j < ROWS; j++)
					{
						if (!linesToClear[j])
						{
							block.setPosition(static_cast<float>(BLOCK_SIZE* i), static_cast<float>(BLOCK_SIZE* j));

							if (gameOver && matrix[i][j])
								block.setFillColor(colors[8]);
							else
								block.setFillColor(colors[matrix[i][j]]);

							window.draw(block);
						}
					}
				}

				block.setFillColor(colors[8]);

				if (!gameOver)
				{
					//Display the holo endpoint.
					for (Position& p : tetris.holoEnd(matrix))
					{
						block.setPosition(static_cast<float>(BLOCK_SIZE* p.x), static_cast<float>(BLOCK_SIZE* p.y));

						window.draw(block);
					}

					block.setFillColor(colors[1 + tetris.getColor()]);
				}

				//Display the Tetris.
				for (Position& p : tetris.getBlocks())
				{
					block.setPosition(static_cast<float>(BLOCK_SIZE* p.x), static_cast<float>(BLOCK_SIZE* p.y));

					window.draw(block);
				}

				//Display the clear effect.
				for (unsigned char i = 0; i < COLUMNS; i++)
				{
					for (unsigned char j = 0; j < ROWS; j++)
					{
						if (linesToClear[j])
						{
							block.setFillColor(colors[0]);
							block.setPosition(static_cast<float>(BLOCK_SIZE* i), static_cast<float>(BLOCK_SIZE* j));
							block.setSize(sf::Vector2f(BLOCK_SIZE - 1, BLOCK_SIZE - 1));

							window.draw(block);

							block.setFillColor(sf::Color(255, 255, 255));
							block.setPosition(floor(BLOCK_SIZE* (.5f + i) - .5f * clearBlockSize), floor(BLOCK_SIZE* (.5f + j) - .5f * clearBlockSize));
							block.setSize(sf::Vector2f(clearBlockSize, clearBlockSize));

							window.draw(block);
						}
					}
				}

				block.setFillColor(colors[1 + nextColor]);
				block.setSize(sf::Vector2f(BLOCK_SIZE - 1, BLOCK_SIZE - 1));

				window.draw(previewBox);

				//Display the next shape inside the preview window. 

				for (Position& p : nextShape)
				{
					block.setPosition((p.x + COLUMNS - 1) * BLOCK_SIZE, (TETRIS_SIZE + p.y) * BLOCK_SIZE);
					window.draw(block);
				}

				//Display the score and fall speed.
				float speed = 32.f / static_cast<float>(fallSpeed);
				std::string buffer(5, '\0');
				std::snprintf(&buffer.front(), buffer.size(), "%.2f", speed);
				dispText(static_cast<unsigned short>(BLOCK_SIZE* (COLUMNS)), static_cast<unsigned short>(.5 * BLOCK_SIZE * ROWS), "Score: " + std::to_string(clearedLines * ROWS) + "\nSpeed: " + buffer + 'x', window);

				window.display();
			}
		}
		
	}

	return 0;
}
#endif // !TESTING
