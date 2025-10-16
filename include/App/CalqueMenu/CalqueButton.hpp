#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "App/TopBar/Button.hpp"

namespace MyGimp {
class CalqueButton {
 public:
    explicit CalqueButton(std::string name = "Calque");
    void draw(sf::RenderWindow &window);
    void setPosition(float x, float y);
    void setName(const std::string &name);
    std::string getTitle() const { return calqueButton.getTitle(); }
    std::string getCode() const { return calqueButton.getCode(); }
    Button::stateButton getState() const { return calqueButton.getState(); }
    void setState(Button::stateButton state) { calqueButton.setState(state); }
    void setActive(bool active);
    std::string handleInput(const sf::Event &event, bool &consumed);
    void setSee(bool see);

 private:
    Button calqueButton;
    Button deleteButton;
    Button seeButton;
};
}  // namespace MyGimp
