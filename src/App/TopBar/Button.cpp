#include <iostream>
#include <string>

#include "App/TopBar/Button.hpp"

namespace MyGimp {
Button::Button(std::string title, std::string code, int widthForced) {
    init(title, code, widthForced);
}

void Button::init(std::string title, std::string code, int widthForced) {
    if (widthForced > 0)
        background.setSize(sf::Vector2f(widthForced, 30));
    else
        background.setSize(sf::Vector2f(title.length() * 10 + 20, 30));
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

void Button::initIcon(const std::string &iconPath, std::string code,
int iconSize) {
    background.setSize(sf::Vector2f(iconSize + 10, iconSize + 10));
    background.setFillColor(sf::Color(70, 70, 70));
    background.setPosition(200, 100);

    if (!iconTexture.loadFromFile(iconPath)) {
        std::cerr << "Failed to load icon for Button" << std::endl;
        return;
    }
    icon.setTexture(iconTexture);
    float scaleX = static_cast<float>(iconSize) / iconTexture.getSize().x;
    float scaleY = static_cast<float>(iconSize) / iconTexture.getSize().y;
    icon.setScale(scaleX, scaleY);
    icon.setPosition(
        background.getPosition().x + 5,
        background.getPosition().y + (background.getSize().y - iconSize) / 2);
    this->code = code;
}

void Button::draw(sf::RenderWindow &window) {
    if (currentState == HIDE)
        return;
    if (currentState == HOVER) {
        background.setFillColor(hoverColor);
    } else if (currentState == ACTIVE) {
        background.setFillColor(activeColor);
    } else {
        background.setFillColor(idleColor);
    }
    window.draw(background);
    if (text.getString() != "")
        window.draw(text);
    if (icon.getTexture() != nullptr)
        window.draw(icon);
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
    if (icon.getTexture() != nullptr)
        icon.setPosition(
            x + 5,
            y + (background.getSize().y - icon.getGlobalBounds().height) / 2);
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

void Button::setHeight(float height) {
    background.setSize(sf::Vector2f(background.getSize().x, height));
}

float Button::getWidth() const {
    return background.getSize().x;
}

std::string Button::getCode() const {
    return code;
}

std::string Button::getTitle() const {
    return text.getString();
}

void Button::setTitle(const std::string &title) {
    text.setString(title);
    background.setSize(sf::Vector2f(title.length() * 10 + 20, 30));
}

sf::Color Button::getColor() const {
    return background.getFillColor();
}

void Button::setColor(const sf::Color &color, stateButton state) {
    if (state == IDLE)
        idleColor = color;
    else if (state == HOVER)
        hoverColor = color;
    else if (state == ACTIVE)
        activeColor = color;

    if (currentState == state)
        background.setFillColor(color);
}

}  // namespace MyGimp
