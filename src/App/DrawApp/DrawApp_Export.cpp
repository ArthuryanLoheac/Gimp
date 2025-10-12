#include <string>

#include "Logger.hpp"

#include "App/DrawApp/DrawApp.hpp"
#include "Exceptions/DrawAppExceptions.hpp"
#include "Exceptions/CalqueExceptions.hpp"

namespace MyGimp {
void DrawApp::exportFile() {
    sf::Image exportedImage;

    if (calques.empty())
        throw DrawApp_NoCalque("No calques to export");
    exportedImage.create(calques[0].getImage().getSize().x,
                        calques[0].getImage().getSize().y);
    for (Calque &c : calques) {
        sf::Vector2u dimensionstoCopy = exportedImage.getSize();
        if (c.getImage().getSize().x < dimensionstoCopy.x)
            dimensionstoCopy.x = c.getImage().getSize().x;
        if (c.getImage().getSize().y < dimensionstoCopy.y)
            dimensionstoCopy.y = c.getImage().getSize().y;
        mixCalqueForExport(exportedImage, c, dimensionstoCopy);
    }
    if (!exportedImage.saveToFile("Saves/Img.jpg"))
        throw DrawApp_ExportError("Failed to export");
}

void DrawApp::mixCalqueForExport(sf::Image &exportedImage, const Calque &c,
const sf::Vector2u dimensionstoCopy) {
    for (unsigned int x = 0; x < dimensionstoCopy.x; x++) {
        for (unsigned int y = 0; y < dimensionstoCopy.y; y++) {
            const sf::Color pixel = exportedImage.getPixel(x, y);
            const sf::Color newPixel = c.getImage().getPixel(x, y);
            const float a = newPixel.a / 255.f;
            if (a == 0) continue;

            const sf::Color finalPixel = sf::Color(
                (pixel.r * (1 - a)) + (newPixel.r * a),
                (pixel.g * (1 - a)) + (newPixel.g * a),
                (pixel.b * (1 - a)) + (newPixel.b * a),
                255);
            exportedImage.setPixel(x, y, finalPixel);
        }
    }
}
}  // namespace MyGimp
