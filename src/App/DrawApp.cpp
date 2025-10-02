#include "App/DrawApp.hpp"
#include "Logger.h"

namespace MyGimp {
void DrawApp::draw(sf::RenderWindow& window) {
    for (auto &calque : calques) {
        calque.draw(window);
    }
}

void DrawApp::update(float deltaTime) {
    // Update logic here
}

void DrawApp::handleInput() {
    // Input handling logic here
}

sf::Vector2i DrawApp::getDimensions() const {
    return dimensions;
}

void DrawApp::newCalque(const std::string& name, int width, int height) {
    calques.emplace_back(name);
    calques.back().createEmpty(width, height, sf::Color::White);
}

void DrawApp::newCalque(const std::string& name, const std::string& filepath) {
    calques.emplace_back(name);
    calques.back().createFromFile(filepath);
}

}  // namespace MyGimp