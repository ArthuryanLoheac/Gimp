# include <iostream>
# include <string>
# include <SFML/Graphics.hpp>
# include "Logger.h"

void processEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            LOG_DEBUG("Window close event received");
            window.close();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            LOG_DEBUG("Escape key pressed - closing application");
            window.close();
        }
    }
}

void update(float deltaTime) {
    // Update game logic here
    (void) deltaTime;
}

void render(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    window.display();
}

void initializeWindow(sf::RenderWindow& window) {
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
}

int main() {
    // Initialize logging system
    LOG_INIT();
    LOG_INFO("Starting My Gimp application");
    
    try {
        sf::RenderWindow window(sf::VideoMode(1920, 1080), "My Gimp");
        LOG_INFO("Window created successfully (1920x1080)");
        
        initializeWindow(window);
        LOG_INFO("Window initialization completed");
        
        sf::Clock clock;
        LOG_INFO("Entering main application loop");

        while (window.isOpen()) {
            processEvents(window);
            update(clock.getElapsedTime().asSeconds());
            clock.restart();
            render(window);
        }
        
        LOG_INFO("Application loop ended - window closed");
    } catch (const std::exception& e) {
        LOG_ERROR("Fatal error: " + std::string(e.what()));
        LOG_SHUTDOWN();
        return 1;
    }
    
    LOG_INFO("My Gimp application shutting down normally");
    LOG_SHUTDOWN();
    return 0;
}
