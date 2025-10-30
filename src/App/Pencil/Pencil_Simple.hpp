#pragma once
#include <vector>
#include <string>
#include "Pencil_A.hpp"

namespace MyGimp {
class Pencil_Simple : public Pencil_A {
 public:
    Pencil_Simple() : Pencil_A("Simple Pencil") {};
    ~Pencil_Simple() override = default;

    std::vector<Pixel> use(int x, int y) override;
};
}  // namespace MyGimp