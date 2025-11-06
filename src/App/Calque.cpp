#include <string>
#include <cmath>
#include <memory>

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

void Calque::startPainting(const sf::Vector2f& position, float zoom, std::shared_ptr<Pencil_I> pencil) {
    painting = true;
    pencil->clearPixelsPainted();
    sf::Vector2f pos = position - sprite.getPosition();
    paintAt(pos, zoom, pencil);
}

void Calque::continuePainting(const sf::Vector2f& position, float zoom, std::shared_ptr<Pencil_I> pencil) {
    if (!painting || !pencil)
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
        paintAt(point, zoom, pencil);
    }
    lastPaintPos = position - sprite.getPosition();
}

void Calque::paintOnePixel(const Pencil_I::Pixel pixelData) {
    if (pixelData.x >= 0 && pixelData.y >= 0 &&
        pixelData.x < image.getSize().x && pixelData.y < image.getSize().y) {

        const sf::Color pixel = image.getPixel(pixelData.x, pixelData.y);
        const sf::Color newPixel = pixelData.color;
        const float calqueOpacity = pixel.a / 255.f * opacity;
        const float a = (newPixel.a / 255.f) * calqueOpacity;
        if (a == 0) return;

        // Calculer la nouvelle transparence (alpha)
        const float pixelAlpha = pixel.a / 255.f;
        const float outAlpha = a + pixelAlpha * (1 - a);
        if (outAlpha == 0) {
            image.setPixel(pixelData.x, pixelData.y, sf::Color(0, 0, 0, 0));
            return;
        }
        const sf::Uint8 fnlR = static_cast<sf::Uint8>(((newPixel.r * a)
            + (pixel.r * pixelAlpha * (1 - a))) / outAlpha);
        const sf::Uint8 fnlG = static_cast<sf::Uint8>(((newPixel.g * a)
            + (pixel.g * pixelAlpha * (1 - a))) / outAlpha);
        const sf::Uint8 fnlB = static_cast<sf::Uint8>(((newPixel.b * a)
            + (pixel.b * pixelAlpha * (1 - a))) / outAlpha);
        const sf::Uint8 fnlA = static_cast<sf::Uint8>(outAlpha * 255);
        image.setPixel(pixelData.x, pixelData.y, sf::Color(fnlR, fnlG, fnlB, fnlA));
    }
}

void Calque::stopPainting() {
    painting = false;
    lastPaintPos = sf::Vector2f(0, 0);
}

bool Calque::isPainting() const {
    return painting;
}

void Calque::paintAt(const sf::Vector2f& position, float zoom, std::shared_ptr<Pencil_I> pencil) {
    if (!pencil)
        return;
    sf::Vector2f point(position);
    point = point / zoom;
    std::vector<Pencil_I::Pixel> pixelsPaint = pencil->use(point.x, point.y, image);
    for (const Pencil_I::Pixel pixel : pixelsPaint) {
        if (pencil->isPixelinList(pixel.x, pixel.y))
            continue;
        pencil->addPixelPainted(pixel);
        paintOnePixel(pixel);
    }
}
}  // namespace MyGimp
