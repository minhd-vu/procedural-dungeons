#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "TileMap.hpp"
#include "Player.hpp"

class Game
{
public:
    Game();
    void Run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    int* generateLevel(sf::Vector2u size);

    sf::RenderWindow mWindow;
    sf::View view;
    TileMap map;
    static const sf::Time TimePerFrame;
    Player player;
};

#endif //GAME_H