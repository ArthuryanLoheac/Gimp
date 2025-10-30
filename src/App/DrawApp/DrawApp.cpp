#include <string>
#include <algorithm>
#include <vector>

#include "App/Logger.hpp"
#include "App/const.hpp"

#include "App/DrawApp/DrawApp.hpp"
#include "Exceptions/DrawAppExceptions.hpp"
#include "Exceptions/CalqueExceptions.hpp"

#include "App/Pencil/Pencil_Simple.hpp"

namespace MyGimp {

// Initialization

void DrawApp::init(int width, int height) {
    calques.clear();
    dimensions = sf::Vector2u(width, height);
    newCalque("Calque 1", sf::Color::White);
    currentPencil = std::make_shared<Pencil_Simple>();
    currentPencil->init(1, sf::Color::Black);
    commonInit();
}

void DrawApp::init(const std::string& filepath) {
    try {
        calques.clear();
        calques.emplace_back("Calque 1");
        calques.back().createFromFile(filepath);
        updateCalques();
        dimensions = calques.back().getImage().getSize();
        currentPencil = std::make_shared<Pencil_Simple>();
        currentPencil->init(1, sf::Color::Black);
        commonInit();
    } catch (const Calque_Error &e) {
        LOG_ERROR(e.what());
        init(800, 600);
    }
}

void DrawApp::commonInit() {
    background = sf::RectangleShape(sf::Vector2f(
        static_cast<float>(250),
        static_cast<float>(200)));
    background.setPosition(WIDTH - 250, HEIGHT - 500);
    background.setFillColor(sf::Color(200, 200, 200, 30));
    colorPicker.setPosition(WIDTH - 240.f, HEIGHT - 490.f);
    sizeSelector.setPosition(WIDTH - 215.f, HEIGHT - 335.f);
    sizeSelector.setTitle("Size:");
}

// Calque Management


void DrawApp::newFile() {
    calques.clear();
    dimensions = sf::Vector2u(800, 600);
    newCalque("Calque 1", sf::Color::White);
}

// Getters & Setters

sf::Vector2u DrawApp::getDimensions() const {
    return dimensions;
}

void DrawApp::setId(int id) {
    if (id >= 0 && id < static_cast<int>(calques.size()))
        actualCalqueId = id;
    updateCalques();
}
}  // namespace MyGimp
