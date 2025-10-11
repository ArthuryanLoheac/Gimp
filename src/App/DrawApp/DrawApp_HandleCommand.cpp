#include <string>

#include "Logger.h"

#include "App/DrawApp/DrawApp.hpp"

namespace MyGimp {
void DrawApp::handleCommand(const std::string& command) {
    if (command == "save_file") {
        saveFile();
    } else if (command == "export_file") {
        exportFile();
    } else if (command == "new_file") {
        newFile();
    }
}
}  // namespace MyGimp
