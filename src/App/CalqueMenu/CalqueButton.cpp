#include <string>

#include "App/CalqueMenu/CalqueButton.hpp"

namespace MyGimp {
CalqueButton::CalqueButton(std::string name) {
    calqueButton.init(name, "select_calque", 230);
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

void CalqueButton::setActive(bool active) {
    if (active)
        calqueButton.setColor(sf::Color(70, 70, 70), Button::IDLE);
    else
        calqueButton.setColor(sf::Color(50, 50, 50), Button::IDLE);
}

std::string CalqueButton::handleInput(const sf::Event &event) {
    return calqueButton.handleInput(event);
}
}  // namespace MyGimp
