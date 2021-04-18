#include <Win.hpp>

Win::Win(std::string fontName, int textSize)
{
    if (!mFont.loadFromFile(fontName))
    {
    }

    mText.setFont(mFont);
    mCharSize = textSize;
    mText.setCharacterSize(mCharSize);
    mText.setFillColor(sf::Color::White);
    mText.setString("You win !");
}

Win::~Win() {}

int Win::getSize() const
{
    return mCharSize;
}

sf::FloatRect Win::getLocalBounds()
{
    return mText.getLocalBounds();
}

void Win::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mText, states);
}