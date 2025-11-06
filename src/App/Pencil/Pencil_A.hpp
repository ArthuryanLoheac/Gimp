#pragma once
#include <string>
#include <vector>

#include "App/Pencil/Pencil_I.hpp"

namespace MyGimp {
class Pencil_A : public Pencil_I {
 public:
    explicit Pencil_A(const std::string &name) : pencilName(name) {}
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
    void setOpacity(int opacity) override;
    int getOpacity() const override { return color.a; }
    void clearPixelsPainted() override;
    const std::vector<Pixel>& getPixelsPainted() const override;
    void addPixelPainted(const Pixel& pixel) override;
    bool isPixelinList(int x, int y) const override;

 protected:
    int size = 1;
    sf::Color color = {0, 0, 0, 255};
    std::string pencilName;
    std::vector<Pixel> pixelsPainted;

    sf::Color getPixelImage(const int x, const int y, const sf::Image& img);
};
}  // namespace MyGimp
