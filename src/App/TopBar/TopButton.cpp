#include <memory>
#include <string>
#include <vector>

#include "App/TopBar/TopButton.hpp"
#include "App/Logger.hpp"

namespace MyGimp {
TopButton::TopButton(std::string title,
std::vector<std::pair<std::string, std::string>> items) {
    background.setSize(sf::Vector2f(title.length() * 10 + 20, 30));
    background.setFillColor(sf::Color(50, 50, 50));

    if (!font.loadFromFile("Assets/Fonts/Inter.ttf")) {
        Logger::error("Failed to load font for TopButton");
    }

    text.setFont(font);
    text.setString(title);
        text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);

    for (const auto &item : items) {
        std::shared_ptr<Button> dropDown =
            std::make_shared<Button>(item.first, item.second);
        dropDown->setState(Button::stateButton::HIDE);
        buttonsDropDown.push_back(dropDown);
    }
    setPosition(100, 100);
}

void TopButton::draw(sf::RenderWindow &window) {
    if (currentState == HOVER || isDown) {
        background.setFillColor(sf::Color(70, 70, 70));
    } else {
        background.setFillColor(sf::Color(50, 50, 50));
    }

    window.draw(background);
    window.draw(text);
    for (auto &dropDown : buttonsDropDown)
        dropDown->draw(window);
}

std::string TopButton::handleInput(const sf::Event &event) {
    std::string codeReturn = "";

    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
        if (background.getGlobalBounds().contains(mousePos))
            currentState = HOVER;
        else
            currentState = IDLE;
    }
    if (isDown) {
        for (auto &dropDown : buttonsDropDown) {
            std::string code = dropDown->handleInput(event);
            if (code != "") codeReturn = code;
        }
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            if (background.getGlobalBounds().contains(mousePos)) {
                isDown = !isDown;
                activateDropDowns(isDown);
            } else {
                isDown = false;
                activateDropDowns(false);
            }
        }
    }
    return codeReturn;
}

void TopButton::activateDropDowns(bool activate) {
    for (auto &dropDown : buttonsDropDown) {
        if (activate)
            dropDown->setState(Button::stateButton::IDLE);
        else
            dropDown->setState(Button::stateButton::HIDE);
    }
}

void TopButton::setPosition(float x, float y) {
    background.setPosition(x, y);
    text.setPosition(x + 10, y + 5);

    int newY = y + background.getSize().y;
    for (const auto &item : buttonsDropDown) {
        item->setPosition(background.getPosition().x, newY);
        newY += item->getHeight();
    }
}

float TopButton::getWidth() const {
    return background.getSize().x;
}

}  // namespace MyGimp
