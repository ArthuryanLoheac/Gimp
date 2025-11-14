#include <string>
#include <iostream>
#include <filesystem>

#include "App/Logger.hpp"

#include "App/DrawApp/DrawApp.hpp"
#include "Exceptions/DrawAppExceptions.hpp"
#include "Exceptions/CalqueExceptions.hpp"

#include "App/Pencil/Pencil_I.hpp"
#include "App/dlLoader.hpp"

namespace MyGimp {
void DrawApp::loadPencils() {
    // Implementation for loading pencils can be added here in the future
    std::string path = "./libs/";
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        if (entry.path().extension() == ".so") {
            try {
                auto lib = dlLoader<Pencil_I>::getLib(entry.path().string(), "createPencil", "destroyPencil");
                if (lib)
                    addPencil(lib);
            } catch (const std::exception &e) {
                LOG_ERROR(std::string("Failed to load pencil lib: ") + e.what());
            }
        }
    }
}

void DrawApp::addPencil(std::shared_ptr<Pencil_I>& pencil) {
    loadedPencils.push_back(pencil);
    if (!currentPencil) currentPencil = pencil;
    auto btn = std::make_unique<Button>();
    btn->initIcon("Assets/Pencils/" + pencil->getNameIcon() + ".png",
                  "select_pencil_" + pencil->getName(), 30);
    printf("Adding pencil button: %s\n",
        ("Assets/Pencils/" + pencil->getNameIcon() + ".png").c_str());
    btn->setIcon("Assets/Pencils/" + pencil->getNameIcon() + ".png", 30);
    btn->setPosition(100 + static_cast<float>(pencilsButtons.size() + 1) * 50, 100);
    pencilsButtons.push_back(std::move(btn));
}
}  // namespace MyGimp
