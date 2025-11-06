#include "App/ColorPicker/ColorPicker.hpp"
#include "App/const.hpp"

namespace MyGimp {
ColorPicker::ColorPicker() {
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
            // Use the event's window-relative coordinates
            int mouseX = event.mouseButton.x;
            int mouseY = event.mouseButton.y;
            sf::Vector2f spritePos = colorSprite.getPosition();
            sf::Vector2u textureSize = colorTexture.getSize();
            textureSize.x = static_cast<unsigned int>(textureSize.x *
                colorSprite.getScale().x);
            textureSize.y = static_cast<unsigned int>(textureSize.y *
                colorSprite.getScale().y);
            if (mouseX >= spritePos.x &&
                mouseX <= spritePos.x + textureSize.x &&
                mouseY >= spritePos.y &&
                mouseY <= spritePos.y + textureSize.y) {
                sf::Image img = colorTexture.copyToImage();
                sf::Color pickedColor = img.getPixel(
                    static_cast<unsigned int>((mouseX -
                        static_cast<int>(spritePos.x))
                        / colorSprite.getScale().x),
                    static_cast<unsigned int>((mouseY -
                        static_cast<int>(spritePos.y))
                        / colorSprite.getScale().y));
                return pickedColor;
            }
        }
    }
    return sf::Color::Transparent;
}

void ColorPicker::setPosition(float x, float y) {
    colorSprite.setPosition(x, y);
}

void ColorPicker::setScale(float scaleX, float scaleY) {
    colorSprite.setScale(scaleX, scaleY);
}

}  // namespace MyGimp
