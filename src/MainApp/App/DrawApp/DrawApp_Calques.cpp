#include <string>
#include <algorithm>
#include <utility>
#include <vector>

#include "App/Logger.hpp"

#include "App/DrawApp/DrawApp.hpp"
#include "Exceptions/CalqueExceptions.hpp"

namespace MyGimp {
const int MAX_CALQUES_SAVES = 40;

void DrawApp::newCalque(const std::string& name, sf::Color col) {
    try {
        if (calquesSaves.empty()) {
            calquesSaves.emplace_back();
            currentCalquesId = static_cast<int>(calquesSaves.size()) - 1;
        } else {
            if (currentCalquesId < 0 || currentCalquesId >=
                static_cast<int>(calquesSaves.size()))
                currentCalquesId = static_cast<int>(calquesSaves.size()) - 1;
        }
        getCalques().emplace(getCalques().begin(), name);
        getCalques().front().createEmpty(dimensions.x, dimensions.y, col);
        updateCalques();
    } catch (const Calque_Error &e) {
        LOG_ERROR(e.what());
    }
}

void DrawApp::newCalque(const std::string& name, const std::string& filepath) {
    try {
        getCalques().emplace(getCalques().begin(), name);
        getCalques().front().createFromFile(filepath);
        updateCalques();
    } catch (const Calque_Error &e) {
        LOG_ERROR(e.what());
    }
}

std::vector<Calque>& DrawApp::getCalques() {
    return calquesSaves[currentCalquesId];
}

Calque &DrawApp::getCalque() {
    if (actualCalqueId < 0 ||
        actualCalqueId >= static_cast<int>(getCalques().size())) {
        throw Calque_Error("Invalid calque ID accessed.");
    }
    return getCalques()[actualCalqueId];
}

Calque &DrawApp::getCalque(int id) {
    if (id < 0 || id >= static_cast<int>(getCalques().size())) {
        throw Calque_Error("Invalid calque ID accessed.");
    }
    return getCalques()[id];
}

bool DrawApp::deleteCalque() {
    bool result = deleteCalque(actualCalqueId);
    if (result)
        actualCalqueId = std::max(0, actualCalqueId - 1);
    updateCalques();
    return result;
}

bool DrawApp::deleteCalque(int id) {
    if (getCalques().size() <= 1)
        return false;
    if (id >= 0 && id < static_cast<int>(getCalques().size())) {
        getCalques().erase(getCalques().begin() + id);
        updateCalques();
        return true;
    }
    return false;
}

void DrawApp::moveCalquePos(bool up) {
    if (actualCalqueId < 0 ||
        actualCalqueId >= static_cast<int>(getCalques().size()))
        return;
    if (up && actualCalqueId > 0) {
        std::swap(getCalque(), getCalques()[actualCalqueId - 1]);
        actualCalqueId = actualCalqueId - 1;
    } else if (!up && actualCalqueId <
        static_cast<int>(getCalques().size()) - 1) {
        std::swap(getCalque(), getCalques()[actualCalqueId + 1]);
        actualCalqueId = actualCalqueId + 1;
    }
    updateCalques();
}

void DrawApp::updateCalques() {
    calqueMenu.update(getCalques(), actualCalqueId);
}

void DrawApp::makeSaveCalques() {
    std::vector<Calque> calquesCopy;
    for (const auto& calque : getCalques()) {
        Calque calqueCopy(calque.getName());
        calqueCopy.copyCalque(calque);
        calquesCopy.push_back(std::move(calqueCopy));
    }
    calquesSaves.push_back(std::move(calquesCopy));
    if (calquesSaves.size() > MAX_CALQUES_SAVES)
        calquesSaves.erase(calquesSaves.begin());
    currentCalquesId = static_cast<int>(calquesSaves.size()) - 1;
}

void DrawApp::loadPreviousCalques() {
    if (calquesSaves.size() <= 1)
        return;
    calquesSaves.pop_back();
    actualCalqueId = std::min(actualCalqueId,
        static_cast<int>(getCalques().size()) - 1);
    currentCalquesId = static_cast<int>(calquesSaves.size()) - 1;
    updateCalques();
}

}  // namespace MyGimp
