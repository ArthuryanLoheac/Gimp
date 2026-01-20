#pragma once
#include <string>
#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>
#include "App/Pencil/Pencil_I.hpp"

namespace MyGimp {
class Calque {
 public:
    explicit Calque(const std::string& name) : name(name) {}
    ~Calque() = default;

    void createEmpty(int width, int height,
        sf::Color col = sf::Color::Transparent);
    void createFromFile(const std::string& filepath);
    void copyCalque(const Calque& other);

    void draw(sf::RenderWindow& window, float zoom, sf::Vector2f pos);

    // Getters and Setters
    void setVisible(bool isVisible);
    bool isVisible() const;
    const std::string& getName() const;
    const sf::Image& getImage() const;
    float getOpacity() const;
    void setOpacity(float opacity);

    // Painting methods
    void startPainting(const sf::Vector2f& position, float zoom,
        std::shared_ptr<Pencil_I> pencil, bool erase = false);
    void continuePainting(const sf::Vector2f& position, float zoom = 1.f,
        std::shared_ptr<Pencil_I> pencil = nullptr);
    void stopPainting();
    bool isPainting() const;
    const sf::Color pipetteAt(const sf::Vector2f& position, float zoom) const;

    void paintAt(const sf::Vector2f& position, float zoom,
        std::shared_ptr<Pencil_I> pencil, bool erase = false);

    // private getter
    float getCalqueOpacity() const { return opacity; }
    std::string getCalqueName() const { return name; }
    sf::Image getCalqueImage() const { return image; }
    sf::Texture getCalqueTexture() const { return texture; }
    sf::Sprite getCalqueSprite() const { return sprite; }
    bool getCalqueVisible() const { return visible; }
    bool getCalquePainting() const { return painting; }
    bool getCalqueIsErasing() const { return isErasing; }
    sf::Vector2f getCalqueLastPaintPos() const { return lastPaintPos; }
    // Image setter for loading from a project
    void setImage(const sf::Image& img);

 private:
    void paintOnePixel(const Pencil_I::Pixel pixel, bool erase = false);

    float opacity = 1.0f;
    std::string name;
    sf::Image image;

    sf::Texture texture;
    sf::Sprite sprite;
    bool visible = true;

    // Performance optimizations
    bool imageDirty = false; // set when image pixels changed
    sf::Clock textureUpdateClock;
    sf::Time textureUpdateInterval = sf::milliseconds(30);

    bool painting = false;
    bool isErasing = false;
    sf::Vector2f lastPaintPos;
};
}  // namespace MyGimp
