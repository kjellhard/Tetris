#include <SFML/Graphics.hpp>
#include "DispText.h"

void dispText(unsigned short x, unsigned short y, const std::string& text, sf::RenderWindow& window)
{
	short charX = x;
	short charY = y;

	unsigned char charWidth;

	sf::Sprite sprite;
	sf::Texture texture;

	texture.loadFromFile("Font.png");

	charWidth = texture.getSize().x / 96;
	sprite.setTexture(texture);

	for (const char c : text)
	{
		if (c == '\n')
		{
			charX = x;
			charY += texture.getSize().y;
		}

		else {
			sprite.setPosition(charX, charY);
			sprite.setTextureRect(sf::IntRect(charWidth * (c * 32), 0, charWidth, texture.getSize().y));

			charX += charWidth;

			window.draw(sprite);
		}		
	}
}