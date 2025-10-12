#include <string>

#include "Logger.hpp"

#include "App/DrawApp/DrawApp.hpp"

namespace MyGimp {
void DrawApp::handleCommand(const std::string& command) {
    if (command.empty())
        return;
    handleCommandCalques(command);
    handleCommandFile(command);
}

void DrawApp::handleCommandCalques(const std::string& command) {
    if (command.empty())
        return;
    if (command == "add_calque") {
        newCalque("New Calque", sf::Color::Transparent);
    }
}

void DrawApp::handleCommandFile(const std::string& command) {
    if (command.empty())
        return;
    if (command == "save_file") {
        saveFile();
    } else if (command == "export_file") {
        exportFile();
    } else if (command == "new_file") {
        newFile();
    }
}
}  // namespace MyGimp
