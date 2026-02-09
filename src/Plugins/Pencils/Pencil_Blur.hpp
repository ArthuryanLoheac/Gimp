#pragma once
#include <vector>
#include <string>

#include "App/Pencil/Pencil_A.hpp"

namespace MyGimp {
class Pencil_Blur final : public Pencil_A {
 public:
    Pencil_Blur() : Pencil_A("Blur Pencil", "Blur") {}
    ~Pencil_Blur() override = default;

    std::vector<Pixel> use(int x, int y,
        [[maybe_unused]] const sf::Image &img) final;
};
}  // namespace MyGimp
