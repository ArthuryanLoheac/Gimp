#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>

namespace MyGimp {
class TopButtonsDropDown {
 public:
    enum stateButton { HIDE, IDLE, HOVER, ACTIVE };

    TopButtonsDropDown(std::string title = "Button", std::function<void()> onClick = nullptr);
    ~TopButtonsDropDown() = default;
    void draw(sf::RenderWindow &window);
    void handleInput(const sf::Event &event);

    void setPosition(float x, float y);
    stateButton getState() const;
    void setState(stateButton state);
    float getHeight() const;

 private:
    std::function<void()> onClick;

    sf::RectangleShape background;
    sf::Text text;
    sf::Font font;
    stateButton currentState;
};
}  // namespace MyGimp
