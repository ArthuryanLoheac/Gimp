#include <vector>
#include <memory>

#include "Plugins/Pencils/Pencil_Blur.hpp"

extern "C" MyGimp::Pencil_I* createPencil() {
    return new MyGimp::Pencil_Blur();
}

extern "C" void destroyPencil(MyGimp::Pencil_I* p) {
    delete p;
}

namespace MyGimp {
std::vector<Pencil_I::Pixel> MyGimp::Pencil_Blur::use(const int x,
const int y, [[maybe_unused]] const sf::Image &img) {
    std::vector<Pixel> pixels;
    int halfSize = size / 2;
    for (int dx = -halfSize; dx <= halfSize; ++dx) {
        for (int dy = -halfSize; dy <= halfSize; ++dy) {
            int sx = x + dx;
            int sy = y + dy;
            // compute simple box blur average over a small radius (1)
            int rSum = 0, gSum = 0, bSum = 0, aSum = 0;
            int count = 0;
            for (int bx = -1; bx <= 1; ++bx) {
                for (int by = -1; by <= 1; ++by) {
                    sf::Color c = getPixelImage(sx + bx, sy + by, img);
                    rSum += c.r;
                    gSum += c.g;
                    bSum += c.b;
                    aSum += c.a;
                    ++count;
                }
            }
            Pixel p;
            p.x = sx;
            p.y = sy;
            p.color = sf::Color(static_cast<sf::Uint8>(rSum / count),
                                static_cast<sf::Uint8>(gSum / count),
                                static_cast<sf::Uint8>(bSum / count),
                                static_cast<sf::Uint8>(aSum / count));
            pixels.push_back(p);
        }
    }
    return pixels;
}
}  // namespace MyGimp
