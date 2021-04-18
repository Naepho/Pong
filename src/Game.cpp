#include <Game.hpp>
#include <stdlib.h>

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() : mWindow(sf::VideoMode(640, 480), "Pong", sf::Style::Close | sf::Style::Titlebar),
               mPlayer(sf::Vector2f(20, 60)), mAI(sf::Vector2f(20, 60)), mBall(7.5f), mScore("minBold.otf", 32),
               mLose("minBold.otf", 48), mWin("minBold.otf", 48)
{
    mPlayer.setPosition(sf::Vector2f(10, mWindow.getSize().y / 2 - 60 / 2));
    mAI.setPosition(sf::Vector2f(mWindow.getSize().x - 10 - 20, mWindow.getSize().y / 2 - 60 / 2));
    mBall.setPosition(sf::Vector2f(mWindow.getSize().x / 2 - mBall.getSize(), mWindow.getSize().y / 2 - mBall.getSize()));
    mScore.setPosition(sf::Vector2f(mWindow.getSize().x / 2 - mScore.getLocalBounds().width / 2, 20));
    mLose.setPosition(sf::Vector2f(mWindow.getSize().x / 2 - mLose.getLocalBounds().width / 2, mWindow.getSize().y / 2 - mLose.getLocalBounds().height / 2));
    mWin.setPosition(sf::Vector2f(mWindow.getSize().x / 2 - mLose.getLocalBounds().width / 2, mWindow.getSize().y / 2 - mLose.getLocalBounds().height / 2));
    mIsMovingUp = false;
    mIsMovingDown = false;
    playerLose = false;
    playerWin = false;

    mLine[0] = sf::Vertex(sf::Vector2f(mWindow.getSize().x / 2, 0));
    mLine[1] = sf::Vertex(sf::Vector2f(mWindow.getSize().x / 2, mWindow.getSize().y));

    // algorithm for random ball velocity
    mBall.setVelocity(sf::Vector2f((rand() % 80 + 70) / 100.f, (rand() % 80 + 70) / 100.f));

    int randBallVelocity = rand() % 100 + 1;
    if (randBallVelocity >= 25 && randBallVelocity < 50)
    {
        mBall.setVelocity(mBall.getVelocity().x * -1.f, mBall.getVelocity().y);
    }
    else if (randBallVelocity >= 50 && randBallVelocity < 75)
    {
        mBall.setVelocity(mBall.getVelocity().x, mBall.getVelocity().y * -1.f);
    }
    else if (randBallVelocity >= 75)
    {
        mBall.setVelocity(mBall.getVelocity() * -1.f);
    }
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
    sf::Vector2f velocity(0.f, 0.f);
    if (mIsMovingUp)
    {
        velocity.y -= 1.f;
    }
    if (mIsMovingDown)
    {
        velocity.y += 1.f;
    }

    mPlayer.setVelocity(velocity);
    mPlayer.update(deltaTime);
    if (mPlayer.getPosition().y < 0)
    {
        mPlayer.setPosition(sf::Vector2f(mPlayer.getPosition().x, 0));
    }
    else if (mPlayer.getPosition().y + mPlayer.getSize().y > mWindow.getSize().y)
    {
        mPlayer.setPosition(sf::Vector2f(mPlayer.getPosition().x, mWindow.getSize().y - mPlayer.getSize().y));
    }

    mBall.update(deltaTime);
    if (mBall.getPosition().x < 0 || mBall.getPosition().x > mWindow.getSize().x - mBall.getSize() * 2)
    {
        mBall.setVelocity(mBall.getVelocity().x * -1.f, mBall.getVelocity().y);
    }
    if (mBall.getPosition().y < 0 || mBall.getPosition().y > mWindow.getSize().y - mBall.getSize() * 2)
    {
        mBall.setVelocity(mBall.getVelocity().x, mBall.getVelocity().y * -1.f);
    }

    mAI.update(deltaTime, sf::Vector2f(mBall.getPosition().x + mBall.getSize(), mBall.getPosition().y + mBall.getSize()), sf::Vector2f(mWindow.getSize().x, mWindow.getSize().y));
    if (mAI.getPosition().y < 0)
    {
        mAI.setPosition(sf::Vector2f(mAI.getPosition().x, 0));
    }
    else if (mAI.getPosition().y + mAI.getSize().y > mWindow.getSize().y)
    {
        mAI.setPosition(sf::Vector2f(mAI.getPosition().x, mWindow.getSize().y - mAI.getSize().y));
    }

    // ball bouncing on player and AI
    if (mBall.getGlobalBounds().intersects(mPlayer.getGlobalBounds()))
    {
        mScore.update(1);
        if (mBall.getGlobalBounds().contains(sf::Vector2f(mPlayer.getPosition().x + mPlayer.getSize().x / 2, mPlayer.getPosition().y)) ||
            mBall.getGlobalBounds().contains(sf::Vector2f(mPlayer.getPosition().x + mPlayer.getSize().x / 2, mPlayer.getPosition().y + mPlayer.getSize().y)) ||
            mBall.getGlobalBounds().contains(sf::Vector2f(mPlayer.getPosition().x + (mPlayer.getSize().x / 4) * 3, mPlayer.getPosition().y)) ||
            mBall.getGlobalBounds().contains(sf::Vector2f(mPlayer.getPosition().x + (mPlayer.getSize().x / 4) * 3, mPlayer.getPosition().y + mPlayer.getSize().y)) ||
            mBall.getGlobalBounds().contains(sf::Vector2f(mPlayer.getPosition().x + mPlayer.getSize().x, mPlayer.getPosition().y)) ||
            mBall.getGlobalBounds().contains(sf::Vector2f(mPlayer.getPosition().x + mPlayer.getSize().x, mPlayer.getPosition().y + mPlayer.getSize().y)) ||
            mBall.getGlobalBounds().contains(sf::Vector2f(mPlayer.getPosition().x, mPlayer.getPosition().y)) ||
            mBall.getGlobalBounds().contains(sf::Vector2f(mPlayer.getPosition().x, mPlayer.getPosition().y + mPlayer.getSize().y)))
        {
            mBall.setVelocity(mBall.getVelocity().x * -1.f, mBall.getVelocity().y * -1.f);
        }
        else
        {
            mBall.setVelocity(mBall.getVelocity().x * -1.f, mBall.getVelocity().y);
        }
    }

    if (mBall.getGlobalBounds().intersects(mAI.getGlobalBounds()))
    {
        if (mBall.getGlobalBounds().contains(sf::Vector2f(mAI.getPosition().x + mAI.getSize().x / 2, mAI.getPosition().y)) ||
            mBall.getGlobalBounds().contains(sf::Vector2f(mAI.getPosition().x + mAI.getSize().x / 2, mAI.getPosition().y + mAI.getSize().y)) ||
            mBall.getGlobalBounds().contains(sf::Vector2f(mAI.getPosition().x + mAI.getSize().x / 4, mAI.getPosition().y)) ||
            mBall.getGlobalBounds().contains(sf::Vector2f(mAI.getPosition().x + mAI.getSize().x / 4, mAI.getPosition().y + mAI.getSize().y)) ||
            mBall.getGlobalBounds().contains(sf::Vector2f(mAI.getPosition().x, mAI.getPosition().y)) ||
            mBall.getGlobalBounds().contains(sf::Vector2f(mAI.getPosition().x, mAI.getPosition().y + mAI.getSize().y)) ||
            mBall.getGlobalBounds().contains(sf::Vector2f(mAI.getPosition().x + mAI.getSize().x, mAI.getPosition().y)) ||
            mBall.getGlobalBounds().contains(sf::Vector2f(mAI.getPosition().x + mAI.getSize().x, mAI.getPosition().y + mAI.getSize().y)))
        {
            mBall.setVelocity(mBall.getVelocity().x * -1.f, mBall.getVelocity().y * -1.f);
        }
        else
        {
            mBall.setVelocity(mBall.getVelocity().x * -1.f, mBall.getVelocity().y);
        }
    }

    // end of game
    if (mBall.getGlobalBounds().intersects(sf::FloatRect(-10, -10, 12, mWindow.getSize().y)))
    {
        playerLose = true;
    }

    if (mBall.getGlobalBounds().intersects(sf::FloatRect(mWindow.getSize().x - 2, -10, mWindow.getSize().x + 10, mWindow.getSize().y)))
    {
        playerWin = true;
    }
}

void Game::render()
{

    if (!playerLose && !playerWin)
    {
        mWindow.clear();
        mWindow.setView(mWindow.getDefaultView());

        mWindow.draw(mPlayer);
        mWindow.draw(mAI);
        mWindow.draw(mBall);
        mWindow.draw(mScore);
        mWindow.draw(mLine, 2, sf::Lines);
    }

    if (playerLose)
    {
        mWindow.draw(mLose);
    }

    if (playerWin)
    {
        mWindow.draw(mWin);
    }

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

    case sf::Keyboard::Up:
        mIsMovingUp = isPressed;
        break;

    case sf::Keyboard::Down:
        mIsMovingDown = isPressed;
        break;

    default:
        break;
    }
}