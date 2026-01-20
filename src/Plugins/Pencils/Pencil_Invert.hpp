#pragma once
#include <vector>
#include <string>

#include "App/Pencil/Pencil_A.hpp"

namespace MyGimp {
class Pencil_Invert final : public Pencil_A {
 public:
    Pencil_Invert() : Pencil_A("Invert Pencil", "Invert") {}
    ~Pencil_Invert() override = default;

    std::vector<Pixel> use(int x, int y,
        [[maybe_unused]] const sf::Image &img) final;
};
}  // namespace MyGimp
