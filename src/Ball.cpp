#include <Ball.hpp>

Ball::Ball(float radius) : mVelocity(0.f, 0.f), mCirc(radius), mCircSize(radius)
{
    mCirc.setFillColor(sf::Color::White);
    mSpeed = 250;
}

Ball::~Ball()
{
}

void Ball::update(sf::Time dt)
{
    move(mVelocity * dt.asSeconds() * mSpeed);
}

void Ball::setVelocity(sf::Vector2f velocity)
{
    mVelocity = velocity;
}

void Ball::setVelocity(float vx, float vy)
{
    mVelocity = sf::Vector2f(vx, vy);
}

sf::Vector2f Ball::getVelocity() const
{
    return mVelocity;
}

sf::FloatRect Ball::getGlobalBounds() const
{
    sf::FloatRect bounds = mCirc.getLocalBounds();

    bounds.left += getPosition().x;
    bounds.top += getPosition().y;

    return bounds;
}

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mCirc, states);
}

float Ball::getSize() const
{
    return mCircSize;
}