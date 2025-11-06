#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "App/TopBar/Button.hpp"

namespace MyGimp {
class PercentageSelector {
 public:
    explicit PercentageSelector(const std::string &code,
       bool isPercentageInput = true);
    ~PercentageSelector() = default;

    void draw(sf::RenderWindow &window);
    std::string handleInput(const sf::Event &event, bool &consumed);
    int getPercentage() const;
    void setPercentage(int value);
    void setPosition(float x, float y);
    void setSelected(bool value);
    bool isSelected() const { return selected; }

    void setTitle(const std::string &titleStr);
    void setIsPercentageInput(bool b);

 private:
    bool selected = false;

    std::string code;
    sf::RectangleShape cursor;
    std::string currentInput;
    int percentage = 0;
    sf::Text text;
    sf::Text title;
    sf::Font font;
    Button buttonUp, buttonDown;
    sf::Clock cursorClock;

    bool isPercentageInput = true;
    std::string characterPercentageInput = "%";
};
}  // namespace MyGimp
