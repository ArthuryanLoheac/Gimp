#include <vector>
#include <memory>

#include "Plugins/Pencils/Pencil_Contrast.hpp"

extern "C" MyGimp::Pencil_I* createPencil() {
    return new MyGimp::Pencil_Contrast();
}

extern "C" void destroyPencil(MyGimp::Pencil_I* p) {
    delete p;
}

namespace MyGimp {
std::vector<Pencil_I::Pixel> MyGimp::Pencil_Contrast::use(const int x,
const int y, [[maybe_unused]] const sf::Image &img) {
    std::vector<Pixel> pixels;
    int halfSize = size / 2;
    // contrast factor >1 increases contrast, <1 decreases
    const float contrastFactor = 1.2f;
    for (int dx = -halfSize; dx <= halfSize; ++dx) {
        for (int dy = -halfSize; dy <= halfSize; ++dy) {
            Pixel p;
            p.x = x + dx;
            p.y = y + dy;
            sf::Color src = getPixelImage(p.x, p.y, img);
            auto adjust = [&](uint8_t c) -> uint8_t {
                float f = (c / 255.f - 0.5f) * contrastFactor + 0.5f;
                return static_cast<uint8_t>(std::clamp(f * 255.f, 0.f, 255.f));
            };
            p.color = sf::Color(adjust(src.r), adjust(src.g),
                adjust(src.b), src.a);
            pixels.push_back(p);
        }
    }
    return pixels;
}
}  // namespace MyGimp
