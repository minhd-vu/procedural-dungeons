#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "TileMap.hpp"
#include "Player.hpp"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <array>
#include <random>
#include <chrono>
#include <stack>
#include <fstream>

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

    sf::RenderWindow mWindow;
    sf::View view;
    TileMap map;
    static const sf::Time TimePerFrame;
    Player player;
};

#endif //GAME_H