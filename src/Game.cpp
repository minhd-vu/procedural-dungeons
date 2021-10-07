#include "Game.hpp"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

void Game::loadLevel(std::string filename)
{
    std::ifstream in(filename, std::ios::in);

    int number;

    while (in >> number)
    {
        level.push_back(number);
    }

    in.close();
}

Game::Game() : mWindow(sf::VideoMode(800, 800), "Procedural Dungeons")
{
    // define the level with an array of tile indices
    loadLevel("level.txt");
    player.load("images/birb.png", sf::Vector2f(32.f, 32.f));
    view = sf::View(sf::FloatRect(0.f, 0.f, 1600.f, 1600.f));

    // create the tilemap from the level definition
    if (!map.load("images/tileset.png", sf::Vector2u(32, 32), level, 50, 50))
        return;
}

void Game::Run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;

    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
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
    player.update();
}

void Game::render()
{
    mWindow.clear();
    // view.setCenter(player.getCenter());
    mWindow.setView(view);

    // TODO: Draw your objects here
    mWindow.draw(map);
    mWindow.draw(player.getSprite());

    mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::W || key == sf::Keyboard::Up)
    {
        player.getMovementFlags()[UP] = isPressed;
    }
    if (key == sf::Keyboard::S || key == sf::Keyboard::Down)
    {
        player.getMovementFlags()[DOWN] = isPressed;
    }
    if (key == sf::Keyboard::A || key == sf::Keyboard::Left)
    {
        player.getMovementFlags()[LEFT] = isPressed;
    }
    if (key == sf::Keyboard::D || key == sf::Keyboard::Right)
    {
        player.getMovementFlags()[RIGHT] = isPressed;
    }
}