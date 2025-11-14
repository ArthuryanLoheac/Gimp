#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

namespace MyGimp {
class Pencil_I {
 public:
    struct Pixel {
        int x;
        int y;
        sf::Color color;
    };

    Pencil_I() = default;
    virtual ~Pencil_I() = default;

    virtual void init(const int size, const sf::Color& color) = 0;
    virtual std::vector<Pixel> use(const int x,
        const int y, const sf::Image& img) = 0;
    virtual std::string getName() const = 0;
    virtual int getSize() const = 0;
    virtual void setSize(int size) = 0;
    virtual sf::Color getColor() const = 0;
    virtual void setColor(const sf::Color& color) = 0;
    virtual void setOpacity(int opacity) = 0;
    virtual int getOpacity() const = 0;
    virtual void clearPixelsPainted() = 0;
    virtual const std::vector<Pixel>& getPixelsPainted() const = 0;
    virtual void addPixelPainted(const Pixel& pixel) = 0;
    virtual bool isPixelinList(int x, int y) const = 0;
    virtual std::string getNameIcon() const = 0;
};
}  // namespace MyGimp
