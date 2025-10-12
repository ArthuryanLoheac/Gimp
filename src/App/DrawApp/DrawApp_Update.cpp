#include <string>

#include "Logger.hpp"

#include "App/DrawApp/DrawApp.hpp"

float getZoom(float dim, float zoom) {
    return (dim * zoom / 2.f - 50);
}

float getMinOffset(unsigned int winDim, float dim, float zoom) {
    return (-static_cast<int>(winDim) / 2.f - getZoom(dim, zoom));
}

float getMaxOffset(unsigned int winDim, float dim, float zoom) {
    return (static_cast<int>(winDim) / 2.f + getZoom(dim, zoom));
}

namespace MyGimp {
void DrawApp::update(float deltaTime, sf::RenderWindow& window) {
    if (dragging) {
        sf::Vector2i currentMousePos = sf::Mouse::getPosition();
        viewOffset += sf::Vector2f(currentMousePos - lastMousePos);
        lastMousePos = currentMousePos;
    }

    // Clamp viewOffset to prevent excessive panning
    if (viewOffset.x > getMaxOffset(window.getSize().x, dimensions.x, zoom))
        viewOffset.x = getMaxOffset(window.getSize().x, dimensions.x, zoom);
    if (viewOffset.y > getMaxOffset(window.getSize().y, dimensions.y, zoom))
        viewOffset.y = getMaxOffset(window.getSize().y, dimensions.y, zoom);
    if (viewOffset.x < getMinOffset(window.getSize().x, dimensions.x, zoom))
        viewOffset.x = getMinOffset(window.getSize().x, dimensions.x, zoom);
    if (viewOffset.y < getMinOffset(window.getSize().y, dimensions.y, zoom))
        viewOffset.y = getMinOffset(window.getSize().y, dimensions.y, zoom);
    calqueMenu.update(deltaTime, calques);
}
}  // namespace MyGimp
