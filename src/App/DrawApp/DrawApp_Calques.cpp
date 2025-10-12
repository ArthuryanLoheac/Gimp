#include <string>
#include <algorithm>
#include <vector>

#include "App/Logger.hpp"

#include "App/DrawApp/DrawApp.hpp"
#include "Exceptions/CalqueExceptions.hpp"

namespace MyGimp {
void DrawApp::newCalque(const std::string& name, sf::Color col) {
    try {
        calques.emplace_back(name);
        calques.back().createEmpty(dimensions.x, dimensions.y, col);
        updateCalques();
    } catch (const Calque_Error &e) {
        LOG_ERROR(e.what());
    }
}

void DrawApp::newCalque(const std::string& name, const std::string& filepath) {
    try {
        calques.emplace_back(name);
        calques.back().createFromFile(filepath);
        updateCalques();
    } catch (const Calque_Error &e) {
        LOG_ERROR(e.what());
    }
}

std::vector<Calque>& DrawApp::getCalques() {
    return calques;
}

bool DrawApp::deleteCalque() {
    bool result = deleteCalque(actualCalqueId);
    if (result)
        actualCalqueId = std::max(0, actualCalqueId - 1);
    updateCalques();
    return result;
}

bool DrawApp::deleteCalque(int id) {
    if (calques.size() <= 1)
        return false;
    if (id >= 0 && id < static_cast<int>(calques.size())) {
        calques.erase(calques.begin() + id);
        updateCalques();
        return true;
    }
    return false;
}

void DrawApp::updateCalques() {
    calqueMenu.update(calques, actualCalqueId);
}
}  // namespace MyGimp
