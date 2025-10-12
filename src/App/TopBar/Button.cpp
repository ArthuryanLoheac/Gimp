#include <iostream>
#include <string>

#include "App/TopBar/Button.hpp"

namespace MyGimp {
Button::Button(std::string title, std::string code) {
    background.setSize(sf::Vector2f(200, 30));
    background.setFillColor(sf::Color(70, 70, 70));
    background.setPosition(200, 100);
    currentState = IDLE;

    if (!font.loadFromFile("Assets/Fonts/Inter.ttf"))
        std::cerr << "Failed to load font for Button" << std::endl;

    text.setFont(font);
    text.setString(title);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);
    text.setPosition(210, 110);

    this->code = code;
}

void Button::draw(sf::RenderWindow &window) {
    if (currentState == HIDE)
        return;
    if (currentState == HOVER) {
        background.setFillColor(sf::Color(90, 90, 90));
    } else if (currentState == ACTIVE) {
        background.setFillColor(sf::Color(110, 110, 110));
    } else {
        background.setFillColor(sf::Color(70, 70, 70));
    }
    window.draw(background);
    window.draw(text);
}

std::string Button::handleInput(const sf::Event &event) {
    std::string codeReturn = "";

    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
        if (background.getGlobalBounds().contains(mousePos))
            currentState = HOVER;
        else
            currentState = IDLE;
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            if (background.getGlobalBounds().contains(mousePos)) {
                currentState = ACTIVE;
                codeReturn = code;
            } else {
                currentState = IDLE;
            }
        }
    }
    return codeReturn;
}

void Button::setPosition(float x, float y) {
    background.setPosition(x, y);
    text.setPosition(x + 10, y + 5);
}

Button::stateButton Button::getState() const {
    return currentState;
}

void Button::setState(stateButton state) {
    currentState = state;
}

float Button::getHeight() const {
    return background.getSize().y;
}

std::string Button::getCode() const {
    return code;
}

}  // namespace MyGimp
