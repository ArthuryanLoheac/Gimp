#include "PencilMenu.hpp"
#include "App/const.hpp"
#include "App/Pencil/Pencil_I.hpp"
#include <memory>
#include <string>

namespace MyGimp {
PencilMenu::PencilMenu()
{
    background = sf::RectangleShape(sf::Vector2f(
        static_cast<float>(250),
        static_cast<float>(200)));
    background.setPosition(WIDTH - 250, HEIGHT - 500);
    background.setFillColor(sf::Color(50, 50, 50, 200));
    sizeSelector.setTitle("Size:");
    colorPicker.setPosition(WIDTH - 240.f, HEIGHT - 490.f);
    sizeSelector.setPosition(WIDTH - 215.f, HEIGHT - 335.f);
    opacitySelector.setTitle("Opacity:");
    opacitySelector.setPosition(WIDTH - 75.f, HEIGHT - 335.f);
}

void PencilMenu::draw(sf::RenderWindow &window)
{
    window.draw(background);
    sizeSelector.draw(window);
    colorPicker.draw(window);
    opacitySelector.draw(window);
}

std::string PencilMenu::handleInput(sf::Event &event, bool &consumed,
std::shared_ptr<Pencil_I> &currentPencil)
{
    sf::Color pickedColor = colorPicker.handleInput(event);
    if (pickedColor != sf::Color::Transparent) {
        currentPencil->setColor(pickedColor);
        consumed = true;
    }
    if (event.type == sf::Event::MouseWheelScrolled && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !consumed) {
        int newSize = currentPencil->getSize() +
            static_cast<int>(event.mouseWheelScroll.delta);
        newSize = std::clamp(newSize, 1, 999);
        currentPencil->setSize(newSize);
        sizeSelector.setPercentage(newSize);
        consumed = true;
    }
    std::string returnValue = opacitySelector.handleInput(event, consumed);
    if (!returnValue.empty())
        return returnValue;
    return sizeSelector.handleInput(event, consumed);
}
}  // namespace MyGimp
