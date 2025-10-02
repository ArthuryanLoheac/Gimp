#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "App/DrawApp.hpp"

namespace MyGimp {
class App {
 public:
    App() = default;
    ~App() = default;
    void run();
    void init();
    static const int WIDTH = 1920;
    static const int HEIGHT = 1080;

 private:
    void processEvents();
    void update(float deltaTime);
    void render();

    void close();

    DrawApp drawApp;
    sf::RenderWindow window;
};
}  // namespace MyGimp
