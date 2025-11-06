#include <vector>

#include "App/Pencil/Pencil_Circle.hpp"

namespace MyGimp {
std::vector<Pencil_I::Pixel> MyGimp::Pencil_Circle::use(const int x,
const int y, [[maybe_unused]] const sf::Image &img) {
    std::vector<Pixel> pixels;

    int halfSize = size / 2;
    sf::Vector2f center{x + 0.5f, y + 0.5f};

    for (int dx = -halfSize; dx <= halfSize; ++dx) {
        for (int dy = -halfSize; dy <= halfSize; ++dy) {
            if (dx * dx + dy * dy > halfSize * halfSize)
                continue;
            Pixel p;
            p.x = x + dx;
            p.y = y + dy;
            p.color = this->color;
            pixels.push_back(p);
        }
    }
    return pixels;
}
}  // namespace MyGimp
