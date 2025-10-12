#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>
#include "App/TopBar/Button.hpp"

namespace MyGimp {
class TopButton {
 public:
    enum stateButton { IDLE, HOVER };

    explicit TopButton(std::string title = "Button",
        std::vector<std::pair<std::string, std::string>> items = {});
    ~TopButton() = default;
    void draw(sf::RenderWindow &window);
    std::string handleInput(const sf::Event &event);

    void setPosition(float x, float y);
    float getWidth() const;

 private:
    void activateDropDowns(bool activate);

    bool isDown = false;
    stateButton currentState;
    sf::RectangleShape background;
    sf::Text text;
    sf::Font font;
    std::vector<std::shared_ptr<Button>> buttonsDropDown;
};
}  // namespace MyGimp
