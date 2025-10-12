#include <string>
#include <vector>

#include "App/Logger.hpp"

#include "App/DrawApp/DrawApp.hpp"
#include "Exceptions/DrawAppExceptions.hpp"
#include "Exceptions/CalqueExceptions.hpp"


namespace MyGimp {

// Initialization

void DrawApp::init(int width, int height) {
    calques.clear();
    dimensions = sf::Vector2u(width, height);
    newCalque("Calque 1", sf::Color::White);
}

void DrawApp::init(const std::string& filepath) {
    try {
        calques.clear();
        calques.emplace_back("Calque 1");
        calques.back().createFromFile(filepath);
        dimensions = calques.back().getImage().getSize();
    } catch (const Calque_Error &e) {
        LOG_ERROR(e.what());
        init(800, 600);
    }
}

// Calque Management

void DrawApp::newCalque(const std::string& name, sf::Color col) {
    try {
        calques.emplace_back(name);
        calques.back().createEmpty(dimensions.x, dimensions.y, col);
    } catch (const Calque_Error &e) {
        LOG_ERROR(e.what());
    }
}

void DrawApp::newCalque(const std::string& name, const std::string& filepath) {
    try {
        calques.emplace_back(name);
        calques.back().createFromFile(filepath);
    } catch (const Calque_Error &e) {
        LOG_ERROR(e.what());
    }
}

void DrawApp::newFile() {
    calques.clear();
    dimensions = sf::Vector2u(800, 600);
    newCalque("Calque 1", sf::Color::White);
}

// Getters & Setters

std::vector<Calque>& DrawApp::getCalques() {
    return calques;
}

sf::Vector2u DrawApp::getDimensions() const {
    return dimensions;
}
}  // namespace MyGimp
