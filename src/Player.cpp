#include <Player.hpp>

Player::Player(sf::Vector2f rectSize) : mVelocity(0.f, 0.f), mRect(rectSize), mRectSize(rectSize)
{
    mRect.setFillColor(sf::Color::White);
    mSpeed = 175;
}

Player::~Player()
{
}

void Player::update(sf::Time dt)
{
    move(mVelocity * dt.asSeconds() * mSpeed);
}

void Player::setVelocity(sf::Vector2f velocity)
{
    mVelocity = velocity;
}

void Player::setVelocity(float vx, float vy)
{
    mVelocity = sf::Vector2f(vx, vy);
}

sf::Vector2f Player::getVelocity() const
{
    return mVelocity;
}

sf::FloatRect Player::getGlobalBounds()
{
    sf::FloatRect bounds = mRect.getLocalBounds();

    bounds.left += getPosition().x;
    bounds.top += getPosition().y;

    return bounds;
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mRect, states);
}

sf::Vector2f Player::getSize() const
{
    return mRectSize;
}