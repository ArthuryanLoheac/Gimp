#include <string>

#include "App/Logger.hpp"

#include "App/DrawApp/DrawApp.hpp"

namespace MyGimp {
void DrawApp::draw(sf::RenderWindow& window) {
    sf::Vector2f pos =  {
        viewOffset.x + window.getSize().x / 2.f - dimensions.x * zoom / 2.f,
        viewOffset.y + window.getSize().y / 2.f - dimensions.y * zoom / 2.f};

    for (auto &calque : calques) {
        calque.draw(window, zoom, pos);
    }
    topBar.draw(window);
    calqueMenu.draw(window);
}
}  // namespace MyGimp
