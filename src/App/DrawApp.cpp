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

void DrawApp::handleInput(sf::Event &event) {
    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::E
        && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        exportFile();
    }
    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::S
        && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        saveFile();
    }
}

sf::Vector2u DrawApp::getDimensions() const {
    return dimensions;
}

void DrawApp::init(int width, int height) {
    calques.clear();
    dimensions = sf::Vector2u(width, height);
    newCalque("Calque 1", sf::Color::White);
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

void DrawApp::saveFile() {
    LOG_INFO("SAVE FILE");
}

void DrawApp::exportFile() {
    sf::Image exportedImage;

    if (calques.size() <= 0)
        return;
    exportedImage.create(calques[0].getImage().getSize().x, calques[0].getImage().getSize().y);
    for (Calque &c : calques) {
        sf::Vector2u dimensionstoCopy = exportedImage.getSize();
        if (c.getImage().getSize().x < dimensionstoCopy.x)
            dimensionstoCopy.x = c.getImage().getSize().x;
        if (c.getImage().getSize().y < dimensionstoCopy.y)
            dimensionstoCopy.y = c.getImage().getSize().y;
        mixCalqueForExport(exportedImage, c, dimensionstoCopy);
    }
    exportedImage.saveToFile("Saves/Img.jpg");
}

void DrawApp::mixCalqueForExport(sf::Image &exportedImage, const Calque &c,
const sf::Vector2u dimensionstoCopy) {
    for (int x = 0; x < dimensionstoCopy.x; x++) {
        for (int y = 0; y < dimensionstoCopy.y; y++) {
            const sf::Color pixel = exportedImage.getPixel(x, y);
            const sf::Color newPixel = c.getImage().getPixel(x, y);
            const float a = newPixel.a / 255.f;
            if (a == 0) continue;

            const sf::Color finalPixel = sf::Color(
                (pixel.r * (1 - a)) + (newPixel.r * a),
                (pixel.g * (1 - a)) + (newPixel.g * a),
                (pixel.b * (1 - a)) + (newPixel.b * a),
                255
            );
            exportedImage.setPixel(x, y, finalPixel);
        }
    }
}

}  // namespace MyGimp