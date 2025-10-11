#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

namespace MyGimp {
class TopButton {
 public:
    TopButton(std::string title = "Button");
    ~TopButton() = default;
    void draw(sf::RenderWindow &window);
    void handleInput(const sf::Event &event);

    void setPosition(float x, float y);
    float getWidth() const;

 private:
    sf::RectangleShape background;
    sf::Text text;
    sf::Font font;
};
}  // namespace MyGimp
