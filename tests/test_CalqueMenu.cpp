#include <criterion/criterion.h>
#include "App/CalqueMenu/CalqueMenu.hpp"

Test(CalqueMenu, basic_init) {
    MyGimp::CalqueMenu menu;
    cr_assert(true); // Construction ne doit pas crasher
}

Test(CalqueMenu, update_and_buttons) {
    MyGimp::CalqueMenu menu;
    std::vector<MyGimp::Calque> calques;
    calques.emplace_back("Layer1");
    calques.emplace_back("Layer2");
    menu.update(calques, 1);
    cr_assert(true); // update ne doit pas crasher
}

Test(CalqueMenu, handle_input_mock) {
    MyGimp::CalqueMenu menu;
    bool consumed = false;
    sf::Event event;
    event.type = sf::Event::MouseMoved;
    event.mouseMove.x = 5;
    event.mouseMove.y = 5;
    std::string code = menu.handleInput(event, consumed);
    cr_assert(code == "" || code == "add_calque" || code == "delete_calque");
}
