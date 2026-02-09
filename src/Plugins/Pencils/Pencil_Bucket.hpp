#pragma once
#include <vector>
#include <string>

#include "App/Pencil/Pencil_A.hpp"

namespace MyGimp {
class Pencil_Bucket final : public Pencil_A {
 public:
    Pencil_Bucket() : Pencil_A("Bucket Pencil", "Bucket") {}
    ~Pencil_Bucket() override = default;

    std::vector<Pixel> use(int x, int y,
        [[maybe_unused]] const sf::Image &img) final;
};
}  // namespace MyGimp
