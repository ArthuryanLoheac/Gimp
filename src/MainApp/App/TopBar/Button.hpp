#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>

namespace MyGimp {
class Button {
 public:
    enum stateButton { HIDE, IDLE, HOVER, ACTIVE };

    explicit Button(std::string title,
       std::string code = "", int widthForced = 200);
    Button() = default;
    ~Button() = default;
    void draw(sf::RenderWindow &window);
    std::string handleInput(const sf::Event &event, bool &consumed);

    void init(std::string title, std::string code = "", int widthForced = 200);
    void initIcon(const std::string &iconPath,
      std::string code = "", int iconSize = 20);
    // Getters
    void setPosition(float x, float y);

    stateButton getState() const;
    void setState(stateButton state);

    float getHeight() const;
    void setHeight(float height);
    float getWidth() const;
    void setWidth(float width);
    void setDeltaPosText(float x, float y);
    void setSize(float width, float height);

    std::string getCode() const;

    std::string getTitle() const;
    void setTitle(const std::string &title);

    sf::Color getColor() const;
    void setColor(const sf::Color &color, stateButton state = IDLE);

    void setIcon(const std::string &iconPath, int iconSize = 20);

 private:
    sf::Vector2f deltaPosText = {0, 0};
    sf::Vector2f position = {0, 0};

    sf::RectangleShape background;
    sf::Text text;
    sf::Font font;
    stateButton currentState;
    std::string code;
    sf::Texture iconTexture;
    sf::Sprite icon;

    sf::Color idleColor = sf::Color(70, 70, 70);
    sf::Color hoverColor = sf::Color(90, 90, 90);
    sf::Color activeColor = sf::Color(110, 110, 110);
};
}  // namespace MyGimp
