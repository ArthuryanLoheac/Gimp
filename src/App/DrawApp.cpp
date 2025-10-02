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

sf::Vector2u DrawApp::getDimensions() const {
    return dimensions;
}

void DrawApp::init(int width, int height) {
    calques.clear();
    dimensions = sf::Vector2u(width, height);
    newCalque("Calque 1");
}

void DrawApp::init(const std::string& filepath) {
    calques.clear();
    calques.emplace_back("Calque 1");
    calques.back().createFromFile(filepath);
    dimensions = calques.back().getImage().getSize();
}

void DrawApp::newCalque(const std::string& name, sf::Color col) {
    calques.emplace_back(name);
    calques.back().createEmpty(dimensions.x, dimensions.y, col);
}

void DrawApp::newCalque(const std::string& name, const std::string& filepath) {
    calques.emplace_back(name);
    calques.back().createFromFile(filepath);
}

}  // namespace MyGimp