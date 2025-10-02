#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

namespace MyGimp {
class Calque {
 public:
    Calque(const std::string& name) : name(name) {}
    ~Calque() = default;

    void createEmpty(int width, int height, sf::Color col = sf::Color::Transparent);
    void createFromFile(const std::string& filepath);

    void draw(sf::RenderWindow& window);

    // Getters and Setters
    void setVisible(bool isVisible);
    bool isVisible() const;
    const std::string& getName() const;
    sf::Image getImage() const;

 private:
    std::string name;
    sf::Image image;

    sf::Texture texture;
    sf::Sprite sprite;
    bool visible = true;
};
}  // namespace MyGimp
