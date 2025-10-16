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
}

void PercentageSelector::draw(sf::RenderWindow &window)
{
    window.draw(text);
    buttonUp.draw(window);
    buttonDown.draw(window);
}

std::string PercentageSelector::handleInput(const sf::Event &event, bool &consumed)
{
    std::string codeReturn = "";
    codeReturn += buttonDown.handleInput(event, consumed);
    codeReturn += buttonUp.handleInput(event, consumed);
    return codeReturn;
}

void PercentageSelector::setPosition(float x, float y)
{
    text.setPosition(x + 45, y + 5);
    buttonUp.setPosition(x + 55, y);
    buttonDown.setPosition(x + 55, y + 15);
}

void PercentageSelector::setPercentage(int value)
{
    percentage = std::clamp(value, 0, 100);
    text.setString(std::to_string(percentage) + "%");
    text.setOrigin(text.getLocalBounds().width, 0);
}

int PercentageSelector::getPercentage() const
{
    return percentage;
}

}  // namespace MyGimp
