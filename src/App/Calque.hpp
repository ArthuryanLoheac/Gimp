#pragma once
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>

#include "App/Pencil/Pencil_I.hpp"

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
    void startPainting(const sf::Vector2f& position, float zoom, std::shared_ptr<Pencil_I> pencil);
    void continuePainting(const sf::Vector2f& position, float zoom = 1.f, std::shared_ptr<Pencil_I> pencil = nullptr);
    void stopPainting();
    bool isPainting() const;

    void paintAt(const sf::Vector2f& position, float zoom, std::shared_ptr<Pencil_I> pencil);

 private:
    void paintOnePixel(const Pencil_I::Pixel pixel);

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
