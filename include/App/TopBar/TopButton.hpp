#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include <vector>
#include <functional>
#include <memory>
#include "App/TopBar/TopButtonsDropDown.hpp"

namespace MyGimp {
class TopButton {
 public:
    enum stateButton { IDLE, HOVER };

    TopButton(std::string title = "Button", std::vector<std::pair<std::string, std::function<void()>>> items = {});
    ~TopButton() = default;
    void draw(sf::RenderWindow &window);
    void handleInput(const sf::Event &event);

    void setPosition(float x, float y);
    float getWidth() const;

 private:
    void activateDropDowns(bool activate);

    bool isDown = false;
    stateButton currentState;
    sf::RectangleShape background;
    sf::Text text;
    sf::Font font;
    std::vector<std::shared_ptr<TopButtonsDropDown>> buttonsDropDown;
};
}  // namespace MyGimp
