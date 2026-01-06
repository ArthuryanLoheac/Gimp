#include <string>
#include <fstream>
#include <vector>
#include <cstdint>

#include "App/Logger.hpp"

#include "App/DrawApp/DrawApp.hpp"
#include "Exceptions/DrawAppExceptions.hpp"
#include "Exceptions/CalqueExceptions.hpp"

namespace MyGimp {
void DrawApp::loadFile() {
    try {
        std::string path = popupFolder.openPopup("Open Project",
            {".gimp"}, false, false);
        if (path.empty())
            throw DrawApp_LoadError("No file selected");
        loadFile(path);
    } catch (const std::exception &e) {
        LOG_ERROR(e.what());
        throw DrawApp_LoadError(e.what());
    }
}

void DrawApp::loadFile(const std::string& filepath) {
    try {
        std::ifstream ifs(filepath, std::ios::binary);
        if (!ifs)
            throw DrawApp_LoadError("Unable to open file: " + filepath);

        // Read magic
        char magic[4];
        ifs.read(magic, 4);
        if (ifs.gcount() != 4 || std::string(magic, 4) != "MGMP")
            throw DrawApp_LoadError("Invalid project file");

        uint32_t version = 0;
        ifs.read(reinterpret_cast<char*>(&version), sizeof(version));

        uint32_t width = 0, height = 0;
        ifs.read(reinterpret_cast<char*>(&width), sizeof(width));
        ifs.read(reinterpret_cast<char*>(&height), sizeof(height));

        uint32_t numCalques = 0;
        ifs.read(reinterpret_cast<char*>(&numCalques), sizeof(numCalques));

        std::vector<Calque> loaded;
        loaded.reserve(numCalques);

        for (uint32_t i = 0; i < numCalques; ++i) {
            uint32_t nlen = 0;
            ifs.read(reinterpret_cast<char*>(&nlen), sizeof(nlen));
            std::string name;
            name.resize(nlen);
            ifs.read(&name[0], nlen);

            uint8_t vis = 1;
            ifs.read(reinterpret_cast<char*>(&vis), sizeof(vis));

            float op = 1.0f;
            ifs.read(reinterpret_cast<char*>(&op), sizeof(op));

            uint32_t iw = 0, ih = 0;
            ifs.read(reinterpret_cast<char*>(&iw), sizeof(iw));
            ifs.read(reinterpret_cast<char*>(&ih), sizeof(ih));

            std::vector<sf::Uint8> pixels;
            if (iw > 0 && ih > 0) {
                pixels.resize(static_cast<size_t>(iw) * ih * 4);
                ifs.read(reinterpret_cast<char*>(pixels.data()), pixels.size());
                if (static_cast<size_t>(ifs.gcount()) != pixels.size()) {
                    // If we can't read all bytes, bail
                    throw DrawApp_LoadError("Unexpected EOF while reading pixels");
                }
            }

            Calque c(name);
            sf::Image img;
            if (iw > 0 && ih > 0) {
                img.create(iw, ih, pixels.empty() ? nullptr : pixels.data());
            } else {
                img.create(1, 1, sf::Color::Transparent);
            }
            c.setImage(img);
            c.setOpacity(op);
            c.setVisible(vis != 0);
            loaded.push_back(std::move(c));
        }

        // Replace current states
        calquesSaves.clear();
        redoCalquesSaves.clear();
        calquesSaves.push_back(std::move(loaded));
        currentCalquesId = 0;
        actualCalqueId = 0;
        dimensions = sf::Vector2u(width, height);
        updateCalques();
        LOG_INFO(std::string("Loaded project from ") + filepath);
    } catch (const std::exception &e) {
        LOG_ERROR(e.what());
        throw DrawApp_LoadError(e.what());
    }
}
}  // namespace MyGimp
