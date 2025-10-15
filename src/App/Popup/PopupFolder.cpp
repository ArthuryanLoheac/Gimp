#include "App/Popup/PopupFolder.hpp"
#include <filesystem>
#include <algorithm>

namespace MyGimp {
std::string PopupFolder::openPopup(const std::string& name,
std::vector<std::string> _extensions, bool _isSelectFolder,
bool _isSelectNameFile) {
    selectedPath = "/home";
    window.create(sf::VideoMode(400, 400), "Popup Folder");
    window.setFramerateLimit(60);
    nameFile = "";
    isSelectFolder =_isSelectFolder;
    isSelectNameFile =_isSelectNameFile;
    extensions = _extensions;

    font.loadFromFile("Assets/Fonts/Inter.ttf");
    title.setFont(font);
    title.setString(name);
    title.setCharacterSize(24);
    title.setFillColor(sf::Color::White);
    title.setPosition(20, 10);
    nameFileText.setFont(font);
    nameFileText.setString(nameFile);
    nameFileText.setCharacterSize(16);
    nameFileText.setFillColor(sf::Color::White);
    nameFileText.setPosition(20, 360);
    nameFile = "";

    buttonValidate.init("Confirm", "validate", 80);
    buttonValidate.setPosition(310, 360);

    backgroundTop.setSize(sf::Vector2f(400, 50));
    backgroundTop.setFillColor(sf::Color(50, 50, 50));
    backgroundTop.setPosition(0, 0);

    backgroundBottom.setSize(sf::Vector2f(400, 50));
    backgroundBottom.setFillColor(sf::Color(50, 50, 50));
    backgroundBottom.setPosition(0, 350);

    nameFileField.setSize(sf::Vector2f(275, 2));
    nameFileField.setFillColor(sf::Color(70, 70, 70));
    nameFileField.setPosition(20, 385);

    cursorIndicator.setSize(sf::Vector2f(2, 20));
    cursorIndicator.setFillColor(sf::Color(170, 170, 170));
    cursorIndicator.setPosition(20, 360);

    updatePaths();

    cursorClock.restart();
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

    if (selectedPath.back() != '/' && selectedPath.back() != '\\' && !isGoodExtension(selectedPath))
        selectedPath += '/';
    if (nameFile.empty()) nameFile = "NewFile";
    if (!isGoodExtension(nameFile)) nameFile += ".png";
    if (isSelectNameFile)
        return selectedPath + nameFile; // Example return value
    else
        return selectedPath;
}

bool PopupFolder::isGoodExtension(const std::string& filename) {
    std::string ext = getExtension(filename);
    if (std::find(extensions.begin(), extensions.end(), ext)
        == extensions.end() || ext.empty())
        return false;
    return true;
}

std::string PopupFolder::getExtension(const std::string& filename) {
    size_t dotPos = filename.find_last_of('.');
    if (dotPos == std::string::npos)
        return "";
    return filename.substr(dotPos);
}

void PopupFolder::draw()
{
    // Draw the options
    for (auto& option : options)
        option->draw(window);

    window.draw(backgroundTop);
    window.draw(backgroundBottom);
    window.draw(title);
    if (isSelectNameFile) {
        window.draw(nameFileField);
        if (cursorClock.getElapsedTime().asSeconds() < 0.5f || (static_cast<int>
            (cursorClock.getElapsedTime().asSeconds() * 2) % 2 == 0))
            window.draw(cursorIndicator);
        window.draw(nameFileText);
        buttonValidate.draw(window);
    }
}

void PopupFolder::updatePaths()
{
    options.clear();
    options.push_back(std::make_shared<Button>("..",
        std::filesystem::path(selectedPath).parent_path().string(), 365));
    options.back()->setPosition(20, 20 + options.size() * separationY);
    for (const auto& entry : std::filesystem::directory_iterator(selectedPath)) {
        if (!entry.is_directory() && isSelectFolder)
            continue;
        options.push_back(std::make_shared<Button>(
            entry.path().filename().string(),
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
            // is directory ?
            if (!std::filesystem::is_directory(std::filesystem::path(
                selectedPath)) && !isSelectFolder &&
                isGoodExtension(selectedPath)) {
                window.close();
                return;
            } else {
                pathChanged = true;
            }
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

    if (event.type == sf::Event::TextEntered && isSelectNameFile) {
        if (event.text.unicode == 8) { // Backspace
            if (!nameFile.empty())
                nameFile.pop_back();
        } else if (event.text.unicode < 128 && event.text.unicode >= 32) {
            nameFile += static_cast<char>(event.text.unicode);
        }
        cursorIndicator.setPosition(20 + nameFileField.getSize().x + 5, 360);
        nameFileText.setString(nameFile);
        cursorIndicator.setPosition(20 + nameFileText.getLocalBounds().width,
            360);
    }
}
}  // namespace MyGimp