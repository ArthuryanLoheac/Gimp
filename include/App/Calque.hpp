#pragma once
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace MyGimp {
class Calque {
 public:
    explicit Calque(const std::string& name) : name(name) {}
    ~Calque() = default;

    void createEmpty(int width, int height,
        sf::Color col = sf::Color::Transparent);
    void createFromFile(const std::string& filepath);

    void draw(sf::RenderWindow& window, float zoom, sf::Vector2f pos);

    // Getters and Setters
    void setVisible(bool isVisible);
    bool isVisible() const;
    const std::string& getName() const;
    const sf::Image& getImage() const;
    float getOpacity() const;
    void setOpacity(float opacity);

    // Painting methods
    void startPainting();
    void continuePainting(const sf::Vector2f& position);
    void stopPainting();
    bool isPainting() const;

 private:
    float opacity = 1.0f;
    std::string name;
    sf::Image image;

    sf::Texture texture;
    sf::Sprite sprite;
    bool visible = true;

    bool painting = false;
    sf::Vector2f lastPaintPos;
};
}  // namespace MyGimp
