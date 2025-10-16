#pragma once
#include <string>
#include <vector>
#include <memory>
#include "App/Calque.hpp"
#include "App/TopBar/Button.hpp"
#include "App/CalqueMenu/CalqueButton.hpp"
#include "App/CalqueMenu/PercentageSelector.hpp"

namespace MyGimp {
class CalqueMenu {
 public:
    CalqueMenu();
    ~CalqueMenu() = default;

    void draw(sf::RenderWindow &window);
    void update(std::vector<Calque> &calques, int actualCalqueId);
    std::string handleInput(const sf::Event &event, bool &consumed);

    std::vector<std::shared_ptr<CalqueButton>> &getCalqueButtons();
    PercentageSelector &getPercentageSelector();
 private:
    void initButton(Button &button, const std::string &iconPath,
        const std::string &code, int &x);

    int actualCalqueId = 0;
    std::vector<std::shared_ptr<CalqueButton>> calqueButtons;
    Button addCalqueButton, deleteCalqueButton, arrowUpButton, arrowDownButton;
    PercentageSelector percentageSelector{"opacity_selector"};

    sf::RectangleShape background;
};
}  // namespace MyGimp

