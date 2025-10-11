#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "App/Calque.hpp"


namespace MyGimp {
class DrawApp {
 public:
    ~DrawApp() = default;

    void draw(sf::RenderWindow &);
    void update(float deltaTime, sf::RenderWindow& window);
    void handleInput(sf::Event &event);

    sf::Vector2u getDimensions() const;

    void init(int width, int height);
    void init(const std::string& filepath);
    void newCalque(const std::string& name,
        sf::Color col = sf::Color::Transparent);
    void newCalque(const std::string& name, const std::string& filepath);
    std::vector<Calque>& getCalques();

    bool isDragging() const { return dragging; }

 private:
    std::vector<Calque> calques;
    sf::Vector2u dimensions;
    float zoom = 1.0f;
    sf::Vector2f viewOffset = {0.0f, 0.0f};
    bool dragging = false;
    sf::Vector2i lastMousePos;

    void handleDragging(sf::Event &event);
    void handleZooming(sf::Event &event);

    void saveFile();
    void exportFile();
    void mixCalqueForExport(sf::Image &exportedImage, const Calque &c,
        const sf::Vector2u dimensionstoCopy);
};
}  // namespace MyGimp
