#include "App/TopBar/TopButtonsDropDown.hpp"

namespace MyGimp {
TopButtonsDropDown::TopButtonsDropDown(std::string title, std::function<void()> onClick) {
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

    this->onClick = onClick;
}

void TopButtonsDropDown::draw(sf::RenderWindow &window) {
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

void TopButtonsDropDown::handleInput(const sf::Event &event) {
    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
        if (background.getGlobalBounds().contains(mousePos)) {
            currentState = HOVER;
        } else {
            currentState = IDLE;
        }
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            if (background.getGlobalBounds().contains(mousePos)) {
                currentState = ACTIVE;
                if (onClick)
                    onClick();
            } else {
                currentState = IDLE;
            }
        }
    }
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
