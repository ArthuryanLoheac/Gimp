#include <criterion/criterion.h>
#include "App/DrawApp.hpp"

Test(DrawApp, init_with_dimensions) {
    MyGimp::DrawApp app;
    app.init(800, 600);
    cr_assert_eq(app.getDimensions().x, 800);
    cr_assert_eq(app.getDimensions().y, 600);
    cr_assert_eq(app.getCalques().size(), 1);
    cr_assert_eq(app.getCalques()[0].getName(), "Calque 1");
}

Test(DrawApp, init_with_file) {
    MyGimp::DrawApp app;
    app.init("tests/Images/Img.jpg");
    cr_assert_eq(app.getDimensions().x, 612);
    cr_assert_eq(app.getDimensions().y, 408);
    cr_assert_eq(app.getCalques().size(), 1);
    cr_assert_eq(app.getCalques()[0].getName(), "Calque 1");
}

Test(DrawApp, add_empty_calque) {
    MyGimp::DrawApp app;
    app.init(800, 600);
    app.newCalque("EmptyLayer", sf::Color::Red);
    cr_assert_eq(app.getCalques().size(), 2);
    cr_assert_eq(app.getCalques()[1].getName(), "EmptyLayer");
    cr_assert_eq(app.getCalques()[1].getImage().getSize().x, 800);
    cr_assert_eq(app.getCalques()[1].getImage().getSize().y, 600);
}

Test(DrawApp, add_file_calque) {
    MyGimp::DrawApp app;
    app.init(800, 600);
    app.newCalque("FileLayer", "tests/Images/Img.jpg");
    cr_assert_eq(app.getCalques().size(), 2);
    cr_assert_eq(app.getCalques()[1].getName(), "FileLayer");
    cr_assert_eq(app.getCalques()[1].getImage().getSize().x, 612);
    cr_assert_eq(app.getCalques()[1].getImage().getSize().y, 408);
}