#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

#include "App/Logger.hpp"

#include "App/DrawApp/DrawApp.hpp"

namespace MyGimp {
void DrawApp::handlePainting(sf::Event &event) {
    if (getCalques().empty())
        return;
    if (!getCalque().isVisible())
        return;

    // Pipette tool with middle mouse button (samples composited color)
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Middle) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        sf::Color pickedColor = sampleColorAt(mousePos);
        if (pickedColor != sf::Color::Transparent)
            currentPencil->setColor(pickedColor);
    }
    // Start Painting with left or right mouse button
    if (event.type == sf::Event::MouseButtonPressed &&
        (event.mouseButton.button == sf::Mouse::Left ||
         event.mouseButton.button == sf::Mouse::Right)) {
        makeSaveCalques();
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        getCalque().startPainting(mousePos, zoom, currentPencil,
            event.mouseButton.button == sf::Mouse::Right);
    }
    // Stop painting on mouse button release
    if (event.type == sf::Event::MouseButtonReleased &&
        (event.mouseButton.button == sf::Mouse::Left ||
         event.mouseButton.button == sf::Mouse::Right)) {
        getCalque().stopPainting();
    }
    // Continue painting on mouse move
    if (event.type == sf::Event::MouseMoved) {
        if (getCalque().isPainting()) {
            sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
            getCalque().continuePainting(mousePos, zoom, currentPencil);
        }
    }
}

// Sample the composited color at a given window position by blending visible
// calques from top to bottom (like export blending)
sf::Color DrawApp::sampleColorAt(const sf::Vector2f& windowPos) {
    if (getCalques().empty())
        return sf::Color::Transparent;

    // Convert window coords to canvas coords using sprite position (set in draw)
    sf::Vector2f pos = windowPos - getCalque().getCalqueSprite().getPosition();
    pos = pos / zoom;
    int ix = static_cast<int>(std::floor(pos.x));
    int iy = static_cast<int>(std::floor(pos.y));

    sf::Color outColor(0, 0, 0, 0);
    float outAlpha = 0.f;

    for (int i = static_cast<int>(getCalques().size()) - 1; i >= 0; --i) {
        const Calque &c = getCalques()[i];
        if (!c.isVisible()) continue;
        if (ix < 0 || iy < 0 || ix >= static_cast<int>(c.getImage().getSize().x) ||
            iy >= static_cast<int>(c.getImage().getSize().y))
            continue;

        sf::Color newPixel = c.getImage().getPixel(static_cast<unsigned int>(ix),
                                                   static_cast<unsigned int>(iy));
        float a = (newPixel.a / 255.f) * c.getOpacity();
        if (a == 0.f) continue;

        float outAlphaNew = a + outAlpha * (1 - a);
        if (outAlphaNew == 0.f) {
            outAlpha = 0.f;
            outColor = sf::Color::Transparent;
            continue;
        }

        const float r = (((newPixel.r * a) + (outColor.r * outAlpha * (1 - a))) / outAlphaNew);
        const float g = (((newPixel.g * a) + (outColor.g * outAlpha * (1 - a))) / outAlphaNew);
        const float b = (((newPixel.b * a) + (outColor.b * outAlpha * (1 - a))) / outAlphaNew);

        outAlpha = outAlphaNew;
        outColor = sf::Color(static_cast<sf::Uint8>(std::clamp<int>(static_cast<int>(r), 0, 255)),
                             static_cast<sf::Uint8>(std::clamp<int>(static_cast<int>(g), 0, 255)),
                             static_cast<sf::Uint8>(std::clamp<int>(static_cast<int>(b), 0, 255)),
                             static_cast<sf::Uint8>(outAlpha * 255));

        if (outAlpha >= 0.999f)
            break; // opaque enough, stop
    }

    return outColor;
}

}  // namespace MyGimp
