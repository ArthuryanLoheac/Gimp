#pragma once
#include "Pencil_I.hpp"
#include <string>

namespace MyGimp {
class Pencil_A : public Pencil_I {
 public:
    Pencil_A(const std::string &name) : pencilName(name) {};
    ~Pencil_A() override = default;

    int getSize() const override { return size; }
    void setSize(int newSize) override { size = newSize; }
    std::string getName() const override { return pencilName; }
    Color getColor() const override { return color; }
    void setColor(const Color& color) override { this->color = color; }

 protected:
    int size = 1;
    Pencil_I::Color color = {0, 0, 0, 255};
    std::string pencilName;
};
}  // namespace MyGimp