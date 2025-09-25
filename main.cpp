# include <iostream>
# include <string>
# include <SFML/Graphics.hpp>

void processEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            window.close();
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
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "My Gimp");
    initializeWindow(window);
    sf::Clock clock;

    while (window.isOpen()) {
        processEvents(window);
        update(clock.getElapsedTime().asSeconds());
        clock.restart();
        render(window);
    }
}
