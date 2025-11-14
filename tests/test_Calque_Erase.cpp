#include <criterion/criterion.h>
#include <SFML/Graphics.hpp>

#include "App/Calque.hpp"
#include "Pencil_Square.hpp"

using namespace MyGimp;

Test(Calque, paint_then_erase_full_opacity) {
    Calque cal("EraseLayer");
    cal.createEmpty(10, 10, sf::Color::Transparent);

    auto pencil = std::make_shared<Pencil_Square>();
    pencil->init(3, sf::Color(255, 0, 0, 255));

    // Paint at center
    cal.startPainting(sf::Vector2f(5.f, 5.f), 1.f, pencil, false);
    cal.stopPainting();

    sf::Color painted = cal.getImage().getPixel(5, 5);
    cr_assert_neq(painted.a, 0);

    // Erase at same center with full-opacity pencil -> should become fully transparent
    pencil->clearPixelsPainted();
    cal.startPainting(sf::Vector2f(5.f, 5.f), 1.f, pencil, true);
    cal.stopPainting();

    sf::Color afterErase = cal.getImage().getPixel(5, 5);
    cr_assert_eq(afterErase.a, 0);
}

Test(Calque, erase_partial_opacity_reduces_alpha) {
    Calque cal("EraseLayer2");
    // Start with an opaque white image
    cal.createEmpty(8, 8, sf::Color(255, 255, 255, 255));

    auto pencil = std::make_shared<Pencil_Square>();
    // Use a half-opacity pencil for erasing
    pencil->init(3, sf::Color(0, 0, 0, 128));

    // Erase a pixel
    cal.startPainting(sf::Vector2f(3.f, 3.f), 1.f, pencil, true);
    cal.stopPainting();

    sf::Color after = cal.getImage().getPixel(3, 3);
    // Alpha should be reduced but not zero when erasing with partial opacity
    cr_assert(after.a < 255);
    cr_assert(after.a > 0);
}
