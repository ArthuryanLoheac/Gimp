#include <string>

#include "App/Logger.hpp"

#include "App/DrawApp/DrawApp.hpp"

namespace MyGimp {
void DrawApp::draw(sf::RenderWindow& window) {
    sf::Vector2f pos =  {
        viewOffset.x + window.getSize().x / 2.f - dimensions.x * zoom / 2.f,
        viewOffset.y + window.getSize().y / 2.f - dimensions.y * zoom / 2.f};

    for (int i = static_cast<int>(getCalques().size()) - 1; i >= 0; --i) {
        if (!getCalques()[i].isVisible())
            continue;
        getCalques()[i].draw(window, zoom, pos);
    }
    pencilMenu.draw(window);
    topBar.draw(window);
    calqueMenu.draw(window);
    for (auto& button : pencilsButtons)
        if (button)
            button->draw(window);
}
}  // namespace MyGimp
