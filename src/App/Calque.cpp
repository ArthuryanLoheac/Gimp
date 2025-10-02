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
}

bool Calque::isVisible() const {
    return visible;
}

const std::string& Calque::getName() const {
    return name;
}

sf::Image Calque::getImage() const {
    return image;
}

void Calque::draw(sf::RenderWindow& window) {
    if (visible) {
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        window.draw(sprite);
    }
}
}  // namespace MyGimp