#pragma once
#include <vector>
#include <string>

#include "App/Pencil/Pencil_A.hpp"

namespace MyGimp {
class Pencil_Circle final : public Pencil_A {
 public:
    Pencil_Circle() : Pencil_A("Circle Pencil", "Circle") {}
    ~Pencil_Circle() override = default;

    std::vector<Pixel> use(int x, int y,
        [[maybe_unused]] const sf::Image &img) final;
};
}  // namespace MyGimp
