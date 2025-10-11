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

 private:
    std::string name;
    sf::Image image;

    sf::Texture texture;
    sf::Sprite sprite;
    bool visible = true;
};
}  // namespace MyGimp
