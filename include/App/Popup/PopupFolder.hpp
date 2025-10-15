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
    std::string nameFile;
    std::string selectedPath;
    sf::Text title;
    sf::Text nameFileText;
    sf::Font font;
    std::vector<std::shared_ptr<Button>> options;
    sf::RectangleShape backgroundTop;
    sf::RectangleShape backgroundBottom;
    sf::RectangleShape nameFileField;
    sf::RectangleShape cursorIndicator;
    sf::Clock cursorClock;
    bool open;
    float scrollOffset = 0.0f;
    const float separationY = 32.0f;
};
}  // namespace MyGimp