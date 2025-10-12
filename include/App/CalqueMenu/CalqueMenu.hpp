#pragma once
#include <string>
#include <vector>
#include <memory>
#include "App/Calque.hpp"
#include "App/TopBar/Button.hpp"
#include "App/CalqueMenu/CalqueButton.hpp"

namespace MyGimp {
class CalqueMenu {
 public:
    CalqueMenu();
    ~CalqueMenu() = default;

    void draw(sf::RenderWindow &window);
    void update(float deltaTime, std::vector<Calque> &calques);
    std::string handleInput(const sf::Event &event);

 private:
    std::vector<std::shared_ptr<CalqueButton>> calqueButtons;
    Button addCalqueButton{"Add", "add_calque", 0};
    sf::RectangleShape background;
};
}  // namespace MyGimp

