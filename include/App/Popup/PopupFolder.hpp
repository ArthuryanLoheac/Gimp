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

    std::string openPopup(const std::string& name, std::vector<std::string> _extensions, bool _isSelectFolder = true, bool _isSelectNameFile = true);

 private:
    void draw();
    void updatePaths();
    void handleInput(sf::Event &event);
    std::string getExtension(const std::string& filename);
    bool isGoodExtension(const std::string& filename);

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
    std::vector<std::string> extensions;
    bool open;
    float scrollOffset = 0.0f;
    const float separationY = 32.0f;
    bool isSelectFolder = true;
    bool isSelectNameFile = true;
};
}  // namespace MyGimp