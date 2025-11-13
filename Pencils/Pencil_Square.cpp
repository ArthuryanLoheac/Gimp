#include <vector>
#include <memory>

#include "Pencil_Square.hpp"

extern "C" MyGimp::Pencil_I* createPencil() {
    return new MyGimp::Pencil_Square();
}

extern "C" void destroyPencil(MyGimp::Pencil_I* p) {
    delete p;
}

namespace MyGimp {
std::vector<Pencil_I::Pixel> MyGimp::Pencil_Square::use(const int x,
const int y, [[maybe_unused]] const sf::Image &img) {
    std::vector<Pixel> pixels;

    int halfSize = size / 2;
    for (int dx = -halfSize; dx <= halfSize; ++dx) {
        for (int dy = -halfSize; dy <= halfSize; ++dy) {
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
