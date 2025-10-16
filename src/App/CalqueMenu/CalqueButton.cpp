#include <string>

#include "App/CalqueMenu/CalqueButton.hpp"

namespace MyGimp {
CalqueButton::CalqueButton(std::string name) {
    calqueButton.init(name, "select_calque", 230);
    calqueButton.setColor(sf::Color(50, 50, 50));
    deleteButton.initIcon("Assets/Icons/delete.png", "delete_calque_id", 20);
    seeButton.initIcon("Assets/Icons/visibility_on.png", "see_calque_id", 20);
}

void CalqueButton::draw(sf::RenderWindow &window) {
    calqueButton.draw(window);
    deleteButton.draw(window);
    seeButton.draw(window);
}

void CalqueButton::setPosition(float x, float y) {
    calqueButton.setPosition(x, y);
    deleteButton.setPosition(x + 200, y);
    seeButton.setPosition(x + 170, y);
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

std::string CalqueButton::handleInput(const sf::Event &event, bool &consumed) {
    std::string codeReturn = deleteButton.handleInput(event, consumed);
    codeReturn += seeButton.handleInput(event, consumed);
    codeReturn += calqueButton.handleInput(event, consumed);
    return codeReturn;
}

void CalqueButton::setSee(bool see) {
    if (see)
        seeButton.setIcon("Assets/Icons/visibility_on.png", 20);
    else
        seeButton.setIcon("Assets/Icons/visibility_off.png", 20);
}

}  // namespace MyGimp
