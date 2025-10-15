#include "App/Popup/PopupFolder.hpp"
#include <filesystem>

namespace MyGimp {
std::string PopupFolder::openPopup(const std::string& name)
{
    selectedPath = "/home";
    window.create(sf::VideoMode(400, 400), "Popup Folder");
    window.setFramerateLimit(60);

    font.loadFromFile("Assets/Fonts/Inter.ttf");
    title.setFont(font);
    title.setString(name);
    title.setCharacterSize(24);
    title.setFillColor(sf::Color::White);
    title.setPosition(20, 10);

    buttonValidate.init("Choose Current Folder", "validate");
    buttonValidate.setPosition(200 - (buttonValidate.getWidth() / 2.f), 355);

    backgroundTop.setSize(sf::Vector2f(400, 50));
    backgroundTop.setFillColor(sf::Color(50, 50, 50));
    backgroundTop.setPosition(0, 0);

    backgroundBottom.setSize(sf::Vector2f(400, 50));
    backgroundBottom.setFillColor(sf::Color(50, 50, 50));
    backgroundBottom.setPosition(0, 350);

    updatePaths();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            handleInput(event);
        }

        window.clear(sf::Color(20, 20, 20));
        draw();
        window.display();
    }

    return selectedPath; // Example return value
}

void PopupFolder::draw()
{
    // Draw the options
    for (auto& option : options)
        option->draw(window);

    window.draw(backgroundTop);
    window.draw(backgroundBottom);
    window.draw(title);
    buttonValidate.draw(window);
}

void PopupFolder::updatePaths()
{
    options.clear();
    options.push_back(std::make_shared<Button>("..", std::filesystem::path(selectedPath).parent_path().string(), 365));
    options.back()->setPosition(20, 20 + options.size() * separationY);
    for (const auto& entry : std::filesystem::directory_iterator(selectedPath)) {
        if (!entry.is_directory())
            continue;
        options.push_back(std::make_shared<Button>(entry.path().filename().string(),
                                entry.path().string(), 365));
        options.back()->setPosition(20, 20 + options.size() * separationY);
    }
    scrollOffset = 0.0f;
}

void PopupFolder::handleInput(sf::Event &event)
{
    bool consumed = false;
    // Handle user input for the popup folder
    if (buttonValidate.handleInput(event, consumed) == "validate")
        window.close();
    bool pathChanged = false;
    for (auto& option : options) {
        if (option->handleInput(event, consumed) != "") {
            selectedPath = option->getCode();
            pathChanged = true;
            break;
        }
    }
    if (pathChanged)
        updatePaths();
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0)
            scrollOffset += 15.0f;
        else
            scrollOffset -= 15.0f;
        if (scrollOffset > 0.0f)
            scrollOffset = 0.0f;
        if (options.size() * separationY <= 300)
            scrollOffset = 0.0f;
        else if (scrollOffset <= options.size() * -separationY + 300 - 2)
            scrollOffset = options.size() * -separationY + 300 - 2;
        for (int i = 0; i < options.size(); i++)
            options[i]->setPosition(20, 20 + (i + 1) * separationY + scrollOffset);
    }
}
}  // namespace MyGimp