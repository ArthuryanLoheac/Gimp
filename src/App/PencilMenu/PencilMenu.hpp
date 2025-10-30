#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "App/ColorPicker/ColorPicker.hpp"
#include "App/CalqueMenu/PercentageSelector.hpp"
#include "App/Pencil/Pencil_I.hpp"

namespace MyGimp {
class PencilMenu {
 public:
    PencilMenu();
    ~PencilMenu() = default;

    void draw(sf::RenderWindow &window);
    std::string handleInput(sf::Event &event, bool &consumed, std::shared_ptr<Pencil_I> &currentPencil);
    PercentageSelector& getSizeSelector() { return sizeSelector; }
 private:
    PercentageSelector sizeSelector{"size_selector", false};
    sf::RectangleShape background;
    ColorPicker colorPicker;
};

}  // namespace MyGimp