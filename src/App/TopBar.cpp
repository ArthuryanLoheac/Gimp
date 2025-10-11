#include "App/TopBar.hpp"

namespace MyGimp {
TopBar::TopBar()
{
    background.setSize(sf::Vector2f(1920, 50));
    background.setFillColor(sf::Color(50, 50, 50, 200));
    background.setPosition(0, 0);
}

void TopBar::draw(sf::RenderWindow &window)
{
    window.draw(background);
}

void TopBar::handleInput(const sf::Event &event)
{
    // Handle top bar specific input here
}
}  // namespace MyGimp
