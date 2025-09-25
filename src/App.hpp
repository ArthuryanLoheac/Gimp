#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

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

    sf::RenderWindow window;
};
}  // namespace MyGimp
