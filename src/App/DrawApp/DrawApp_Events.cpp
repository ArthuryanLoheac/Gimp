#include <string>
#include <vector>
#include <algorithm>

#include "App/Logger.hpp"

#include "App/DrawApp/DrawApp.hpp"

const float MIN_ZOOM = 0.01f;
const float MAX_ZOOM = 25.0f;
const float ZOOM_STEP = 0.1f;

namespace MyGimp {
void DrawApp::handleInput(sf::Event &event) {
    try {
        if (event.type == sf::Event::KeyReleased &&
            event.key.code == sf::Keyboard::E
            && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            exportFile();
        }
        if (event.type == sf::Event::KeyReleased &&
            event.key.code == sf::Keyboard::S
            && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            saveFile();
        }
        handleZooming(event);
        handleDragging(event);
        handleCommandCalques(calqueMenu.handleInput(event));
        handleCommand(topBar.handleInput(event));
    } catch (const std::exception &e) {
        LOG_ERROR(e.what());
    }
}

void DrawApp::handleDragging(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left &&
        sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        dragging = true;
        lastMousePos = sf::Mouse::getPosition();
    }
    if (event.type == sf::Event::MouseButtonReleased &&
        event.mouseButton.button == sf::Mouse::Left && dragging) {
        dragging = false;
    }
    if (event.type == sf::Event::KeyReleased &&
        event.key.code == sf::Keyboard::Space && dragging) {
        dragging = false;
    }
}

void DrawApp::handleZooming(sf::Event &event) {
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0)
            zoom += ZOOM_STEP;
        else if (event.mouseWheelScroll.delta < 0)
            zoom -= ZOOM_STEP;
        zoom = std::clamp(zoom, MIN_ZOOM, MAX_ZOOM);
    }
}
}  // namespace MyGimp
