#include "App/App.hpp"
#include "Logger.h"

namespace MyGimp {
void App::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        processEvents();
        update(clock.getElapsedTime().asSeconds());
        clock.restart();
        render();
    }
}

void App::init() {
    window.create(sf::VideoMode(WIDTH, HEIGHT), "My Gimp");
    LOG_INFO("Window created successfully (" + std::to_string(WIDTH)
        + "x" + std::to_string(HEIGHT) + ")");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    drawApp.init("tests/Images/Img.jpg");
    drawApp.newCalque("Calque 2", sf::Color(0, 0, 255, 50));
    drawApp.newCalque("Calque 3", sf::Color(255, 0, 0, 50));
    LOG_INFO("Window initialization completed");
}

void App::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            LOG_DEBUG("Window close event received");
            window.close();
        } else if (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::Escape) {
            LOG_DEBUG("Escape key pressed - closing application");
            window.close();
        } else {
            drawApp.handleInput(event);
        }
    }
}

void App::update(float deltaTime) {
    // Update game logic here
    drawApp.update(deltaTime);
}

void App::render() {
    window.clear(sf::Color::Black);
    drawApp.draw(window);
    window.display();
}
}  // namespace MyGimp
