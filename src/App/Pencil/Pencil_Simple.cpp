#include "Pencil_Simple.hpp"

namespace MyGimp {
std::vector<Pencil_I::Pixel> MyGimp::Pencil_Simple::use(const int x, const int y)
{
    std::vector<Pixel> pixels;
    int halfSize = size / 2;
    for (int dx = -halfSize; dx <= halfSize; ++dx) {
        for (int dy = -halfSize; dy <= halfSize; ++dy) {
            Pixel p;
            p.x = x + dx;
            p.y = y + dy;
            p.color = color;
            pixels.push_back(p);
        }
    }
    return pixels;
}
}  // namespace MyGimp