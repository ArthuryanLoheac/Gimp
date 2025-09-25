# include <iostream>
# include <string>
# include <SFML/Graphics.hpp>

void initializeWindow(sf::RenderWindow& window) {
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "My Gimp");
    initializeWindow(window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        window.display();
    }
}
