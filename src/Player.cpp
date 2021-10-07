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
    speed = size.x;
    sprite.setScale(sf::Vector2f(scale_x, scale_y));
}

void Player::update(TileMap &map)
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

    int i = (sprite.getPosition().x + x) / map.getTileSize().x;
    int j = (sprite.getPosition().y + y) / map.getTileSize().y;

    if (map.getTiles()[i + j * map.getWidth()])
    {
        sprite.move(x, y);
    }
}