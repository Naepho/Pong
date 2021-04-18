#ifndef WIN
#define WIN

#include <SFML/Graphics.hpp>

class Win : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
    Win(std::string fontName, int textSize);
    ~Win();

    int getSize() const;
    sf::FloatRect getLocalBounds();

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    sf::Text mText;
    sf::Font mFont;
    int mCharSize;
};

#endif