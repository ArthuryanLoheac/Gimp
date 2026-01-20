#include <vector>
#include <memory>

#include "Plugins/Pencils/Pencil_Brightness.hpp"

extern "C" MyGimp::Pencil_I* createPencil() {
    return new MyGimp::Pencil_Brightness();
}

extern "C" void destroyPencil(MyGimp::Pencil_I* p) {
    delete p;
}

namespace MyGimp {
std::vector<Pencil_I::Pixel> MyGimp::Pencil_Brightness::use(const int x,
const int y, [[maybe_unused]] const sf::Image &img) {
    std::vector<Pixel> pixels;
    int halfSize = size / 2;
    const int delta = 30;  // increase brightness by this amount
    for (int dx = -halfSize; dx <= halfSize; ++dx) {
        for (int dy = -halfSize; dy <= halfSize; ++dy) {
            Pixel p;
            p.x = x + dx;
            p.y = y + dy;
            sf::Color src = getPixelImage(p.x, p.y, img);
            auto bright = [&](uint8_t c) -> uint8_t {
                return static_cast<uint8_t>(std::clamp<int>(static_cast<int>(c)
                    + delta, 0, 255));
            };
            p.color = sf::Color(bright(src.r), bright(src.g),
                bright(src.b), src.a);
            pixels.push_back(p);
        }
    }
    return pixels;
}
}  // namespace MyGimp
