#include <vector>
#include <memory>

#include "Plugins/Pencils/Pencil_Grayscale.hpp"

extern "C" MyGimp::Pencil_I* createPencil() {
    return new MyGimp::Pencil_Grayscale();
}

extern "C" void destroyPencil(MyGimp::Pencil_I* p) {
    delete p;
}

namespace MyGimp {
std::vector<Pencil_I::Pixel> MyGimp::Pencil_Grayscale::use(const int x,
const int y, [[maybe_unused]] const sf::Image &img) {
    std::vector<Pixel> pixels;
    int halfSize = size / 2;
    for (int dx = -halfSize; dx <= halfSize; ++dx) {
        for (int dy = -halfSize; dy <= halfSize; ++dy) {
            Pixel p;
            p.x = x + dx;
            p.y = y + dy;
            sf::Color src = getPixelImage(p.x, p.y, img);
            // luminosity method
            uint8_t gray = static_cast<uint8_t>(std::min(255.f,
                0.21f * src.r + 0.72f * src.g + 0.07f * src.b));
            p.color = sf::Color(gray, gray, gray, src.a);
            pixels.push_back(p);
        }
    }
    return pixels;
}
}  // namespace MyGimp
