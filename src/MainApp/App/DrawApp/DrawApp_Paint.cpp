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

    // Deselect on left click outside active selection
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left && selectionActive) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        sf::FloatRect bounds = selectionSprite.getGlobalBounds();
        if (!bounds.contains(mousePos)) {
            cancelSelection();
            return;
        }
    }

    // Move selection: Alt + left click inside selection
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left && selectionActive &&
        sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        startMoveSelection(mousePos);
        return;
    }

    // Shape drawing: R or C + left drag
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left &&
        (sf::Keyboard::isKeyPressed(sf::Keyboard::R) ||
         sf::Keyboard::isKeyPressed(sf::Keyboard::C))) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        startShapeDrawing(mousePos);
        return;
    }

    // Selection: Ctrl + left drag to select
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left &&
        sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        startSelection(mousePos);
        return;
    }

    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
        if (shapeDrawing) {
            updateShapeDrawing(mousePos);
            return;
        }
        if (selecting) {
            updateSelection(mousePos);
            return;
        }
        if (draggingSelection) {
            updateMoveSelection(mousePos);
            return;
        }
        if (getCalque().isPainting()) {
            sf::Vector2f mousePos2(event.mouseMove.x, event.mouseMove.y);
            getCalque().continuePainting(mousePos2, zoom, currentPencil);
        }
        return;
    }

    if (event.type == sf::Event::MouseButtonReleased &&
        event.mouseButton.button == sf::Mouse::Left) {
        if (shapeDrawing) {
            finalizeShapeDrawing();
            return;
        }
        if (selecting) {
            finalizeSelection();
            return;
        }
        if (draggingSelection) {
            commitMoveSelection();
            return;
        }
    }

    // Start Painting with left or right mouse button (disabled when selecting)
    if (!selecting && !draggingSelection && event.type == sf::Event::MouseButtonPressed &&
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

    // Cancel selection with Escape
    if (event.type == sf::Event::KeyReleased &&
        event.key.code == sf::Keyboard::Escape) {
        if (selecting || selectionActive || draggingSelection || shapeDrawing) {
            cancelSelection();
            cancelShapeDrawing();
        }
    }
}

// Sample the composited color at a given window position by blending visible
// calques from top to bottom (like export blending)

sf::Color MyGimp::DrawApp::sampleColorAt(const sf::Vector2f& windowPos) {
    if (getCalques().empty())
        return sf::Color::Transparent;

    // Convert window coords to canvas coords using current calque sprite position
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

// --- Shape drawing helper functions ---

void MyGimp::DrawApp::startShapeDrawing(const sf::Vector2f& windowPos) {
    // Cancel any selection active to avoid conflicts
    if (selectionActive) cancelSelection();
    shapeDrawing = true;
    shapeStartWindow = sf::Vector2i(static_cast<int>(windowPos.x), static_cast<int>(windowPos.y));
    shapeRect = sf::IntRect(0,0,0,0);
    // Determine which shape based on key
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        selectionShape = SelectionShape::RECT;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
        selectionShape = SelectionShape::CIRCLE;
    else
        selectionShape = SelectionShape::RECT;
}

void MyGimp::DrawApp::updateShapeDrawing(const sf::Vector2f& windowPos) {
    sf::Vector2i cur(static_cast<int>(windowPos.x), static_cast<int>(windowPos.y));
    int x0 = std::min(shapeStartWindow.x, cur.x);
    int y0 = std::min(shapeStartWindow.y, cur.y);
    int x1 = std::max(shapeStartWindow.x, cur.x);
    int y1 = std::max(shapeStartWindow.y, cur.y);
    // Convert window coords to canvas coords using current calque sprite
    sf::Vector2f spritePos = getCalque().getCalqueSprite().getPosition();
    int left = static_cast<int>(std::floor((x0 - spritePos.x) / zoom));
    int top = static_cast<int>(std::floor((y0 - spritePos.y) / zoom));
    int right = static_cast<int>(std::floor((x1 - spritePos.x) / zoom));
    int bottom = static_cast<int>(std::floor((y1 - spritePos.y) / zoom));
    if (right < left) std::swap(left, right);
    if (bottom < top) std::swap(top, bottom);
    shapeRect.left = std::max(0, left);
    shapeRect.top = std::max(0, top);
    shapeRect.width = std::max(0, right - left + 1);
    shapeRect.height = std::max(0, bottom - top + 1);
    if (selectionShape == SelectionShape::CIRCLE) {
        shapeCircleCenter.x = shapeRect.left + shapeRect.width / 2;
        shapeCircleCenter.y = shapeRect.top + shapeRect.height / 2;
        shapeCircleRadius = std::min(shapeRect.width, shapeRect.height) / 2;
    }
}

void MyGimp::DrawApp::finalizeShapeDrawing() {
    if (!shapeDrawing) return;
    shapeDrawing = false;
    if (shapeRect.width <= 0 || shapeRect.height <= 0) return;
    // Apply to current calque
    makeSaveCalques();
    Calque &c = getCalque();
    sf::Image img = c.getCalqueImage();
    const sf::Color col = currentPencil->getColor();

    for (int sx = 0; sx < shapeRect.width; ++sx) {
        for (int sy = 0; sy < shapeRect.height; ++sy) {
            int ix = shapeRect.left + sx;
            int iy = shapeRect.top + sy;
            if (ix < 0 || iy < 0 || ix >= static_cast<int>(img.getSize().x) ||
                iy >= static_cast<int>(img.getSize().y)) continue;
            if (selectionShape == SelectionShape::CIRCLE) {
                int dx = ix - shapeCircleCenter.x;
                int dy = iy - shapeCircleCenter.y;
                if (dx*dx + dy*dy > shapeCircleRadius * shapeCircleRadius) continue;
            }
            // blend col onto img at (ix,iy) using calque opacity
            const sf::Color dst = img.getPixel(ix, iy);
            float a = (col.a / 255.f) * c.getOpacity();
            if (a == 0.f) continue;
            float dstA = dst.a / 255.f;
            float outA = a + dstA * (1 - a);
            if (outA == 0.f) { img.setPixel(ix, iy, sf::Color(0,0,0,0)); continue; }
            const sf::Uint8 r = static_cast<sf::Uint8>(((col.r * a) + (dst.r * dstA * (1 - a))) / outA);
            const sf::Uint8 g = static_cast<sf::Uint8>(((col.g * a) + (dst.g * dstA * (1 - a))) / outA);
            const sf::Uint8 b = static_cast<sf::Uint8>(((col.b * a) + (dst.b * dstA * (1 - a))) / outA);
            const sf::Uint8 A = static_cast<sf::Uint8>(outA * 255);
            img.setPixel(ix, iy, sf::Color(r,g,b,A));
        }
    }
    c.setImage(img);
}

void MyGimp::DrawApp::cancelShapeDrawing() {
    shapeDrawing = false;
    shapeRect = sf::IntRect(0,0,0,0);
}

// --- Selection helper functions ---

void MyGimp::DrawApp::startSelection(const sf::Vector2f& windowPos) {
    // If a selection is already active, restore it first to avoid losing it
    if (selectionActive) {
        cancelSelection();
    }
    selecting = true;
    selectionStartWindow = sf::Vector2i(static_cast<int>(windowPos.x),
                                        static_cast<int>(windowPos.y));
    selectionRect = sf::IntRect(0,0,0,0);
    // Determine shape based on modifier keys: R => rectangle, C => circle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        selectionShape = SelectionShape::RECT;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
        selectionShape = SelectionShape::CIRCLE;
    else
        selectionShape = SelectionShape::RECT;
    selectionCircleRadius = 0;
}

void MyGimp::DrawApp::updateSelection(const sf::Vector2f& windowPos) {
    sf::Vector2i cur(static_cast<int>(windowPos.x), static_cast<int>(windowPos.y));
    int x0 = std::min(selectionStartWindow.x, cur.x);
    int y0 = std::min(selectionStartWindow.y, cur.y);
    int x1 = std::max(selectionStartWindow.x, cur.x);
    int y1 = std::max(selectionStartWindow.y, cur.y);
    // Convert window coords to canvas coords
    sf::Vector2f spritePos = getCalque().getCalqueSprite().getPosition();
    int left = static_cast<int>(std::floor((x0 - spritePos.x) / zoom));
    int top = static_cast<int>(std::floor((y0 - spritePos.y) / zoom));
    int right = static_cast<int>(std::floor((x1 - spritePos.x) / zoom));
    int bottom = static_cast<int>(std::floor((y1 - spritePos.y) / zoom));
    if (right < left) std::swap(left, right);
    if (bottom < top) std::swap(top, bottom);
    selectionRect.left = std::max(0, left);
    selectionRect.top = std::max(0, top);
    selectionRect.width = std::max(0, right - left + 1);
    selectionRect.height = std::max(0, bottom - top + 1);

    if (selectionShape == SelectionShape::CIRCLE) {
        // compute circle center and radius in canvas coords
        selectionCircleCenter.x = selectionRect.left + selectionRect.width / 2;
        selectionCircleCenter.y = selectionRect.top + selectionRect.height / 2;
        selectionCircleRadius = std::min(selectionRect.width, selectionRect.height) / 2;
    }
}

void MyGimp::DrawApp::finalizeSelection() {
    selecting = false;
    if (selectionRect.width <= 0 || selectionRect.height <= 0)
        return;
    // Ensure valid calque
    if (actualCalqueId < 0 || actualCalqueId >= static_cast<int>(getCalques().size()))
        return;

    // Extract pixels into selectionImage and clear area (cut)
    Calque &c = getCalque();
    sf::Image img = c.getCalqueImage();

    selectionImage.create(selectionRect.width, selectionRect.height, sf::Color::Transparent);
    selectionBackup.create(selectionRect.width, selectionRect.height, sf::Color::Transparent);

    for (int sx = 0; sx < selectionRect.width; ++sx) {
        for (int sy = 0; sy < selectionRect.height; ++sy) {
            int ix = selectionRect.left + sx;
            int iy = selectionRect.top + sy;
            if (ix >= 0 && iy >= 0 && ix < static_cast<int>(img.getSize().x) &&
                iy < static_cast<int>(img.getSize().y)) {
                // If circle shape, skip pixels outside circle
                if (selectionShape == SelectionShape::CIRCLE) {
                    int dx = ix - selectionCircleCenter.x;
                    int dy = iy - selectionCircleCenter.y;
                    if (dx*dx + dy*dy > selectionCircleRadius * selectionCircleRadius)
                        continue;
                }
                sf::Color p = img.getPixel(ix, iy);
                selectionImage.setPixel(sx, sy, p);
                selectionBackup.setPixel(sx, sy, p);
                img.setPixel(ix, iy, sf::Color(0,0,0,0)); // cut
            }
        }
    }

    // Commit cut to calque
    c.setImage(img);
    selectionTexture.loadFromImage(selectionImage);
    selectionSprite.setTexture(selectionTexture);
    // position sprite in window coords
    sf::Vector2f spritePos = c.getCalqueSprite().getPosition();
    selectionSpriteWindowPos = spritePos + sf::Vector2f(static_cast<float>(selectionRect.left) * zoom,
                                                         static_cast<float>(selectionRect.top) * zoom);
    selectionSprite.setPosition(selectionSpriteWindowPos);

    selectionActive = true;
    selectionCalqueId = actualCalqueId;

    // Save state after cut so user can undo
    makeSaveCalques();
}

void MyGimp::DrawApp::cancelSelection() {
    if (!selectionActive) {
        selecting = false;
        draggingSelection = false;
        return;
    }
    // restore backup into calque
    if (selectionCalqueId != actualCalqueId) {
        // if calque changed, put it back to the original calque
    }
    Calque &c = getCalque();
    sf::Image img = c.getCalqueImage();
    for (int sx = 0; sx < selectionRect.width; ++sx) {
        for (int sy = 0; sy < selectionRect.height; ++sy) {
            int ix = selectionRect.left + sx;
            int iy = selectionRect.top + sy;
            if (ix >= 0 && iy >= 0 && ix < static_cast<int>(img.getSize().x) &&
                iy < static_cast<int>(img.getSize().y)) {
                img.setPixel(ix, iy, selectionBackup.getPixel(sx, sy));
            }
        }
    }
    c.setImage(img);

    // clear selection
    selectionActive = false;
    selecting = false;
    draggingSelection = false;
    selectionRect = sf::IntRect(0,0,0,0);
    selectionImage = sf::Image();
    selectionBackup = sf::Image();
}

void MyGimp::DrawApp::startMoveSelection(const sf::Vector2f& windowPos) {
    if (!selectionActive) return;
    // check if click inside selectionSprite
    sf::FloatRect bounds = selectionSprite.getGlobalBounds();
    if (!bounds.contains(windowPos)) return;
    draggingSelection = true;
    selectionDragStart = sf::Vector2i(static_cast<int>(windowPos.x), static_cast<int>(windowPos.y));
}

void MyGimp::DrawApp::updateMoveSelection(const sf::Vector2f& windowPos) {
    if (!draggingSelection) return;
    sf::Vector2f delta(static_cast<float>(static_cast<int>(windowPos.x) - selectionDragStart.x),
                       static_cast<float>(static_cast<int>(windowPos.y) - selectionDragStart.y));
    selectionSprite.setPosition(selectionSpriteWindowPos + delta);
}

void MyGimp::DrawApp::commitMoveSelection() {
    if (!selectionActive || !draggingSelection) return;
    draggingSelection = false;
    // compute new top-left in canvas coords
    sf::Vector2f spritePos = getCalque().getCalqueSprite().getPosition();
    sf::Vector2f newWindowPos = selectionSprite.getPosition();
    int newLeft = static_cast<int>(std::floor((newWindowPos.x - spritePos.x) / zoom + 0.5f));
    int newTop = static_cast<int>(std::floor((newWindowPos.y - spritePos.y) / zoom + 0.5f));

    Calque &c = getCalque();
    sf::Image img = c.getCalqueImage();

    // Paste selectionImage into img with alpha composition
    for (int sx = 0; sx < selectionImage.getSize().x; ++sx) {
        for (int sy = 0; sy < selectionImage.getSize().y; ++sy) {
            int ix = newLeft + sx;
            int iy = newTop + sy;
            if (ix < 0 || iy < 0 || ix >= static_cast<int>(img.getSize().x) ||
                iy >= static_cast<int>(img.getSize().y)) continue;
            sf::Color src = selectionImage.getPixel(sx, sy);
            sf::Color dst = img.getPixel(ix, iy);
            float a = src.a / 255.f;
            if (a == 0.f) continue;
            float outAlpha = a + (dst.a / 255.f) * (1 - a);
            if (outAlpha == 0.f) { img.setPixel(ix, iy, sf::Color(0,0,0,0)); continue; }
            const sf::Uint8 r = static_cast<sf::Uint8>(((src.r * a) + (dst.r * (dst.a / 255.f) * (1 - a))) / outAlpha);
            const sf::Uint8 g = static_cast<sf::Uint8>(((src.g * a) + (dst.g * (dst.a / 255.f) * (1 - a))) / outAlpha);
            const sf::Uint8 b = static_cast<sf::Uint8>(((src.b * a) + (dst.b * (dst.a / 255.f) * (1 - a))) / outAlpha);
            const sf::Uint8 A = static_cast<sf::Uint8>(outAlpha * 255);
            img.setPixel(ix, iy, sf::Color(r,g,b,A));
        }
    }

    c.setImage(img);

    // clear selection
    selectionActive = false;
    selectionRect = sf::IntRect(0,0,0,0);
    selectionImage = sf::Image();
    selectionBackup = sf::Image();

    // Save state after move
    makeSaveCalques();
}

}  // namespace MyGimp
