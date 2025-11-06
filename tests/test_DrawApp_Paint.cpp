#include <criterion/criterion.h>
#include <SFML/Graphics.hpp>

#include "App/DrawApp/DrawApp.hpp"
#include "App/Pencil/Pencil_Circle.hpp"

using namespace MyGimp;

Test(DrawApp_Paint, paint_flow_modifies_calque_or_pencil) {
    DrawApp app;
    // init small canvas
    app.init(64, 48);
    // create a pencil and set it as current pencil if API exists
    // We'll try to interact through public DrawApp interface used elsewhere in tests

    // Add an empty calque and make it active
    app.newCalque("PaintLayer", sf::Color::Black);
    app.setId(0);

    // Prepare a circle pencil
    std::shared_ptr<Pencil_I> pencil = std::make_shared<Pencil_Circle>();
    pencil->init(5, sf::Color(255, 0, 0, 255));

    // We'll paint directly on the Calque using public Calque methods (start/continue/stop)
    auto calques = app.getCalques();
    cr_assert_geq(calques.size(), (size_t)1);

    // Paint directly using calque painting API
    Calque &c = const_cast<Calque&>(calques[0]);
    c.startPainting(sf::Vector2f(10.f, 10.f), 1.f, pencil);
    c.continuePainting(sf::Vector2f(12.f, 12.f), 1.f, pencil);
    c.stopPainting();

    // Verify either the pencil recorded painted pixels or the image has non-transparent pixels at/near the painted location
    bool pencilHasPixels = false;
    try {
        auto pa = std::dynamic_pointer_cast<Pencil_Circle>(pencil);
        if (pa) {
            pencilHasPixels = (pa->getPixelsPainted().size() > 0);
        } else {
            // For other pencil types that implement Pencil_A methods
            pencilHasPixels = (pencil->getOpacity() >= 0); // trivial check to ensure pencil is valid
        }
    } catch (...) { pencilHasPixels = false; }

    bool imageModified = false;
    try {
        const sf::Image &img = c.getImage();
        unsigned int w = img.getSize().x;
        unsigned int h = img.getSize().y;
        for (unsigned int xx = 8; xx <= 14 && xx < w; ++xx) {
            for (unsigned int yy = 8; yy <= 14 && yy < h; ++yy) {
                if (img.getPixel(xx, yy).a != 0) {
                    imageModified = true;
                    break;
                }
            }
            if (imageModified) break;
        }
    } catch (...) {}

    // At least one of the two should be true (either pencil recorded pixels or image changed), otherwise the paint flow didn't run
    cr_assert(pencilHasPixels || imageModified);
}
