#include <string>
#include <vector>
#include <algorithm>

#include "App/Logger.hpp"

#include "App/DrawApp/DrawApp.hpp"

namespace MyGimp {
void DrawApp::handlePainting(sf::Event &event) {
    if (getCalques().empty())
        return;
    if (!getCalques()[actualCalqueId].isVisible())
        return;

    // Pipette tool with middle mouse button
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Middle) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        sf::Color pickedColor = getCalques()[actualCalqueId].pipetteAt(mousePos, zoom);
        if (pickedColor != sf::Color::Transparent)
            currentPencil->setColor(pickedColor);
    }
    // Start Painting with left or right mouse button
    if (event.type == sf::Event::MouseButtonPressed &&
        (event.mouseButton.button == sf::Mouse::Left ||
         event.mouseButton.button == sf::Mouse::Right)) {
        makeSaveCalques();
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        getCalques()[actualCalqueId].startPainting(mousePos, zoom, currentPencil,
            event.mouseButton.button == sf::Mouse::Right);
    }
    // Stop painting on mouse button release
    if (event.type == sf::Event::MouseButtonReleased &&
        (event.mouseButton.button == sf::Mouse::Left ||
         event.mouseButton.button == sf::Mouse::Right)) {
        getCalques()[actualCalqueId].stopPainting();
    }
    // Continue painting on mouse move
    if (event.type == sf::Event::MouseMoved) {
        if (getCalques()[actualCalqueId].isPainting()) {
            sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
            getCalques()[actualCalqueId].continuePainting(mousePos, zoom, currentPencil);
        }
    }
}
}  // namespace MyGimp
