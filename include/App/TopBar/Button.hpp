#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>

namespace MyGimp {
class Button {
 public:
    enum stateButton { HIDE, IDLE, HOVER, ACTIVE };

    explicit Button(std::string title = "Button",
       std::string code = "", bool widthForced = false);
    ~Button() = default;
    void draw(sf::RenderWindow &window);
    std::string handleInput(const sf::Event &event);

    void setPosition(float x, float y);
    stateButton getState() const;
    void setState(stateButton state);
    float getHeight() const;
    std::string getCode() const;

 private:
    sf::RectangleShape background;
    sf::Text text;
    sf::Font font;
    stateButton currentState;
    std::string code;
};
}  // namespace MyGimp
