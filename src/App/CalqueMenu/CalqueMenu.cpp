#include <string>
#include <vector>
#include <memory>

#include "App/CalqueMenu/CalqueMenu.hpp"
#include "App/const.hpp"

const int MENU_WIDTH = 250;
const int MENU_HEIGHT = 300;

namespace MyGimp {
CalqueMenu::CalqueMenu() {
    int x = WIDTH - MENU_WIDTH + 10;
    addCalqueButton.setPosition(x, HEIGHT - MENU_HEIGHT + 10);
    addCalqueButton.setState(Button::IDLE);
    x += addCalqueButton.getWidth() + 10;

    deleteCalqueButton.setPosition(x, HEIGHT - MENU_HEIGHT + 10);
    deleteCalqueButton.setState(Button::IDLE);

    background.setSize(sf::Vector2f(MENU_WIDTH, MENU_HEIGHT));
    background.setFillColor(sf::Color(50, 50, 50, 200));
    background.setPosition(WIDTH - MENU_WIDTH, HEIGHT - MENU_HEIGHT);
}

void CalqueMenu::draw(sf::RenderWindow &window) {
    window.draw(background);
    addCalqueButton.draw(window);
    deleteCalqueButton.draw(window);
    int id = 0;
    for (auto &button : calqueButtons) {
        button->setActive(id == actualCalqueId);
        button->draw(window);
        id++;
    }
}

void CalqueMenu::update(std::vector<Calque> &calques, int actualCalqueId) {
    this->actualCalqueId = actualCalqueId;
    calqueButtons.clear();
    for (const auto &calque : calques) {
        std::shared_ptr<CalqueButton> button =
            std::make_shared<CalqueButton>(calque.getName());
        button->setPosition(WIDTH - MENU_WIDTH + 10,
            HEIGHT - MENU_HEIGHT + 50 + calqueButtons.size() * 35);
        calqueButtons.emplace_back(button);
    }
}

std::string CalqueMenu::handleInput(const sf::Event &event) {
    std::string codeReturn = "";

    if (addCalqueButton.handleInput(event) == "add_calque")
        codeReturn = "add_calque";
    if (deleteCalqueButton.handleInput(event) == "delete_calque")
        codeReturn = "delete_calque";
    for (size_t i = 0; i < calqueButtons.size(); i++) {
        if (calqueButtons[i]->handleInput(event) == "select_calque")
            codeReturn = "select_calque_" + std::to_string(i);
    }
    return codeReturn;
}
}  // namespace MyGimp
