#pragma once
#include <SFML/Graphics.hpp>

namespace MyGimp {
class ColorPicker {
 public:
    ColorPicker();
    ~ColorPicker() = default;

    void draw(sf::RenderWindow& window);
    sf::Color handleInput(sf::Event& event);
    void setPosition(float x, float y);

 private:
    sf::Texture colorTexture;
    sf::Sprite colorSprite;
};

}  // namespace MyGimp
