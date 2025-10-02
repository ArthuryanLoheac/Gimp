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

    sf::Vector2u getDimensions() const;

    void init(int width, int height);
    void init(const std::string& filepath);
    void newCalque(const std::string& name, sf::Color col = sf::Color::Transparent);
    void newCalque(const std::string& name, const std::string& filepath);
 private:
    std::vector<Calque> calques;
    sf::Vector2u dimensions;
};
}  // namespace MyGimp