#ifndef BALL
#define BALL

#include <SFML/Graphics.hpp>

class Ball : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public:
    Ball(float radius);
    ~Ball();

    void update(sf::Time dt);

    void setVelocity(sf::Vector2f velocity);
    void setVelocity(float vx, float vy);
    sf::Vector2f getVelocity() const;

    float getSize() const;
    sf::FloatRect getGlobalBounds() const;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    sf::Vector2f mVelocity;
    sf::CircleShape mCirc;
    float mCircSize;
    float mSpeed;
};

#endif