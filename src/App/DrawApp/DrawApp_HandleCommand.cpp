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
            calqueMenu.getPercentageSelector().setPercentage(
                static_cast<int>(calques[actualCalqueId].getOpacity() * 100));
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
    } else if (command.rfind("see_calque_id_", 0) == 0) {
        try {
            int id = std::stoi(command.substr(14));
            if (id < 0 || id >= static_cast<int>(calques.size()))
                return;
            calques[id].setVisible(!calques[id].isVisible());
            calqueMenu.getCalqueButtons()[id]->setSee(calques[id].isVisible());
        } catch (const std::exception &e) {
            LOG_ERROR("Invalid calque see command: " + command);
        }
    } else if (command == "opacity_selector_up") {
        int opacity = calqueMenu.getPercentageSelector().getPercentage();
        opacity = std::min(100, opacity + 5);
        calqueMenu.getPercentageSelector().setPercentage(opacity);
        if (calques.empty() || actualCalqueId < 0 ||
            actualCalqueId >= static_cast<int>(calques.size()))
            return;
        calques[actualCalqueId].setOpacity(opacity / 100.f);
    } else if (command == "opacity_selector_down") {
        int opacity = calqueMenu.getPercentageSelector().getPercentage();
        opacity = std::max(0, opacity - 5);
        calqueMenu.getPercentageSelector().setPercentage(opacity);
        if (calques.empty() || actualCalqueId < 0 ||
            actualCalqueId >= static_cast<int>(calques.size()))
            return;
        calques[actualCalqueId].setOpacity(opacity / 100.f);
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
