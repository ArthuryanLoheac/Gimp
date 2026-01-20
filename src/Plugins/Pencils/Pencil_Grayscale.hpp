#pragma once
#include <vector>
#include <string>

#include "App/Pencil/Pencil_A.hpp"

namespace MyGimp {
class Pencil_Grayscale final : public Pencil_A {
 public:
    Pencil_Grayscale() : Pencil_A("Grayscale Pencil", "Grayscale") {}
    ~Pencil_Grayscale() override = default;

    std::vector<Pixel> use(int x, int y,
        [[maybe_unused]] const sf::Image &img) final;
};
}  // namespace MyGimp
