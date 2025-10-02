#include <criterion/criterion.h>
#include <string.h>

#include "App/Calque.hpp"

Test(Calques, get_name) {
    MyGimp::Calque calque("TestLayer");
    cr_assert_eq(calque.getName(), "TestLayer");
}

Test(Calques, visibility_toggle) {
    MyGimp::Calque calque("VisibilityLayer");
    cr_assert_eq(calque.isVisible(), true);
    calque.setVisible(false);
    cr_assert_eq(calque.isVisible(), false);
    calque.setVisible(true);
    cr_assert_eq(calque.isVisible(), true);
}

Test(Calques, basic_creation) {
    MyGimp::Calque calque("BasicLayer");
    cr_assert_eq(calque.getImage().getSize().x, 0);
    cr_assert_eq(calque.getImage().getSize().y, 0);
}

Test(Calques, create_empty) {
    MyGimp::Calque calque("EmptyLayer");
    calque.createEmpty(100, 100);
    cr_assert_eq(calque.getImage().getSize().x, 100);
    cr_assert_eq(calque.getImage().getSize().y, 100);
}

Test(Calques, create_from_file) {
    MyGimp::Calque calque("FileLayer");
    calque.createFromFile("tests/Images/Img.jpg");
    cr_assert_eq(calque.getImage().getSize().x, 612);
    cr_assert_eq(calque.getImage().getSize().y, 408);
}