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
    void update(float deltaTime);
    void handleInput();

    sf::Vector2i getDimensions() const;

    void newCalque(const std::string& name, int width, int height);
    void newCalque(const std::string& name, const std::string& filepath);
 private:
    std::vector<Calque> calques;
    sf::Vector2i dimensions;
};
}  // namespace MyGimp