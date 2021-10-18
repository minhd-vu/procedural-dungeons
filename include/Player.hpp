#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <queue>
#include "TileMap.hpp"

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

    void load(const std::string &filename, sf::Vector2f size);

    ~Player()
    {
    }

    void update(TileMap &map);

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
        return movement;
    }

    sf::Vector2u getPostion()
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
    bool movement[DIRECTION_SIZE] = {false};
    std::queue<Node> path;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2u position;
};

#endif