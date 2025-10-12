#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "App/DrawApp/DrawApp.hpp"

namespace MyGimp {
class App {
 public:
    App() = default;
    ~App() = default;
    void run();
    void init();

 private:
    void processEvents();
    void update(float deltaTime);
    void render();

    void setCursor(const sf::Cursor::Type type);
    void resetCursor();
    void close();

    DrawApp drawApp;
    sf::RenderWindow window;
    sf::Cursor cursor;
};
}  // namespace MyGimp
