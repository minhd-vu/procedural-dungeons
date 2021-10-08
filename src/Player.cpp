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
    speed = 2.f;
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

    bool collision_x = false;
    bool collision_y = false;

    int i = sprite.getPosition().x / map.getTileSize().x;
    int j = sprite.getPosition().y / map.getTileSize().y;

    std::vector<sf::Vector2u> neighbors;
    neighbors.push_back(sf::Vector2u(i - 1, j));
    neighbors.push_back(sf::Vector2u(i + 1, j));
    neighbors.push_back(sf::Vector2u(i, j - 1));
    neighbors.push_back(sf::Vector2u(i, j + 1));
    neighbors.push_back(sf::Vector2u(i - 1, j - 1));
    neighbors.push_back(sf::Vector2u(i + 1, j - 1));
    neighbors.push_back(sf::Vector2u(i - 1, j + 1));
    neighbors.push_back(sf::Vector2u(i + 1, j + 1));

    sf::IntRect container(0, 0, map.getWidth(), map.getHeight());

    for (auto neighbor : neighbors)
    {
        int i = neighbor.x + neighbor.y * map.getWidth();
        if (container.contains(neighbor.x, neighbor.y) && map.getTiles()[i] == 0)
        {
            auto vertex = map.getVertices()[i * 4];
            sf::FloatRect tile(vertex.position, (sf::Vector2f)map.getTileSize());

            sf::FloatRect bounds_x = sprite.getGlobalBounds();
            sf::FloatRect bounds_y = sprite.getGlobalBounds();
            bounds_x.left += x;
            bounds_y.top += y;

            if (bounds_x.intersects(tile))
            {
                collision_x = true;
            }

            if (bounds_y.intersects(tile))
            {
                collision_y = true;
            }
        }
    }

    // std::cout << "x " << bounds.left << " y " << bounds.top << " " << collision << "\n";
    if (!collision_x)
    {
        sprite.move(x, 0);
    }

    if (!collision_y)
    {
        sprite.move(0, y);
    }
}