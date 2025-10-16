#include "App/CalqueMenu/PercentageSelector.hpp"
#include <algorithm>

namespace MyGimp {

PercentageSelector::PercentageSelector(const std::string &code)
{
    if (!font.loadFromFile("Assets/Fonts/Inter.ttf"))
        return;
    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);
    setPercentage(100);
    this->code = code;
    buttonUp.initIcon("Assets/Icons/arrow_up.png", code + "_up", 15);
    buttonDown.initIcon("Assets/Icons/arrow_down.png", code + "_down", 15);
    buttonDown.setSize(15, 15);
    buttonUp.setSize(15, 15);
    buttonDown.setDeltaPosText(-5, 0);
    buttonUp.setDeltaPosText(-5, 0);
    buttonUp.setState(Button::IDLE);
    buttonDown.setState(Button::IDLE);
    cursor.setSize({2, 20});
    setSelected(false);
}

void PercentageSelector::draw(sf::RenderWindow &window)
{
    window.draw(text);
    buttonUp.draw(window);
    buttonDown.draw(window);
    if (cursorClock.getElapsedTime().asSeconds() < 0.5f && selected || (static_cast<int>
        (cursorClock.getElapsedTime().asSeconds() * 2) % 2 == 0) && selected)
        window.draw(cursor);
}

std::string PercentageSelector::handleInput(const sf::Event &event, bool &consumed)
{
    if (consumed)
        return "";
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (event.mouseButton.x >= text.getPosition().x - text.getLocalBounds().width &&
                event.mouseButton.x <= text.getPosition().x + 5 &&
                event.mouseButton.y >= text.getPosition().y &&
                event.mouseButton.y <= text.getPosition().y + text.getCharacterSize()) {
                setSelected(true);
                consumed = true;
            } else {
                setSelected(false);
            }
        }
    }
    if (event.type == sf::Event::TextEntered && selected) {
        if (event.text.unicode == 8) {
            if (!currentInput.empty())
                currentInput.pop_back();
        } else if (event.text.unicode < 128 && event.text.unicode >= 48 &&
            event.text.unicode <= 57) {
            if (currentInput.size() < 3)
                currentInput += static_cast<char>(event.text.unicode);
        }
        consumed = true;
        if (currentInput.empty())
            currentInput = "0";
        return code + "_input_" + currentInput;
    }

    std::string codeReturn = "";
    codeReturn += buttonDown.handleInput(event, consumed);
    codeReturn += buttonUp.handleInput(event, consumed);
    return codeReturn;
}

void PercentageSelector::setPosition(float x, float y)
{
    text.setPosition(x + 45, y + 5);
    cursor.setPosition(x + 30, y + 5);
    buttonUp.setPosition(x + 55, y);
    buttonDown.setPosition(x + 55, y + 15);
}

void PercentageSelector::setSelected(bool value)
{
    selected = value;
    if (selected)
        cursor.setOutlineColor(sf::Color::White);
    else
        cursor.setOutlineColor(sf::Color::Transparent);
}

void PercentageSelector::setPercentage(int value)
{
    percentage = std::clamp(value, 0, 100);
    text.setString(std::to_string(percentage) + "%");
    text.setOrigin(text.getLocalBounds().width, 0);
    currentInput = std::to_string(percentage);
}

int PercentageSelector::getPercentage() const
{
    return percentage;
}

}  // namespace MyGimp
