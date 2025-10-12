#include <string>

#include "App/CalqueMenu/CalqueButton.hpp"

namespace MyGimp {
CalqueButton::CalqueButton(std::string name) {
    calqueButton.init(name, "calque_button", 230);
    calqueButton.setColor(sf::Color(50, 50, 50));
}

void CalqueButton::draw(sf::RenderWindow &window) {
    calqueButton.draw(window);
}

void CalqueButton::setPosition(float x, float y) {
    calqueButton.setPosition(x, y);
}

void CalqueButton::setName(const std::string &name) {
    calqueButton.setTitle(name);
}

std::string CalqueButton::handleInput(const sf::Event &event) {
    return calqueButton.handleInput(event);
}
}  // namespace MyGimp
