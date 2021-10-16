#include "Player.hpp"

void Player::load(const std::string &filename, sf::Vector2f size)
{
    if (!this->texture.loadFromFile(filename))
    {
        // error...
        std::cout << filename << "\n";
    }

    sprite = sf::Sprite(texture);
    float scale_x = size.x / texture.getSize().x;
    float scale_y = size.y / texture.getSize().y;
    speed = 1;
    sprite.setScale(sf::Vector2f(scale_x, scale_y));
}

void Player::update(TileMap &map)
{
    int x = 0, y = 0;

    if (nodes.empty())
        return;

    movementFlags[nodes.front()] = true;
    std::cout << nodes.front() << "\n";

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

    movementFlags[nodes.front()] = false;
    nodes.pop();

    if (x && map.getTiles()[position.x + x + position.y * map.getWidth()])
    {
        position.x += x;
    }

    if (y && map.getTiles()[position.x + (position.y + y) * map.getWidth()])
    {
        position.y += y;
    }

    sprite.setPosition(position.x * map.getTileSize().x, position.y * map.getTileSize().y);
}