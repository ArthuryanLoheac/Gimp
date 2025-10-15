#include "App/Popup/PopupFolder.hpp"

std::string PopupFolder::openPopup(const std::string& name)
{
    sf::RenderWindow window(sf::VideoMode(400, 200), "Popup Folder");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return "Saves/"; // Example return value
}
