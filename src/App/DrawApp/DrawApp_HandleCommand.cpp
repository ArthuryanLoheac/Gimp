#include <string>

#include "App/Logger.hpp"

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
    } else if (command.rfind("select_calque_", 0) == 0) {
        try {
            setId(std::stoi(command.substr(14)));
        } catch (const std::exception &e) {
            LOG_ERROR("Invalid calque selection command: " + command);
        }
    } else if (command.rfind("delete_calque_id_", 0) == 0) {
        try {
            deleteCalque(std::stoi(command.substr(17)));
        } catch (const std::exception &e) {
            LOG_ERROR("Invalid calque deletion command: " + command);
        }
    } else if (command == "delete_calque") {
        deleteCalque();
    } else if (command == "move_calque_up") {
        moveCalquePos(true);
    } else if (command == "move_calque_down") {
        moveCalquePos(false);
    } else if (command == "import_image") {
        std::string path = popupFolder.openPopup("Choose Image",
            {".png", ".jpg", ".bmp"}, false, false);
        std::string namePath = path.substr(path.find_last_of("/\\") + 1);
        if (path.empty())
            return;
        newCalque(namePath, path);
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
