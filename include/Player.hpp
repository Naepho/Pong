#ifndef PLAYER
#define PLAYER

#include <SFML/Graphics.hpp>

class Player : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public:
    Player(sf::Vector2f rectSize);
    ~Player();

    void update(sf::Time dt);

    void setVelocity(sf::Vector2f velocity);
    void setVelocity(float vx, float vy);
    sf::Vector2f getVelocity() const;

    sf::Vector2f getSize() const;
    sf::FloatRect getGlobalBounds();

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    sf::Vector2f mVelocity;
    sf::RectangleShape mRect;
    sf::Vector2f mRectSize;
    float mSpeed;
};

#endif