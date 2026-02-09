#pragma once
#include <vector>
#include <string>

#include "App/Pencil/Pencil_A.hpp"

namespace MyGimp {
class Pencil_Brightness final : public Pencil_A {
 public:
    Pencil_Brightness() : Pencil_A("Brightness Pencil", "Brightness") {}
    ~Pencil_Brightness() override = default;

    std::vector<Pixel> use(int x, int y,
        [[maybe_unused]] const sf::Image &img) final;
};
}  // namespace MyGimp
