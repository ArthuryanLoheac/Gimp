#include <string>

#include "App/Logger.hpp"

#include "App/DrawApp/DrawApp.hpp"
#include "Exceptions/DrawAppExceptions.hpp"
#include "Exceptions/CalqueExceptions.hpp"

namespace MyGimp {
void DrawApp::exportFile() {
    sf::Image exportedImage;
    std::string path = popupFolder.openPopup("Select Folder",
        {".png", ".jpg", ".bmp"});

    if (calques.empty())
        throw DrawApp_NoCalque("No calques to export");
    exportedImage.create(calques[0].getImage().getSize().x,
        calques[0].getImage().getSize().y, sf::Color(0, 0, 0, 0));
    for (int i = calques.size() - 1; i >= 0; --i) {
        Calque &c = calques[i];
        if (!c.isVisible())
            continue;

        sf::Vector2u dimensionstoCopy = exportedImage.getSize();
        if (c.getImage().getSize().x < dimensionstoCopy.x)
            dimensionstoCopy.x = c.getImage().getSize().x;
        if (c.getImage().getSize().y < dimensionstoCopy.y)
            dimensionstoCopy.y = c.getImage().getSize().y;
        mixCalqueForExport(exportedImage, c, dimensionstoCopy);
    }
    if (!exportedImage.saveToFile(path))
        throw DrawApp_ExportError("Failed to export");
}

void DrawApp::mixCalqueForExport(sf::Image &exportedImage, const Calque &c,
const sf::Vector2u dimensionstoCopy) {
    for (unsigned int x = 0; x < dimensionstoCopy.x; x++) {
        for (unsigned int y = 0; y < dimensionstoCopy.y; y++) {
            const sf::Color pixel = exportedImage.getPixel(x, y);
            const sf::Color newPixel = c.getImage().getPixel(x, y);
            const float calqueOpacity = c.getOpacity();
            const float a = (newPixel.a / 255.f) * calqueOpacity;
            if (a == 0) continue;

            // Calculer la nouvelle transparence (alpha)
            const float pixelAlpha = pixel.a / 255.f;
            const float outAlpha = a + pixelAlpha * (1 - a);
            if (outAlpha == 0) {
                exportedImage.setPixel(x, y, sf::Color(0, 0, 0, 0));
                continue;
            }
            const sf::Uint8 fnlR = static_cast<sf::Uint8>(((newPixel.r * a)
                + (pixel.r * pixelAlpha * (1 - a))) / outAlpha);
            const sf::Uint8 fnlG = static_cast<sf::Uint8>(((newPixel.g * a)
                + (pixel.g * pixelAlpha * (1 - a))) / outAlpha);
            const sf::Uint8 fnlB = static_cast<sf::Uint8>(((newPixel.b * a)
                + (pixel.b * pixelAlpha * (1 - a))) / outAlpha);
            const sf::Uint8 fnlA = static_cast<sf::Uint8>(outAlpha * 255);
            exportedImage.setPixel(x, y, sf::Color(fnlR, fnlG, fnlB, fnlA));
        }
    }
}
}  // namespace MyGimp
