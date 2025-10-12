#include <string>
#include <vector>

#include "App/TopBar/TopBar.hpp"
#include "App/Logger.hpp"

namespace MyGimp {
TopBar::TopBar() {
    background.setSize(sf::Vector2f(1920, 40));
    background.setFillColor(sf::Color(50, 50, 50, 200));
    background.setPosition(0, 0);

    buttons.clear();
    buttons.push_back(std::make_shared<TopButton>("File",
        std::vector<std::pair<std::string, std::string>>{
                    {"New", "new_file"},
                    {"Save", "save_file"},
                    {"Export", "export_file"}}));
    buttons.push_back(std::make_shared<TopButton>("Calque",
        std::vector<std::pair<std::string, std::string>>{
                    {"New Calque", "add_calque"},
                    {"Delete Calque", "delete_calque"}}));

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
    for (auto &button : buttons)
        button->draw(window);
}

std::string TopBar::handleInput(const sf::Event &event) {
    std::string codeReturn = "";

    // Handle top bar specific input here
    for (auto &button : buttons) {
        std::string code = button->handleInput(event);
        if (code != "") codeReturn = code;
    }
    return codeReturn;
}
}  // namespace MyGimp
