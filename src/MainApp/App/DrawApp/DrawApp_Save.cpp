#include <string>
#include <fstream>
#include <cstdint>

#include "App/Logger.hpp"

#include "App/DrawApp/DrawApp.hpp"
#include "Exceptions/DrawAppExceptions.hpp"
#include "Exceptions/CalqueExceptions.hpp"


namespace MyGimp {
void DrawApp::saveFile() {
    try {
        std::string path = popupFolder.openPopup("Save Project",
            {".gimp"});
        if (path.empty())
            path = "project_save.gimp";

        std::ofstream ofs(path, std::ios::binary);
        if (!ofs)
            throw DrawApp_SaveError("Unable to open file for writing: " + path);

        // Header: magic + version
        ofs.write("MGMP", 4);
        uint32_t version = 1;
        ofs.write(reinterpret_cast<const char*>(&version), sizeof(version));

        // Dimensions
        uint32_t width = dimensions.x;
        uint32_t height = dimensions.y;
        ofs.write(reinterpret_cast<const char*>(&width), sizeof(width));
        ofs.write(reinterpret_cast<const char*>(&height), sizeof(height));

        // Number of calques
        uint32_t num = static_cast<uint32_t>(getCalques().size());
        ofs.write(reinterpret_cast<const char*>(&num), sizeof(num));

        for (const auto &c : getCalques()) {
            // Name
            const std::string &name = c.getName();
            uint32_t nlen = static_cast<uint32_t>(name.size());
            ofs.write(reinterpret_cast<const char*>(&nlen), sizeof(nlen));
            ofs.write(name.data(), nlen);

            // Visible
            uint8_t vis = c.isVisible() ? 1 : 0;
            ofs.write(reinterpret_cast<const char*>(&vis), sizeof(vis));

            // Opacity
            float op = c.getOpacity();
            ofs.write(reinterpret_cast<const char*>(&op), sizeof(op));

            // Image size
            const sf::Image &img = c.getImage();
            uint32_t iw = img.getSize().x;
            uint32_t ih = img.getSize().y;
            ofs.write(reinterpret_cast<const char*>(&iw), sizeof(iw));
            ofs.write(reinterpret_cast<const char*>(&ih), sizeof(ih));

            // Pixels (RGBA)
            const sf::Uint8 *pixels = img.getPixelsPtr();
            if (pixels && iw > 0 && ih > 0) {
                size_t psz = static_cast<size_t>(iw) * ih * 4;
                ofs.write(reinterpret_cast<const char*>(pixels), psz);
            }
        }
        ofs.close();
        LOG_INFO(std::string("Saved project to ") + path);
    } catch (const std::exception &e) {
        LOG_ERROR(e.what());
        throw DrawApp_SaveError(e.what());
    }
}
}  // namespace MyGimp
