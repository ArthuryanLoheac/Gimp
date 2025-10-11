#include "App/TopBar/TopBar.hpp"
#include "Logger.h"

namespace MyGimp {
TopBar::TopBar() {
    background.setSize(sf::Vector2f(1920, 40));
    background.setFillColor(sf::Color(50, 50, 50, 200));
    background.setPosition(0, 0);

    buttons.clear();
    buttons.push_back(std::make_shared<TopButton>("File", std::vector<std::string>{"New", "Open", "Save", "Exit"}));
    buttons.push_back(std::make_shared<TopButton>("Edit", std::vector<std::string>{"Undo", "Redo", "Cut", "Copy", "Paste"}));

    float x = 10.0f;

    for (size_t i = 0; i < buttons.size(); ++i) {
        buttons[i]->setPosition(x, 5);
        x += buttons[i]->getWidth() + 10;
    }
}

TopBar::~TopBar() {
    buttons.clear();
}

void TopBar::draw(sf::RenderWindow &window) {
    window.draw(background);
    for (auto &button : buttons) {
        button->draw(window);
    }
}

void TopBar::handleInput(const sf::Event &event) {
    // Handle top bar specific input here
    for (auto &button : buttons) {
        button->handleInput(event);
    }
}
}  // namespace MyGimp
