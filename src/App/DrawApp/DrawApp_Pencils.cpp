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
    printf("Loading pencils...\n");
    // Implementation for loading pencils can be added here in the future
    std::string path = "./libs/";
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        if (entry.path().extension() == ".so") {
            printf("Found pencil lib: %s\n", entry.path().c_str());
                try {
                    auto lib = dlLoader<Pencil_I>::getLib(entry.path().string(), "createPencil", "destroyPencil");
                    if (lib) {
                        loadedPencils.push_back(lib);
                        if (!currentPencil)
                            currentPencil = lib;
                    }
                } catch (const std::exception &e) {
                    LOG_ERROR(std::string("Failed to load pencil lib: ") + e.what());
                }
        }
    }
    // currentPencil already set when loading; nothing more to do here
}
}  // namespace MyGimp
