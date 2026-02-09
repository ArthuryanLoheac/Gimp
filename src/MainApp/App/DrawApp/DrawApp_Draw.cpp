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

    // Draw selection overlay while selecting or when active
    if (selecting || (selectionActive && selectionCalqueId == actualCalqueId)) {
        // If selection has been cut and is being moved, draw the floating sprite
        if (selectionActive && selectionCalqueId == actualCalqueId) {
            selectionSprite.setScale(zoom, zoom);
            window.draw(selectionSprite);
        }

        // Draw shape preview when shapeDrawing (same visuals as selection preview)
        if (shapeDrawing && (shapeRect.width > 0 && shapeRect.height > 0)) {
            sf::Vector2f spritePos = getCalque().getCalqueSprite().getPosition();
            sf::Vector2f rectPos(spritePos.x + shapeRect.left * zoom,
                                 spritePos.y + shapeRect.top * zoom);
            if (selectionShape == SelectionShape::RECT) {
                sf::RectangleShape fill;
                fill.setSize(sf::Vector2f(shapeRect.width * zoom,
                                          shapeRect.height * zoom));
                fill.setPosition(rectPos);
                fill.setFillColor(sf::Color(100, 150, 255, 60)); // subtle blue fill
                window.draw(fill);

                sf::RectangleShape outline;
                outline.setSize(sf::Vector2f(shapeRect.width * zoom,
                                             shapeRect.height * zoom));
                outline.setPosition(rectPos);
                outline.setFillColor(sf::Color::Transparent);
                outline.setOutlineColor(sf::Color(255,255,255,200));
                outline.setOutlineThickness(1.f);
                window.draw(outline);
            } else {
                float radiusWindow = shapeCircleRadius * zoom;
                sf::CircleShape fill(radiusWindow);
                sf::Vector2f centerWindow(spritePos.x + shapeCircleCenter.x * zoom,
                                          spritePos.y + shapeCircleCenter.y * zoom);
                fill.setOrigin(radiusWindow, radiusWindow);
                fill.setPosition(centerWindow);
                fill.setFillColor(sf::Color(100, 150, 255, 60));
                window.draw(fill);

                sf::CircleShape outline(radiusWindow);
                outline.setOrigin(radiusWindow, radiusWindow);
                outline.setPosition(centerWindow);
                outline.setFillColor(sf::Color::Transparent);
                outline.setOutlineColor(sf::Color(255,255,255,200));
                outline.setOutlineThickness(1.f);
                window.draw(outline);
            }
        }

        // Only draw rectangle/circle if we have a non-empty selectionRect
        if (selectionRect.width > 0 && selectionRect.height > 0) {
            sf::Vector2f spritePos = getCalque().getCalqueSprite().getPosition();
            sf::Vector2f rectPos(spritePos.x + selectionRect.left * zoom,
                                 spritePos.y + selectionRect.top * zoom);

            if (selectionShape == SelectionShape::RECT) {
                sf::RectangleShape fill;
                fill.setSize(sf::Vector2f(selectionRect.width * zoom,
                                          selectionRect.height * zoom));
                fill.setPosition(rectPos);
                fill.setFillColor(sf::Color(100, 150, 255, 60)); // subtle blue fill
                window.draw(fill);

                sf::RectangleShape outline;
                outline.setSize(sf::Vector2f(selectionRect.width * zoom,
                                             selectionRect.height * zoom));
                // position outline at the current sprite position (updated while dragging)
                outline.setPosition(rectPos);
                outline.setFillColor(sf::Color::Transparent);
                outline.setOutlineColor(sf::Color(255,255,255,200));
                outline.setOutlineThickness(1.f);
                window.draw(outline);
            } else {
                // Circle: draw circle overlay
                float radiusWindow = selectionCircleRadius * zoom;
                sf::CircleShape fill(radiusWindow);
                // circle center in window coords
                sf::Vector2f centerWindow(spritePos.x + selectionCircleCenter.x * zoom,
                                          spritePos.y + selectionCircleCenter.y * zoom);
                fill.setOrigin(radiusWindow, radiusWindow);
                fill.setPosition(centerWindow);
                fill.setFillColor(sf::Color(100, 150, 255, 60));
                window.draw(fill);

                sf::CircleShape outline(radiusWindow);
                outline.setOrigin(radiusWindow, radiusWindow);
                outline.setPosition(centerWindow);
                outline.setFillColor(sf::Color::Transparent);
                outline.setOutlineColor(sf::Color(255,255,255,200));
                outline.setOutlineThickness(1.f);
                window.draw(outline);
            }
        }
    }

    pencilMenu.draw(window);
    for (auto& button : pencilsButtons)
        if (button)
            button->draw(window);
    topBar.draw(window);
    calqueMenu.draw(window);
}
}  // namespace MyGimp
