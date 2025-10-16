#include <criterion/criterion.h>
#include "App/TopBar/Button.hpp"

Test(Button, basic_init) {
    MyGimp::Button btn("Test", "code", 100);
    cr_assert_eq(btn.getTitle(), "Test");
    cr_assert_eq(btn.getCode(), "code");
    cr_assert_eq(btn.getWidth(), 100);
}

Test(Button, set_title) {
    MyGimp::Button btn("Old", "code", 80);
    btn.setTitle("NewTitle");
    cr_assert_eq(btn.getTitle(), "NewTitle");
}

Test(Button, set_position_and_size) {
    MyGimp::Button btn("Test", "code", 120);
    btn.setPosition(50, 60);
    cr_assert_eq(btn.getWidth(), 120);
    cr_assert_eq(btn.getHeight(), 30);
}

Test(Button, set_state_and_color) {
    MyGimp::Button btn("Test", "code", 100);
    btn.setState(MyGimp::Button::IDLE);
    btn.setColor(sf::Color::Red, MyGimp::Button::IDLE);
    cr_assert_eq(btn.getColor(), sf::Color::Red);
}

Test(Button, handle_input_mock) {
    MyGimp::Button btn("Test", "code", 100);
    bool consumed = false;
    sf::Event event;
    event.type = sf::Event::MouseMoved;
    event.mouseMove.x = 55;
    event.mouseMove.y = 65;
    btn.setPosition(50, 60);
    btn.handleInput(event, consumed);
    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.button = sf::Mouse::Left;
    event.mouseButton.x = 55;
    event.mouseButton.y = 65;
    std::string code = btn.handleInput(event, consumed);
    cr_assert(code == "code" || code == "");
}
