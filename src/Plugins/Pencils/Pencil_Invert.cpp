#include <vector>
#include <memory>

#include "Plugins/Pencils/Pencil_Invert.hpp"

extern "C" MyGimp::Pencil_I* createPencil() {
    return new MyGimp::Pencil_Invert();
}

extern "C" void destroyPencil(MyGimp::Pencil_I* p) {
    delete p;
}

namespace MyGimp {
std::vector<Pencil_I::Pixel> MyGimp::Pencil_Invert::use(const int x,
const int y, [[maybe_unused]] const sf::Image &img) {
    std::vector<Pixel> pixels;
    int halfSize = size / 2;
    for (int dx = -halfSize; dx <= halfSize; ++dx) {
        for (int dy = -halfSize; dy <= halfSize; ++dy) {
            Pixel p;
            p.x = x + dx;
            p.y = y + dy;
            sf::Color src = getPixelImage(p.x, p.y, img);
            p.color = sf::Color(255 - src.r, 255 - src.g, 255 - src.b, src.a);
            pixels.push_back(p);
        }
    }
    return pixels;
}
}  // namespace MyGimp
