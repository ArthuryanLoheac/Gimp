#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>

#include "App/TopBar/TopButton.hpp"

namespace MyGimp {
class TopBar {
 public:
    TopBar();
    ~TopBar();
    void draw(sf::RenderWindow &window);
    std::string handleInput(const sf::Event &event);

 private:
    sf::RectangleShape background;
    std::vector<std::shared_ptr<TopButton>> buttons;
};
}  // namespace MyGimp
