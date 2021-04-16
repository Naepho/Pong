#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>

class Game
{
public:
    Game();
    ~Game();

    void run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();

    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:
    static const sf::Time TimePerFrame;
    sf::RenderWindow mWindow;
};

#endif