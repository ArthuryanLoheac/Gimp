#include <criterion/criterion.h>
#include <SFML/Graphics.hpp>

#include "App/PencilMenu/PencilMenu.hpp"
#include "Pencil_Square.hpp"

using namespace MyGimp;

Test(PencilMenu, handle_input_mouse_move_noop) {
    PencilMenu menu;
    bool consumed = false;
    sf::Event event;
    event.type = sf::Event::MouseMoved;
    event.mouseMove.x = 5;
    event.mouseMove.y = 5;

    std::shared_ptr<Pencil_I> pencil = std::make_shared<Pencil_Square>();
    pencil->init(3, sf::Color::White);

    std::string code = menu.handleInput(event, consumed, pencil);
    cr_assert_eq(code, "");
    cr_assert_eq(consumed, false);
}
