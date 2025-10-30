#include <string>
#include <algorithm>

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
    } else {
        handleCommandOpacity(command);
    }
}

void DrawApp::handleCommandPencils(const std::string& command) {
    if (command == "size_selector_up") {
        int size = pencilMenu.getSizeSelector().getPercentage();
        size += 1;
        pencilMenu.getSizeSelector().setPercentage(size);
        currentPencil->setSize(size);
    } else if (command == "size_selector_down") {
        int size = pencilMenu.getSizeSelector().getPercentage();
        size = std::max(0, size - 1);
        pencilMenu.getSizeSelector().setPercentage(size);
        currentPencil->setSize(size);
    } else if (command.rfind("size_selector_input", 0) == 0) {
        try {
            int size = std::stoi(command.substr(20));
            size = std::max(0, size);
            pencilMenu.getSizeSelector().setPercentage(size);
            currentPencil->setSize(size);
        } catch (const std::exception &e) {
            LOG_ERROR("Invalid size input command: " + command);
        }
    }
}

void DrawApp::handleCommandOpacity(const std::string& command) {
    if (command.rfind("see_calque_id_", 0) == 0) {
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
    } else if (command.rfind("opacity_selector_input", 0) == 0) {
        try {
            int opacity = std::stoi(command.substr(23));
            opacity = std::clamp(opacity, 0, 100);
            calqueMenu.getPercentageSelector().setPercentage(opacity);
            if (calques.empty() || actualCalqueId < 0 ||
                actualCalqueId >= static_cast<int>(calques.size()))
                return;
            calques[actualCalqueId].setOpacity(opacity / 100.f);
        } catch (const std::exception &e) {
            LOG_ERROR("Invalid opacity input command: " + command);
        }
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
