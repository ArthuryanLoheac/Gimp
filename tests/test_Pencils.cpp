#include <criterion/criterion.h>
#include <SFML/Graphics.hpp>

#include "App/Pencil/Pencil_A.hpp"
#include "Pencil_Circle.hpp"
#include "Pencil_Square.hpp"

using namespace MyGimp;

Test(Pencil, basic_init_and_setters) {
    Pencil_Square p;
    p.init(3, sf::Color(10, 20, 30, 200));
    cr_assert_eq(p.getSize(), 3);
    cr_assert_eq(p.getColor().r, 10);
    cr_assert_eq(p.getColor().g, 20);
    cr_assert_eq(p.getColor().b, 30);
    cr_assert_eq(p.getOpacity(), 200);

    p.setSize(5);
    cr_assert_eq(p.getSize(), 5);

    p.setColor(sf::Color(1,2,3,4));
    cr_assert_eq(p.getColor().r, 1);
    // Pencil_A::setColor preserves the previous alpha value; ensure it stayed 200
    cr_assert_eq(p.getColor().a, 200);
}

Test(Pencil, opacity_clamping) {
    Pencil_Square p2;
    p2.setOpacity(-10);
    cr_assert_eq(p2.getOpacity(), 0);
    p2.setOpacity(300);
    cr_assert_eq(p2.getOpacity(), 255);
}

Test(Pencil, pixels_painted_list) {
    Pencil_Square p3;
    p3.clearPixelsPainted();
    Pencil_I::Pixel pix{10, 20, sf::Color::Red};
    p3.addPixelPainted(pix);
    cr_assert(p3.isPixelinList(10, 20));
    cr_assert_eq(p3.getPixelsPainted().size(), (size_t)1);
    p3.clearPixelsPainted();
    cr_assert_eq(p3.getPixelsPainted().size(), (size_t)0);
}

Test(Pencil, circle_and_square_use_area) {
    Pencil_Circle pc;
    pc.init(5, sf::Color::White);
    // For size 5 (halfSize=2) the circle approx area should be > 0 and less than square
    auto circlePixels = pc.use(50, 50, sf::Image());
    Pencil_Square psq;
    psq.init(5, sf::Color::White);
    auto squarePixels = psq.use(50, 50, sf::Image());

    cr_assert(circlePixels.size() > 0);
    cr_assert(squarePixels.size() >= circlePixels.size());

    // Check pixel positions relative to center
    bool foundCenterInSquare = false;
    for (auto &p : squarePixels) {
        if (p.x == 50 && p.y == 50) {
            foundCenterInSquare = true;
            break;
        }
    }
    cr_assert(foundCenterInSquare);
}

Test(Pencil, get_pixel_image_bounds) {
    Pencil_Square p;
    sf::Image img;
    img.create(2, 2, sf::Color::Green);

    // inside bounds
    sf::Color c = p.getPixelImage(1, 1, img);
    cr_assert_eq(c, sf::Color::Green);

    // out of bounds negative
    sf::Color c2 = p.getPixelImage(-1, 0, img);
    cr_assert_eq(c2, sf::Color(0,0,0,0));

    // out of bounds too large
    sf::Color c3 = p.getPixelImage(2, 2, img);
    cr_assert_eq(c3, sf::Color(0,0,0,0));
}
