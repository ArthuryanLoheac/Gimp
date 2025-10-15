#include <criterion/criterion.h>
#include "App/DrawApp/DrawApp.hpp"

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

Test(DrawApp, delete_calque) {
    MyGimp::DrawApp app;
    app.init(800, 600);
    app.newCalque("Layer2", sf::Color::Green);
    cr_assert_eq(app.getCalques().size(), 2);
    bool deleted = app.deleteCalque(1);
    cr_assert_eq(deleted, true);
    cr_assert_eq(app.getCalques().size(), 1);
    // Ne doit pas supprimer le dernier calque
    deleted = app.deleteCalque(0);
    cr_assert_eq(deleted, false);
}

Test(DrawApp, move_calque_up_down) {
    MyGimp::DrawApp app;
    app.init(800, 600);
    app.newCalque("Layer2", sf::Color::Blue);
    app.setId(1);
    app.moveCalquePos(true); // up
    cr_assert_eq(app.getCalques()[0].getName(), "Layer2");
    cr_assert_eq(app.getCalques()[1].getName(), "Calque 1");
    app.moveCalquePos(false); // down
    cr_assert_eq(app.getCalques()[0].getName(), "Calque 1");
    cr_assert_eq(app.getCalques()[1].getName(), "Layer2");
}

Test(DrawApp, set_get_id) {
    MyGimp::DrawApp app;
    app.init(800, 600);
    app.newCalque("Layer2", sf::Color::Yellow);
    app.setId(1);
    cr_assert_eq(app.getCalques()[app.getCalques().size()-1].getName(), "Layer2");
}

Test(DrawApp, save_export_file_mock) {
    MyGimp::DrawApp app;
    app.init(800, 600);
    // On vérifie que les fonctions ne crashent pas (mock)
    app.saveFile();
    cr_assert(true);
}