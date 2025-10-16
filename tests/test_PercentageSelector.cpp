#include <criterion/criterion.h>
#include "App/CalqueMenu/PercentageSelector.hpp"

namespace MyGimp {
Test(PercentageSelector, test_init) {
    PercentageSelector ps("opacity");
    cr_assert_eq(ps.getPercentage(), 100);
}

Test(PercentageSelector, test_change_value) {
    PercentageSelector ps("opacity");
    ps.setPercentage(75);
    cr_assert_eq(ps.getPercentage(), 75);
    ps.setPercentage(0);
    cr_assert_eq(ps.getPercentage(), 0);
    ps.setPercentage(150); // should clamp to 100
    cr_assert_eq(ps.getPercentage(), 100);
}

Test(PercentageSelector, test_selection) {
    PercentageSelector ps("opacity");
    cr_assert_eq(ps.isSelected(), false);
    ps.setSelected(true);
    cr_assert_eq(ps.isSelected(), true);
    ps.setSelected(false);
    cr_assert_eq(ps.isSelected(), false);
}

Test(PercentageSelector, test_input_handling_click) {
    PercentageSelector ps("opacity");
    bool consumed = false;

    // Simulate clicking on the text to select
    sf::Event clickEvent;
    clickEvent.type = sf::Event::MouseButtonPressed;
    clickEvent.mouseButton.button = sf::Mouse::Left;
    clickEvent.mouseButton.x = 50; // Assuming text is at (45, 5) with width < 50
    clickEvent.mouseButton.y = 10; // Assuming text is at (45, 5) with height > 10
    ps.setPosition(0, 0);
    ps.handleInput(clickEvent, consumed);
    cr_assert_eq(ps.isSelected(), true);
    cr_assert_eq(consumed, true);
}

Test(PercentageSelector, test_input_handling_declick) {
    PercentageSelector ps("opacity");
    ps.setSelected(true);
    bool consumed = false;

    // Simulate clicking on the text to select
    sf::Event clickEvent;
    clickEvent.type = sf::Event::MouseButtonPressed;
    clickEvent.mouseButton.button = sf::Mouse::Left;
    clickEvent.mouseButton.x = 500;
    clickEvent.mouseButton.y = 10;
    ps.setPosition(0, 0);
    ps.handleInput(clickEvent, consumed);
    cr_assert_eq(ps.isSelected(), false);
    cr_assert_eq(consumed, false);
}

static std::string test_input_text_handling_typing(
    PercentageSelector &ps,
    sf::Uint32 input
) {
    bool consumed = false;

    sf::Event typeEvent;
    typeEvent.type = sf::Event::TextEntered;
    typeEvent.text.unicode = input;
    std::string result = ps.handleInput(typeEvent, consumed);
    return result;
}
Test(PercentageSelector, test_input_text_handling_typing) {
    PercentageSelector ps("opacity");
    ps.setSelected(true);
    std::string result;

    result = test_input_text_handling_typing(ps, '5');
    cr_assert_eq(result, "opacity_input_100");
    result = test_input_text_handling_typing(ps, 8);
    cr_assert_eq(result, "opacity_input_10");
    result = test_input_text_handling_typing(ps, 8);
    cr_assert_eq(result, "opacity_input_1");
    result = test_input_text_handling_typing(ps, 8);
    cr_assert_eq(result, "opacity_input_0");
    result = test_input_text_handling_typing(ps, '4');
    cr_assert_eq(result, "opacity_input_4");
    result = test_input_text_handling_typing(ps, '5');
    cr_assert_eq(result, "opacity_input_45");
    result = test_input_text_handling_typing(ps, '5');
    cr_assert_eq(result, "opacity_input_455");
    result = test_input_text_handling_typing(ps, '5');
    cr_assert_eq(result, "opacity_input_455");
}

Test(PercentageSelector, test_input_text_handling_consumed) {
    PercentageSelector ps("opacity");
    ps.setSelected(true);

    bool consumed = false;
    sf::Event typeEvent;
    typeEvent.type = sf::Event::TextEntered;
    typeEvent.text.unicode = 8;
    std::string result = ps.handleInput(typeEvent, consumed);
    cr_assert_eq(result, "opacity_input_10");
    typeEvent.text.unicode = 8;
    result = ps.handleInput(typeEvent, consumed);
    cr_assert_eq(result, "");
}
}  // namespace MyGimp
