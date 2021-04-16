#include <Game.hpp>

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() : mWindow(sf::VideoMode(640, 480), "Pong", sf::Style::Close | sf::Style::Titlebar)
{
}

Game::~Game()
{
}

// Main game loop

void Game::run()
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
}

void Game::render()
{
    mWindow.clear();
    mWindow.setView(mWindow.getDefaultView());

    mWindow.display();
}

// Backend

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    switch (key)
    {
    case sf::Keyboard::Escape:
        mWindow.close();
        break;

    default:
        break;
    }
}