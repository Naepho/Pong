#include <AI.hpp>

Ai::Ai(sf::Vector2f rectSize) : mVelocity(0.f, 0.f), mRect(rectSize), mRectSize(rectSize)
{
    mRect.setFillColor(sf::Color::White);
    mSpeed = 150;
}

Ai::~Ai()
{
}

void Ai::update(sf::Time dt)
{
    move(mVelocity * dt.asSeconds() * mSpeed);
}

void Ai::setVelocity(sf::Vector2f velocity)
{
    mVelocity = velocity;
}

void Ai::setVelocity(float vx, float vy)
{
    mVelocity = sf::Vector2f(vx, vy);
}

sf::Vector2f Ai::getVelocity() const
{
    return mVelocity;
}

sf::FloatRect Ai::getGlobalBounds()
{
    sf::FloatRect bounds = mRect.getLocalBounds();

    bounds.left += getPosition().x;
    bounds.top += getPosition().y;

    return bounds;
}

void Ai::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mRect, states);
}

sf::Vector2f Ai::getSize() const
{
    return mRectSize;
}