#include <vector>
#include <memory>

#include "Plugins/Pencils/Pencil_Sepia.hpp"

extern "C" MyGimp::Pencil_I* createPencil() {
    return new MyGimp::Pencil_Sepia();
}

extern "C" void destroyPencil(MyGimp::Pencil_I* p) {
    delete p;
}

namespace MyGimp {
std::vector<Pencil_I::Pixel> MyGimp::Pencil_Sepia::use(const int x,
const int y, [[maybe_unused]] const sf::Image &img) {
    std::vector<Pixel> pixels;
    int halfSize = size / 2;
    for (int dx = -halfSize; dx <= halfSize; ++dx) {
        for (int dy = -halfSize; dy <= halfSize; ++dy) {
            Pixel p;
            p.x = x + dx;
            p.y = y + dy;
            sf::Color src = getPixelImage(p.x, p.y, img);
            int tr = static_cast<int>(0.393 * src.r + 0.769 * src.g + 0.189 * src.b);
            int tg = static_cast<int>(0.349 * src.r + 0.686 * src.g + 0.168 * src.b);
            int tb = static_cast<int>(0.272 * src.r + 0.534 * src.g + 0.131 * src.b);
            p.color = sf::Color(static_cast<sf::Uint8>(std::min(255, tr)),
                                static_cast<sf::Uint8>(std::min(255, tg)),
                                static_cast<sf::Uint8>(std::min(255, tb)),
                                src.a);
            pixels.push_back(p);
        }
    }
    return pixels;
}
}  // namespace MyGimp
