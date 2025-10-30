#include "ColorPicker.hpp"
#include "App/const.hpp"

namespace MyGimp {
ColorPicker::ColorPicker()
{
    if (!colorTexture.loadFromFile("Assets/ColorPicker.jpg"))
        return;
    colorSprite.setTexture(colorTexture);
    setScale(0.64f, 0.64f);
}

void ColorPicker::draw(sf::RenderWindow &window) {
    window.draw(colorSprite);
}

sf::Color ColorPicker::handleInput(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            // Use the event's window-relative coordinates instead of the global mouse position.
            int mouseX = event.mouseButton.x;
            int mouseY = event.mouseButton.y;
            sf::Vector2f spritePos = colorSprite.getPosition();
            sf::Vector2u textureSize = colorTexture.getSize();
            textureSize.x = static_cast<unsigned int>(textureSize.x * colorSprite.getScale().x);
            textureSize.y = static_cast<unsigned int>(textureSize.y * colorSprite.getScale().y);
            if (mouseX >= static_cast<int>(spritePos.x) && mouseX <= static_cast<int>(spritePos.x) + static_cast<int>(textureSize.x) &&
                mouseY >= static_cast<int>(spritePos.y) && mouseY <= static_cast<int>(spritePos.y) + static_cast<int>(textureSize.y)) {
                sf::Image img = colorTexture.copyToImage();
                sf::Color pickedColor = img.getPixel(
                    mouseX - static_cast<int>(spritePos.x),
                    mouseY - static_cast<int>(spritePos.y));
                return pickedColor;
            }
        }
    }
    return sf::Color::Transparent;
}

void ColorPicker::setPosition(float x, float y)
{
    colorSprite.setPosition(x, y);
}

void ColorPicker::setScale(float scaleX, float scaleY)
{
    colorSprite.setScale(scaleX, scaleY);
}

} // namespace MyGimp
