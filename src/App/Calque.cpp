#include <string>
#include <cmath>

#include "App/Calque.hpp"
#include "Exceptions/CalqueExceptions.hpp"

namespace MyGimp {
void Calque::createFromFile(const std::string& filepath) {
    if (!image.loadFromFile(filepath))
        throw Calque_FileError("Unable to load image from " + filepath);
}

void Calque::createEmpty(int width, int height, sf::Color col) {
    if (width <= 0 || height <= 0)
        throw Calque_InvalidSize("Width and Height must be positive integers.");
    image.create(width, height, col);
}

void Calque::setVisible(bool isVisible) {
    visible = isVisible;
    if (!visible)
        stopPainting();
}

bool Calque::isVisible() const {
    return visible;
}

const std::string& Calque::getName() const {
    return name;
}

const sf::Image& Calque::getImage() const {
    return image;
}

float Calque::getOpacity() const {
    return opacity;
}

void Calque::setOpacity(float opacity) {
    if (opacity < 0.0f)
        this->opacity = 0.0f;
    else if (opacity > 1.0f)
        this->opacity = 1.0f;
    else
        this->opacity = opacity;
}

void Calque::draw(sf::RenderWindow &window, float zoom, sf::Vector2f pos) {
    if (visible) {
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setScale(zoom, zoom);
        sprite.setPosition(pos);
        sprite.setColor(sf::Color(255, 255, 255,
            static_cast<sf::Uint8>(opacity * 255)));
        window.draw(sprite);
    }
}

void Calque::startPainting() {
    painting = true;
}

void Calque::continuePainting(const sf::Vector2f& position, float zoom) {
    if (!painting)
        return;

    if (lastPaintPos == sf::Vector2f(0, 0))
        lastPaintPos = position - sprite.getPosition();
    sf::Vector2f start = lastPaintPos;
    sf::Vector2f end = position - sprite.getPosition();

    // Simple Bresenham's line algorithm for painting between points
    sf::Vector2f delta = end - start;
    float length = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    int steps = static_cast<int>(length);
    for (int i = 0; i <= steps; ++i) {
        float t = static_cast<float>(i) / steps;
        sf::Vector2f point = start + t * delta;
        point = point / zoom;
        if (point.x >= 0 && point.y >= 0 &&
            point.x < image.getSize().x && point.y < image.getSize().y) {
            image.setPixel(static_cast<unsigned int>(point.x),
                           static_cast<unsigned int>(point.y),
                           sf::Color::White); // Painting with black color
        }
    }
    lastPaintPos = position - sprite.getPosition();
}

void Calque::stopPainting() {
    painting = false;
    lastPaintPos = sf::Vector2f(0, 0);
}

bool Calque::isPainting() const {
    return painting;
}

}  // namespace MyGimp
