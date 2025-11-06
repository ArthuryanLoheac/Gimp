#include "Pencil_A.hpp"

namespace MyGimp {
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
