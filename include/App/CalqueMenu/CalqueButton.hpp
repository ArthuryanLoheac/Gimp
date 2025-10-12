#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "App/TopBar/Button.hpp"

namespace MyGimp {
class CalqueButton {
 public:
    explicit CalqueButton(std::string name = "Calque");
    void draw(sf::RenderWindow &window);
    void setPosition(float x, float y);
    void setName(const std::string &name);
    std::string handleInput(const sf::Event &event);

 private:
    Button calqueButton;
};
}  // namespace MyGimp
