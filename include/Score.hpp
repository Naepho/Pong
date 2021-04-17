#ifndef SCORE
#define SCORE

#include <SFML/Graphics.hpp>

class Score : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public:
    Score(std::string fontName, int textSize);
    ~Score();

    void update(int score);

    int getSize() const;
    sf::FloatRect getLocalBounds();

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    sf::Text mText;
    sf::Font mFont;
    int mScore;
    int mCharSize;
};

#endif