#pragma once
#include <vector>
#include <string>

#include "App/Pencil/Pencil_A.hpp"

namespace MyGimp {
class Pencil_Sepia final : public Pencil_A {
 public:
    Pencil_Sepia() : Pencil_A("Sepia Pencil", "Sepia") {}
    ~Pencil_Sepia() override = default;

    std::vector<Pixel> use(int x, int y,
        [[maybe_unused]] const sf::Image &img) final;
};
}  // namespace MyGimp
