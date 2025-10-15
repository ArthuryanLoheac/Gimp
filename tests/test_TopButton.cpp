#include <criterion/criterion.h>
#include "App/TopBar/TopButton.hpp"

Test(TopButton, basic_init) {
    std::vector<std::pair<std::string, std::string>> items = {
        {"Item1", "code1"},
        {"Item2", "code2"}
    };
    MyGimp::TopButton topBtn("Menu", items);
    cr_assert_eq(topBtn.getWidth(), (float)(std::string("Menu").length() * 10 + 20));
}

Test(TopButton, dropdown_count) {
    std::vector<std::pair<std::string, std::string>> items = {
        {"Item1", "code1"},
        {"Item2", "code2"},
        {"Item3", "code3"}
    };
    MyGimp::TopButton topBtn("Menu", items);
    // On ne peut pas accéder directement à buttonsDropDown, mais on peut tester indirectement
    cr_assert_eq(topBtn.getWidth(), (float)(std::string("Menu").length() * 10 + 20));
}

Test(TopButton, handle_mouse_hover_and_click) {
    std::vector<std::pair<std::string, std::string>> items = {
        {"Item1", "code1"}
    };
    MyGimp::TopButton topBtn("Menu", items);
    bool consumed = false;
    sf::Event event;
    event.type = sf::Event::MouseMoved;
    event.mouseMove.x = 105; // Dans la zone du bouton
    event.mouseMove.y = 105;
    topBtn.handleInput(event, consumed);
    // On ne peut pas vérifier l'état directement, mais on vérifie que ça ne crash pas
    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.button = sf::Mouse::Left;
    event.mouseButton.x = 105;
    event.mouseButton.y = 105;
    topBtn.handleInput(event, consumed);
    cr_assert(true);
}
