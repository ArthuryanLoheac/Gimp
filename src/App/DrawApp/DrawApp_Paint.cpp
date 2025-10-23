#include <string>
#include <vector>
#include <algorithm>

#include "App/Logger.hpp"

#include "App/DrawApp/DrawApp.hpp"

namespace MyGimp {
void DrawApp::handlePainting(sf::Event &event) {
    if (calques.empty())
        return;
    Calque &currentCalque = calques[actualCalqueId];
    if (!currentCalque.isVisible())
        return;

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        currentCalque.startPainting();
    }
    if (event.type == sf::Event::MouseButtonReleased &&
        event.mouseButton.button == sf::Mouse::Left) {
        currentCalque.stopPainting();
    }
    if (event.type == sf::Event::MouseMoved) {
        if (currentCalque.isPainting()) {
            sf::Vector2i mousePos(event.mouseMove.x, event.mouseMove.y);
            sf::Vector2f worldPos = (sf::Vector2f(mousePos) - viewOffset) / zoom;
            currentCalque.continuePainting(worldPos);
        }
    }
}
}  // namespace MyGimp
