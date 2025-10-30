#pragma once
#include <vector>
#include <string>

namespace MyGimp {
class Pencil_I {
 public:
    struct Color {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };

    struct Pixel {
        int x;
        int y;
        Color color;
    };

    Pencil_I() = default;
    virtual ~Pencil_I() = default;

    virtual std::vector<Pixel> use(const int x, const int y) = 0;
    virtual std::string getName() const = 0;
    virtual int getSize() const = 0;
    virtual void setSize(int size) = 0;
    virtual Color getColor() const = 0;
    virtual void setColor(const Color& color) = 0;
};
}  // namespace MyGimp
