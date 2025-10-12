#include "App/CalqueMenu/CalqueMenu.hpp"
#include "const.hpp"

namespace MyGimp {
CalqueMenu::CalqueMenu() {
    addCalqueButton.setPosition(WIDTH - 200, HEIGHT - 50);
    addCalqueButton.setState(Button::IDLE);
}

void CalqueMenu::draw(sf::RenderWindow &window) {
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
