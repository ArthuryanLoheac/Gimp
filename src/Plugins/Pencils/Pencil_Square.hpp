#pragma once
#include <vector>
#include <string>

#include "App/Pencil/Pencil_A.hpp"

namespace MyGimp {
class Pencil_Square final : public Pencil_A {
 public:
    Pencil_Square() : Pencil_A("Square Pencil", "Square") {}
    ~Pencil_Square() override = default;

    std::vector<Pixel> use(int x, int y,
        [[maybe_unused]] const sf::Image &img) final;
};
}  // namespace MyGimp
