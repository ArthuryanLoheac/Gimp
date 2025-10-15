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

    std::string openPopup(const std::string& name,
      std::vector<std::string> _extensions,
      bool _isSelectFolder = true,
      bool _isSelectNameFile = true);
    bool isGoodExtension(const std::string& filename);
    std::string getExtension(const std::string& filename);
    void setExtensions(const std::vector<std::string>& exts);

 private:
    void init(const std::string& name);
    bool run();
    std::string returnPath();
    void draw();
    void updatePaths();
    void handleInput(sf::Event &event);
    void setupRectangle(sf::RectangleShape &rect,
        float x, float y, float width, float height, sf::Color color);
    void setupText(sf::Text &text,
        const std::string &str, float x, float y, unsigned int size,
        sf::Color color);

    Button buttonValidate;
    sf::RenderWindow window;
    std::string name, nameFile, selectedPath;
    sf::Text title, nameFileText;
    sf::Font font;
    std::vector<std::shared_ptr<Button>> options;
    sf::RectangleShape backgroundTop, backgroundBottom;
    sf::RectangleShape nameFileField;
    sf::RectangleShape cursorIndicator;
    sf::Clock cursorClock;
    std::vector<std::string> extensions;
    float scrollOffset = 0.0f;
    const float separationY = 32.0f;
    bool isSelectFolder = true;
    bool isSelectNameFile = true;
};
}  // namespace MyGimp