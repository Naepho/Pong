#include <AI.hpp>

Ai::Ai(sf::Vector2f rectSize) : mVelocity(0.f, 0.f), mRect(rectSize), mRectSize(rectSize)
{
    mRect.setFillColor(sf::Color::White);
    mSpeed = 175;
}

Ai::~Ai()
{
}

void Ai::update(sf::Time dt, sf::Vector2f ballPos, sf::Vector2f winSize)
{
    mVelocity = sf::Vector2f(0, 0);

    if (ballPos.x < winSize.x / 2)
    {
        if (getPosition().y + mRectSize.y / 2 < winSize.y / 2 - 10)
        {
            bool temp = true;
            while (temp)
            {
                mVelocity.y += 1.f;

                if (getPosition().y + mRectSize.y / 2 < winSize.y / 2 - 5)
                {
                    temp = false;
                }
            }
        }
        else if (getPosition().y + mRectSize.y / 2 > winSize.y / 2 + 10)
        {
            bool temp = true;
            while (temp)
            {
                mVelocity.y -= 1.f;

                if (getPosition().y + mRectSize.y / 2 > winSize.y / 2 + 5)
                {
                    temp = false;
                }
            }
        }
    }
    else
    {
        if (getPosition().y + mRectSize.y / 2 < ballPos.y - 10)
        {
            bool temp = true;
            while (temp)
            {
                mVelocity.y += 1.f;

                if (getPosition().y + mRectSize.y / 2 < ballPos.y - 5)
                {
                    temp = false;
                }
            }
        }
        else if (getPosition().y + mRectSize.y / 2 > ballPos.y + 10)
        {
            bool temp = true;
            while (temp)
            {
                mVelocity.y -= 1.f;

                if (getPosition().y + mRectSize.y / 2 > ballPos.y + 5)
                {
                    temp = false;
                }
            }
        }
        else
        {
        }
    }

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

void Ai::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mRect, states);
}

sf::Vector2f Ai::getSize() const
{
    return mRectSize;
}