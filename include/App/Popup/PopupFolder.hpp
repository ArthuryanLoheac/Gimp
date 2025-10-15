#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "App/TopBar/Button.hpp"
#include <memory>

namespace MyGimp {
class PopupFolder
{
 public:
    PopupFolder() = default;
    ~PopupFolder() = default;

    std::string openPopup(const std::string& name);

 private:
    void draw();
    void updatePaths();
    void handleInput(sf::Event &event);

    Button buttonValidate;
    sf::RenderWindow window;
    std::string name;
    std::string selectedPath;
    sf::Text title;
    sf::Font font;
    std::vector<std::shared_ptr<Button>> options;
    sf::RectangleShape backgroundTop;
    sf::RectangleShape backgroundBottom;
    bool open;
    float scrollOffset = 0.0f;
    const float separationY = 32.0f;
};
}  // namespace MyGimp