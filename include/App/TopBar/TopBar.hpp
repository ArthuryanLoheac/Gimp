#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

namespace MyGimp {
class TopBar {
 public:
    TopBar();
    ~TopBar() = default;
    void draw(sf::RenderWindow &window);
    void handleInput(const sf::Event &event);

 private:
    sf::RectangleShape background;
};
}  // namespace MyGimp
