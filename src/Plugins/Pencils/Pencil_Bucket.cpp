#include <vector>
#include <memory>
#include <utility>
#include <cstdint>

#include "Plugins/Pencils/Pencil_Bucket.hpp"

extern "C" MyGimp::Pencil_I* createPencil() {
    return new MyGimp::Pencil_Bucket();
}

extern "C" void destroyPencil(MyGimp::Pencil_I* p) {
    delete p;
}

namespace MyGimp {
std::vector<Pencil_I::Pixel> MyGimp::Pencil_Bucket::use(const int x,
const int y, [[maybe_unused]] const sf::Image &img) {
    std::vector<Pixel> pixels;

    const unsigned int width = img.getSize().x;
    const unsigned int height = img.getSize().y;
    if (x < 0 || y < 0 || x >= static_cast<int>(width) ||
        y >= static_cast<int>(height))
        return pixels;

    sf::Color target = getPixelImage(x, y, img);
    sf::Color fillColor = this->color;

    if (target == fillColor)
        return pixels;

    std::vector<char> visited(static_cast<size_t>(width) * height);
    std::vector<std::pair<int,int>> stack;
    stack.reserve(1024);
    stack.emplace_back(x, y);

    while (!stack.empty()) {
        auto [cx, cy] = stack.back();
        stack.pop_back();

        size_t idx = static_cast<size_t>(cy) * width + static_cast<size_t>(cx);
        if (visited[idx])
            continue;
        visited[idx] = 1;

        sf::Color cur = getPixelImage(cx, cy, img);
        if (cur.r == target.r && cur.g == target.g && cur.b == target.b && cur.a == target.a) {
            Pixel p;
            p.x = cx;
            p.y = cy;
            p.color = fillColor;
            pixels.push_back(p);

            if (cx > 0) stack.emplace_back(cx - 1, cy);
            if (cx + 1 < static_cast<int>(width)) stack.emplace_back(cx + 1, cy);
            if (cy > 0) stack.emplace_back(cx, cy - 1);
            if (cy + 1 < static_cast<int>(height)) stack.emplace_back(cx, cy + 1);
        }
    }

    return pixels;
}
}  // namespace MyGimp
