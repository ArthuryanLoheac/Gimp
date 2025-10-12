#pragma once
#include <string>
#include <vector>
#include "App/Calque.hpp"
#include "App/TopBar/Button.hpp"

namespace MyGimp {
class CalqueMenu {
 public:
    CalqueMenu();
    ~CalqueMenu() = default;

    void draw(sf::RenderWindow &window);
    void update(float deltaTime, std::vector<Calque> &calques);
    std::string handleInput(const sf::Event &event);

 private:
    Button addCalqueButton{"Add", "add_calque"};
    sf::RectangleShape background;
};
}  // namespace MyGimp

