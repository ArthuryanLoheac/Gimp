#pragma once
#include "Pencil_I.hpp"
#include <string>

namespace MyGimp {
class Pencil_A : public Pencil_I {
 public:
    Pencil_A(const std::string &name) : pencilName(name) {};
    ~Pencil_A() override = default;

    void init(const int size, const sf::Color& color) override {
      this->size = size;
      this->color = color;
    };
    int getSize() const override { return size; }
    void setSize(int newSize) override { size = newSize; }
    std::string getName() const override { return pencilName; }
    sf::Color getColor() const override { return color; }
    void setColor(const sf::Color& color) override { this->color = color; }

 protected:
    int size = 1;
    sf::Color color = {0, 0, 0, 255};
    std::string pencilName;

    sf::Color getPixelImage(const int x, const int y, const sf::Image& img);
};
}  // namespace MyGimp
