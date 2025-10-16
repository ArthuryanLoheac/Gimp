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
    x += deleteCalqueButton.getWidth() + 10;

    arrowUpButton.initIcon("Assets/Icons/arrow_up.png", "move_calque_up", 20);
    arrowUpButton.setPosition(x, HEIGHT - MENU_HEIGHT + 10);
    arrowUpButton.setState(Button::IDLE);
    x += arrowUpButton.getWidth() + 10;

    arrowDownButton.initIcon("Assets/Icons/arrow_down.png",
        "move_calque_down", 20);
    arrowDownButton.setPosition(x, HEIGHT - MENU_HEIGHT + 10);
    arrowDownButton.setState(Button::IDLE);
    x += arrowDownButton.getWidth() + 10;

    background.setSize(sf::Vector2f(MENU_WIDTH, MENU_HEIGHT));
    background.setFillColor(sf::Color(50, 50, 50, 200));
    background.setPosition(WIDTH - MENU_WIDTH, HEIGHT - MENU_HEIGHT);
}

void CalqueMenu::draw(sf::RenderWindow &window) {
    window.draw(background);
    addCalqueButton.draw(window);
    deleteCalqueButton.draw(window);
    arrowUpButton.draw(window);
    arrowDownButton.draw(window);
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

std::string CalqueMenu::handleInput(const sf::Event &event, bool &consumed) {
    std::string codeReturn = "";

    codeReturn += addCalqueButton.handleInput(event, consumed);
    codeReturn += deleteCalqueButton.handleInput(event, consumed);
    codeReturn += arrowUpButton.handleInput(event, consumed);
    codeReturn += arrowDownButton.handleInput(event, consumed);
    for (size_t i = 0; i < calqueButtons.size(); i++) {
        std::string code = calqueButtons[i]->handleInput(event, consumed);
        if (code != "")
            codeReturn += code + "_" + std::to_string(i);
    }
    return codeReturn;
}

std::vector<std::shared_ptr<CalqueButton>> &CalqueMenu::getCalqueButtons() {
    return calqueButtons;
}
}  // namespace MyGimp
