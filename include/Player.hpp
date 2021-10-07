#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
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
        return movementFlags;
    }

private:
    float speed;
    bool movementFlags[DIRECTION_SIZE] = {false};
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif