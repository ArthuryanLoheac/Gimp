#include "App/TopBar/TopButtonsDropDown.hpp"

namespace MyGimp {
TopButtonsDropDown::TopButtonsDropDown(std::string title) {
    background.setSize(sf::Vector2f(200, 30));
    background.setFillColor(sf::Color(70, 70, 70));
    background.setPosition(200, 100);
    currentState = IDLE;

    if (!font.loadFromFile("Assets/Fonts/Inter.ttf")) {
        std::cerr << "Failed to load font for TopButtonsDropDown" << std::endl;
    }

    text.setFont(font);
    text.setString(title);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);
    text.setPosition(210, 110);
}

void TopButtonsDropDown::draw(sf::RenderWindow &window) {
    if (currentState == HIDE)
        return;
    window.draw(background);
    window.draw(text);
}

void TopButtonsDropDown::handleInput(const sf::Event &event) {
}

void TopButtonsDropDown::setPosition(float x, float y) {
    background.setPosition(x, y);
    text.setPosition(x + 10, y + 5);
}

TopButtonsDropDown::stateButton TopButtonsDropDown::getState() const {
    return currentState;
}

void TopButtonsDropDown::setState(stateButton state) {
    currentState = state;
}

float TopButtonsDropDown::getHeight() const {
    return background.getSize().y;
}

}  // namespace MyGimp
