#include "App/Calque.hpp"

namespace MyGimp {
void Calque::createFromFile(const std::string& filepath) {
    if (!image.loadFromFile(filepath)) {
        std::cerr << "Error loading image from file: " << filepath << std::endl;
    }
}

void Calque::createEmpty(int width, int height, sf::Color col) {
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

sf::Image& Calque::getImage() {
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