#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "App/Calque.hpp"


namespace MyGimp {
class DrawApp {
 public:
    ~DrawApp() = default;

    void draw() = 0;
    void update() = 0;
    void handleInput() = 0;

 private:
    std::vector<Calque> calques;
};
}  // namespace MyGimp