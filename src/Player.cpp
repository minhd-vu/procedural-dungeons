#include "Player.hpp"

void Player::load(const std::string &filename, sf::Vector2f size)
{
    if (!this->texture.loadFromFile(filename))
    {
        // error...
        std::cout << filename << "\n";
    }

    speed = 1;
    direction = UP;
    sprite = sf::Sprite(texture, sf::IntRect(0, direction * 32, 32, 32));

    // scaling if the sprite is too large

    // float scale_x = size.x / texture.getSize().x;
    // float scale_y = size.y / texture.getSize().y;
    // sprite.setScale(sf::Vector2f(scale_x, scale_y));
}

/*
 * Returns true if the player ai has no where else to go,
 * otherwise false if there are still moves remaining.
 */
bool Player::update(sf::Vector2u tileSize)
{
    if (!path.empty())
    {
        // set the player direction based on where they were looking last
        sf::Vector2i diff = (sf::Vector2i)path.front().position - (sf::Vector2i)position;
        if (diff.x == 1)
            direction = RIGHT;
        else if (diff.x == -1)
            direction = LEFT;
        else if (diff.y == 1)
            direction = DOWN;
        else if (diff.y == -1)
            direction = UP;

        // set the position to the new postion
        position = path.front().position;
        path.pop();
    }
    else
    {
        return true;
    }

    // animation is done here
    sprite.setTextureRect(sf::IntRect((sprite.getTextureRect().left + 32) % 96, direction * 32, 32, 32));
    sprite.setPosition(position.x * tileSize.x, position.y * tileSize.y);

    return false;
}