#include "App/App.hpp"
#include "App/Logger.hpp"
#include "App/const.hpp"

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
    resetCursor();
    window.setVerticalSyncEnabled(true);
    drawApp.init("tests/Images/Img.jpg");
    drawApp.newCalque("Calque 2", sf::Color(0, 0, 255, 50));
    drawApp.newCalque("Calque 3", sf::Color(255, 0, 0, 50));
    LOG_INFO("Window initialization completed");
}

void App::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            close();
        } else {
            drawApp.handleInput(event);
        }
    }
}

void App::close() {
    if (window.isOpen()) {
        window.close();
        LOG_INFO("Window closed successfully");
    } else {
        LOG_WARN("Attempted to close an already closed window");
    }
}

void App::update(float deltaTime) {
    // Update game logic here
    drawApp.update(deltaTime, window);
}

void App::render() {
    window.clear(sf::Color::Black);
    drawApp.draw(window);
    window.display();
}

void App::setCursor(const sf::Cursor::Type type) {
    if (cursor.loadFromSystem(type)) {
        window.setMouseCursor(cursor);
    } else {
        LOG_ERROR("Failed to load cursor of type " + std::to_string(type));
    }
}

void App::resetCursor() {
    if (cursor.loadFromSystem(sf::Cursor::Arrow))
        window.setMouseCursor(cursor);
}

}  // namespace MyGimp
