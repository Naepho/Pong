#include <Score.hpp>

Score::Score(std::string fontName, int textSize)
{
    if (!mFont.loadFromFile(fontName))
    {
    }

    mText.setFont(mFont);
    mCharSize = textSize;
    mText.setCharacterSize(mCharSize);
    mText.setFillColor(sf::Color::White);
    mScore = 0;
    mText.setString(std::to_string(mScore));
}

Score::~Score() {}

void Score::update(int score)
{
    mScore += score;
    mText.setString(std::to_string(mScore));
}

int Score::getSize() const
{
    return mCharSize;
}

sf::FloatRect Score::getLocalBounds()
{
    return mText.getLocalBounds();
}

void Score::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mText, states);
}