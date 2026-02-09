#include <string>
#include <algorithm>
#include <vector>
#include <memory>

#include "App/Logger.hpp"
#include "App/const.hpp"

#include "App/DrawApp/DrawApp.hpp"
#include "Exceptions/DrawAppExceptions.hpp"
#include "Exceptions/CalqueExceptions.hpp"

namespace MyGimp {

// Initialization

void DrawApp::init(int width, int height) {
    calquesSaves.clear();
    redoCalquesSaves.clear();
    dimensions = sf::Vector2u(width, height);
    newCalque("Calque 1", sf::Color::White);
    loadPencils();
}

void DrawApp::init(const std::string& filepath) {
    try {
        calquesSaves.clear();
        redoCalquesSaves.clear();
        calquesSaves.emplace_back();
        currentCalquesId = 0;
        getCalques().emplace_back("Calque 1");
        getCalques().back().createFromFile(filepath);
        updateCalques();
        dimensions = getCalques().back().getImage().getSize();
        loadPencils();
    } catch (const Calque_Error &e) {
        LOG_ERROR(e.what());
        init(800, 600);
    }
}

// Calque Management


void DrawApp::newFile() {
    calquesSaves.clear();
    redoCalquesSaves.clear();
    dimensions = sf::Vector2u(800, 600);
    newCalque("Calque 1", sf::Color::White);
}

// Getters & Setters

sf::Vector2u DrawApp::getDimensions() const {
    return dimensions;
}

void DrawApp::setId(int id) {
    int size = 0;
    if (currentCalquesId >= 0 && currentCalquesId <
        static_cast<int>(calquesSaves.size()))
        size = static_cast<int>(calquesSaves[currentCalquesId].size());
    else if (!calquesSaves.empty())
        size = static_cast<int>(calquesSaves.back().size());

    if (id >= 0 && id < size)
        actualCalqueId = id;
    updateCalques();
}
}  // namespace MyGimp
