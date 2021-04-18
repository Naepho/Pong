#include <Lose.hpp>

Lose::Lose(std::string fontName, int textSize)
{
    if (!mFont.loadFromFile(fontName))
    {
    }

    mText.setFont(mFont);
    mCharSize = textSize;
    mText.setCharacterSize(mCharSize);
    mText.setFillColor(sf::Color::White);
    mText.setString("You lose !");
}

Lose::~Lose() {}

int Lose::getSize() const
{
    return mCharSize;
}

sf::FloatRect Lose::getLocalBounds()
{
    return mText.getLocalBounds();
}

void Lose::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mText, states);
}