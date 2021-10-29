#include "Game.hpp"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 8.f);

Game::Game() : mWindow(sf::VideoMode(800, 800), "Procedural Dungeons")
{
    // define the level with an array of tile indices
    player.load("images/birdsprite.png", sf::Vector2f(32.f, 32.f));
    view = sf::View(sf::FloatRect(0.f, 0.f, 256.f, 256.f));
    reload();
}

// generate a new map
void Game::reload()
{
    system("python3 procedural_dungeon.py level.txt");

    // create the tilemap from the level definition
    if (!map.load("images/tilemap.png", sf::Vector2u(32, 32), "level.txt", 50, 50))
        return;

    // set the player position
    player.setPosition(map.getStart());

    // a* pathfinding
    std::queue<Node> path;
    map.getPath(map.getStart(), map.getKey(), path);
    map.getPath(map.getKey(), map.getGoal(), path);
    player.setPath(path);
}

// the main game loop
void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        // frame rate limit logic is done here
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        // draw everything
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;

    while (mWindow.pollEvent(event))
    {
        // not used but keep in case they need to be used in the future
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            break;
        case sf::Event::KeyReleased:
            break;
        case sf::Event::Closed:
            mWindow.close();
            break;
        default:
            break;
        }
    }
}

void Game::update(sf::Time deltaTime)
{
    // TODO: Update your objects here
    if (player.update(map.getTileSize()))
        reload();

    if (player.getPostion() == map.getKey())
    {
        map.removeKey();
    }
}

void Game::render()
{
    mWindow.clear();
    view.setCenter(player.getCenter());
    mWindow.setView(view);

    // TODO: Draw your objects here
    mWindow.draw(map);
    mWindow.draw(player.getSprite());

    mWindow.display();
}
