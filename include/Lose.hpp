#ifndef LOSE
#define LOSE

#include <SFML/Graphics.hpp>

class Lose : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
    Lose(std::string fontName, int textSize);
    ~Lose();

    int getSize() const;
    sf::FloatRect getLocalBounds();

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    sf::Text mText;
    sf::Font mFont;
    int mCharSize;
};

#endif