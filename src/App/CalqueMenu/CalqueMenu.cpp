#include <string>
#include <vector>

#include "App/CalqueMenu/CalqueMenu.hpp"
#include "App/const.hpp"

const int MENU_WIDTH = 250;
const int MENU_HEIGHT = 300;

namespace MyGimp {
CalqueMenu::CalqueMenu() {
    addCalqueButton.setPosition(WIDTH - MENU_WIDTH + 10, HEIGHT - MENU_HEIGHT + 10);
    addCalqueButton.setState(Button::IDLE);

    background.setSize(sf::Vector2f(MENU_WIDTH, MENU_HEIGHT));
    background.setFillColor(sf::Color(50, 50, 50, 200));
    background.setPosition(WIDTH - MENU_WIDTH, HEIGHT - MENU_HEIGHT);
}

void CalqueMenu::draw(sf::RenderWindow &window) {
    window.draw(background);
    addCalqueButton.draw(window);
    for (auto &button : calqueButtons)
        button->draw(window);
}

void CalqueMenu::update(float deltaTime, std::vector<Calque> &calques) {
    calqueButtons.clear();
    for (const auto &calque : calques) {
        std::shared_ptr<CalqueButton> button =
            std::make_shared<CalqueButton>(calque.getName());
        button->setPosition(WIDTH - MENU_WIDTH + 10, HEIGHT - MENU_HEIGHT + 50 + calqueButtons.size() * 35);
        calqueButtons.emplace_back(button);
    }
}

std::string CalqueMenu::handleInput(const sf::Event &event) {
    std::string codeReturn = "";

    if (addCalqueButton.handleInput(event) == "add_calque")
        codeReturn = "add_calque";
    return codeReturn;
}
}  // namespace MyGimp
