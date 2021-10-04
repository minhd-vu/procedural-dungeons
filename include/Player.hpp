#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	DIRECTION_SIZE
};

class Player
{
public:
	Player()
	{
	}

	void load(const std::string &filename, sf::Vector2f size)
	{
		if (!this->texture.loadFromFile(filename))
		{
			// error...
			std::cout << filename << "\n";
		}

		sprite = sf::Sprite(texture);
		float scale_x = size.x / texture.getSize().x;
		float scale_y = size.y / texture.getSize().y;
		sprite.setScale(sf::Vector2f(scale_x, scale_y));
	}

	~Player()
	{
	}

	void update()
	{
		float x = 0.f, y = 0.f;

		if (movementFlags[UP])
		{
			y -= speed;
		}
		if (movementFlags[DOWN])
		{
			y += speed;
		}
		if (movementFlags[LEFT])
		{
			x -= speed;
		}
		if (movementFlags[RIGHT])
		{
			x += speed;
		}

		sprite.move(x, y);
	}

	sf::Sprite &getSprite()
	{
		return sprite;
	}

	sf::Vector2f getCenter()
	{
		float x = sprite.getPosition().x + sprite.getGlobalBounds().width / 2.f;
		float y = sprite.getPosition().y + sprite.getGlobalBounds().height / 2.f;
		return sf::Vector2f(x, y);
	}

	bool *getMovementFlags()
	{
		return movementFlags;
	}

private:
	float speed = 1.f;
	bool movementFlags[DIRECTION_SIZE] = {false};
	sf::Texture texture;
	sf::Sprite sprite;
};

#endif