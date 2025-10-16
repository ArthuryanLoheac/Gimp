#include <string>

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

const sf::Image& Calque::getImage() const {
    return image;
}

float Calque::getOpacity() const
{
    return opacity;
}

void Calque::setOpacity(float opacity)
{
    if (opacity < 0.0f)
        this->opacity = 0.0f;
    else if (opacity > 1.0f)
        this->opacity = 1.0f;
    else
        this->opacity = opacity;
}

void Calque::draw(sf::RenderWindow &window, float zoom, sf::Vector2f pos)
{
    if (visible) {
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setScale(zoom, zoom);
        sprite.setPosition(pos);
        sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(opacity * 255)));
        window.draw(sprite);
    }
}
}  // namespace MyGimp
