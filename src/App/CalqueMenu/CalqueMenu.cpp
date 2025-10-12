#include "App/CalqueMenu/CalqueMenu.hpp"
#include "const.hpp"

namespace MyGimp {
CalqueMenu::CalqueMenu() {
    const int width = 250;
    const int height = 300;
    addCalqueButton.setPosition(WIDTH - width + 10, HEIGHT - height + 10);
    addCalqueButton.setState(Button::IDLE);

    background.setSize(sf::Vector2f(width, height));
    background.setFillColor(sf::Color(50, 50, 50, 200));
    background.setPosition(WIDTH - width, HEIGHT - height);
}

void CalqueMenu::draw(sf::RenderWindow &window) {
    window.draw(background);
    addCalqueButton.draw(window);
}

void CalqueMenu::update(float deltaTime, std::vector<Calque> &calques) {
}

std::string CalqueMenu::handleInput(const sf::Event &event) {
    std::string codeReturn = "";

    if (addCalqueButton.handleInput(event) == "add_calque")
        codeReturn = "add_calque";
    return codeReturn;
}
}  // namespace MyGimp
