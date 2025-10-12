#include <string>

#include "App/CalqueMenu/CalqueButton.hpp"

namespace MyGimp {
CalqueButton::CalqueButton(std::string name) {
    calqueButton.init(name, "select_calque", 195);
    calqueButton.setColor(sf::Color(50, 50, 50));
    deleteButton.initIcon("Assets/Icons/delete.png", "delete_calque_id", 20);
}

void CalqueButton::draw(sf::RenderWindow &window) {
    calqueButton.draw(window);
    deleteButton.draw(window);
}

void CalqueButton::setPosition(float x, float y) {
    calqueButton.setPosition(x, y);
    deleteButton.setPosition(x + 200, y);
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
    std::string codeReturn = calqueButton.handleInput(event);
    if (codeReturn.empty())
        codeReturn = deleteButton.handleInput(event);
    return codeReturn;
}
}  // namespace MyGimp
