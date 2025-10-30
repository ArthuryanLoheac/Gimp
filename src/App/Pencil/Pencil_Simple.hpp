#pragma once
#include <vector>
#include <string>
#include "Pencil_A.hpp"

namespace MyGimp {
class Pencil_Simple final : public Pencil_A {
 public:
    Pencil_Simple() : Pencil_A("Simple Pencil") {};
    ~Pencil_Simple() override = default;

    std::vector<Pixel> use(int x, int y, [[maybe_unused]] const sf::Image &img) final;
};
}  // namespace MyGimp
