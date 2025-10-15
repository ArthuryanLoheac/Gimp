#include "App/Popup/PopupFolder.hpp"
#include <filesystem>
#include <algorithm>

namespace MyGimp {
std::string PopupFolder::openPopup(const std::string& name,
std::vector<std::string> _extensions, bool _isSelectFolder,
bool _isSelectNameFile) {
    isSelectFolder = _isSelectFolder;
    isSelectNameFile = _isSelectNameFile;
    extensions = _extensions;

    init(name);
    if (!run()) return "";
    return returnPath();
}

void PopupFolder::init(const std::string& name)
{
    window.create(sf::VideoMode(400, 400), "Popup Folder");
    window.setFramerateLimit(60);

    selectedPath = "/home";
    nameFile = "";

    font.loadFromFile("Assets/Fonts/Inter.ttf");
    setupText(title, name, 20, 10, 24, sf::Color::White);
    setupText(nameFileText, nameFile, 20, 360, 16, sf::Color::White);

    buttonValidate.init("Confirm", "validate", 80);
    buttonValidate.setPosition(310, 360);

    setupRectangle(backgroundTop, 0, 0, 400, 50, sf::Color(50, 50, 50));
    setupRectangle(backgroundBottom, 0, 350, 400, 50, sf::Color(50, 50, 50));
    setupRectangle(nameFileField, 20, 385, 275, 2, sf::Color(70, 70, 70));
    setupRectangle(cursorIndicator, 20, 360, 2, 20, sf::Color(170, 170, 170));
}

bool PopupFolder::run()
{
    updatePaths();

    cursorClock.restart();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            try {
                handleInput(event);
            } catch (std::exception e) {
                window.close();
                return false;
            }
        }

        window.clear(sf::Color(20, 20, 20));
        draw();
        window.display();
    }
    return true;
}

std::string PopupFolder::returnPath()
{
    if (selectedPath.back() != '/' && selectedPath.back() != '\\' &&
        !isGoodExtension(selectedPath))
        selectedPath += '/';
    if (nameFile.empty())
        nameFile = "NewFile";
    if (!isGoodExtension(nameFile))
        nameFile += ".png";

    if (isSelectNameFile)
        return selectedPath + nameFile;
    else
        return selectedPath;
}

void PopupFolder::setupRectangle(sf::RectangleShape &rect,
    float x, float y, float width, float height, sf::Color color)
{
    rect.setSize(sf::Vector2f(width, height));
    rect.setFillColor(color);
    rect.setPosition(x, y);
}

void PopupFolder::setupText(sf::Text &text,
    const std::string &str, float x, float y, unsigned int size,
    sf::Color color)
{
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(x, y);
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

void PopupFolder::setExtensions(const std::vector<std::string>& exts) {
    extensions = exts;
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
                printf("B\n");
                return;
            } else if (!std::filesystem::is_directory(std::filesystem::path(
                selectedPath)) && !isSelectFolder &&
                !isGoodExtension(selectedPath)) {
                throw std::runtime_error("Invalid file");
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