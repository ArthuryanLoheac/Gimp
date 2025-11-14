#include <vector>

#include "App/Pencil/Pencil_A.hpp"

namespace MyGimp {
void Pencil_A::setOpacity(int opacity) {
    if (opacity < 0)
        color.a = 0;
    else if (opacity > 255)
        color.a = 255;
    else
        color.a = static_cast<sf::Uint8>(opacity);
}

void Pencil_A::setColor(const sf::Color &color) {
    int prevAlpha = this->color.a;
    this->color = color;
    this->color.a = static_cast<sf::Uint8>(prevAlpha);
}

void Pencil_A::clearPixelsPainted() {
    pixelsPainted.clear();
}

const std::vector<Pencil_I::Pixel> &Pencil_A::getPixelsPainted() const {
    return pixelsPainted;
}

void Pencil_A::addPixelPainted(const Pixel &pixel) {
    pixelsPainted.push_back(pixel);
}

bool Pencil_A::isPixelinList(int x, int y) const {
    for (const auto& pixel : pixelsPainted) {
        if (pixel.x == x && pixel.y == y) {
            return true;
        }
    }
    return false;
}

sf::Color Pencil_A::getPixelImage(const int x, const int y,
const sf::Image &img) {
    if (x < 0 || y < 0 ||
        x >= static_cast<int>(img.getSize().x) ||
        y >= static_cast<int>(img.getSize().y)) {
        return sf::Color(0, 0, 0, 0);
    }
    return img.getPixel(static_cast<unsigned int>(x),
                        static_cast<unsigned int>(y));
}
}  // namespace MyGimp
