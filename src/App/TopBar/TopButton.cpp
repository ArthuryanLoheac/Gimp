#include "App/TopBar/TopButton.hpp"
#include "Logger.h"

namespace MyGimp {
TopButton::TopButton(std::string title) {
    background.setSize(sf::Vector2f(title.length() * 10 + 20, 30));
    background.setFillColor(sf::Color::Blue);
    background.setPosition(100, 100);

    if (!font.loadFromFile("Assets/Fonts/Inter.ttf")) {
        Logger::error("Failed to load font for TopButton");
    }

    text.setFont(font);
    text.setString(title);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);
    text.setPosition(110, 110);
}

void TopButton::draw(sf::RenderWindow &window) {
    window.draw(background);
    window.draw(text);
}

void TopButton::handleInput(const sf::Event &event) {
}

void TopButton::setPosition(float x, float y) {
    background.setPosition(x, y);
    text.setPosition(x + 10, y + 5);
}

float TopButton::getWidth() const {
    return background.getSize().x;
}

}  // namespace MyGimp
