#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <queue>
#include "TileMap.hpp"

enum Direction
{
    DOWN,
    LEFT,
    RIGHT,
    UP,
    DIRECTION_SIZE
};

class Player
{
public:
    Player()
    {
    }

    void load(const std::string &filename, sf::Vector2f size);

    ~Player()
    {
    }

    bool update(sf::Vector2u tileSize);

    sf::Sprite &getSprite()
    {
        return sprite;
    }

    sf::Vector2f getCenter() const
    {
        float x = sprite.getPosition().x + sprite.getGlobalBounds().width / 2.f;
        float y = sprite.getPosition().y + sprite.getGlobalBounds().height / 2.f;
        return sf::Vector2f(x, y);
    }

    Direction getDirection() const
    {
        return direction;
    }

    sf::Vector2u getPostion() const
    {
        return position;
    }

    void setPosition(unsigned int x, unsigned int y)
    {
        position.x = x;
        position.y = y;
    }

    void setPosition(sf::Vector2u position)
    {
        this->position = position;
    }

    void setPath(std::queue<Node> path)
    {
        this->path = path;
    }

private:
    unsigned int speed;
    Direction direction;
    std::queue<Node> path;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2u position;
};

#endif