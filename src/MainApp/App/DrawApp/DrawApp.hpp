#pragma once
#include <string>
#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>
#include "App/Calque.hpp"
#include "App/TopBar/TopBar.hpp"
#include "App/CalqueMenu/CalqueMenu.hpp"
#include "App/Popup/PopupFolder.hpp"
#include "App/Pencil/Pencil_I.hpp"
#include "App/PencilMenu/PencilMenu.hpp"
#include "App/TopBar/Button.hpp"


namespace MyGimp {
class DrawApp {
 public:
    ~DrawApp() = default;

    void draw(sf::RenderWindow &);
    void update(float deltaTime, sf::RenderWindow& window);
    void handleInput(sf::Event &event);

    sf::Vector2u getDimensions() const;

    void init(int width, int height);
    void init(const std::string& filepath);
    void newCalque(const std::string& name,
        sf::Color col = sf::Color::Transparent);
    void newCalque(const std::string& name, const std::string& filepath);
    std::vector<Calque>& getCalques();
    Calque &getCalque();
    Calque &getCalque(int id);
    bool deleteCalque();
    bool deleteCalque(int id);
    void moveCalquePos(bool up);
    bool isDragging() const { return dragging; }

    void setId(int id);
    int getId() const { return actualCalqueId; }
    void saveFile();
    void exportFile();
    void loadFile();
    void loadFile(const std::string& filepath);

    void makeSaveCalques();
    void loadPreviousCalques();
    void loadNextCalques();

 private:
    std::vector<std::vector<Calque>> calquesSaves;
    int currentCalquesId = -1;
    std::vector<std::vector<Calque>> redoCalquesSaves;

    sf::Vector2u dimensions;
    float zoom = 1.0f;
    sf::Vector2f viewOffset = {0.0f, 0.0f};
    bool dragging = false;
    sf::Vector2i lastMousePos;
    TopBar topBar;
    int actualCalqueId = 0;
    CalqueMenu calqueMenu;
    PopupFolder popupFolder;
    // Pencils
    std::shared_ptr<Pencil_I> currentPencil;
    std::vector<std::shared_ptr<Pencil_I>> loadedPencils;
    std::vector<std::unique_ptr<Button>> pencilsButtons;
    PencilMenu pencilMenu;

    void handleCommand(const std::string& command);
    void handleCommandCalques(const std::string& command);
    void handleCommandOpacity(const std::string& command);
    void handleCommandPencils(const std::string& command);
    void handleCommandFile(const std::string& command);

    void handleDragging(sf::Event &event, bool &consumed);
    void handleZooming(sf::Event &event);
    void handlePainting(sf::Event &event);
    sf::Color sampleColorAt(const sf::Vector2f& windowPos);

    void updateCalques();
    void mixCalqueForExport(sf::Image &exportedImage, const Calque &c,
        const sf::Vector2u dimensionstoCopy);
    void newFile();

    // Selection tool
    void startSelection(const sf::Vector2f& windowPos);
    void updateSelection(const sf::Vector2f& windowPos);
    void finalizeSelection();
    void cancelSelection();

    void startMoveSelection(const sf::Vector2f& windowPos);
    void updateMoveSelection(const sf::Vector2f& windowPos);
    void commitMoveSelection();

    void loadPencils();
    void addPencil(std::shared_ptr<Pencil_I>& pencil);

    // Selection state
    bool selecting = false;
    bool selectionActive = false;
    bool draggingSelection = false;
    sf::IntRect selectionRect = sf::IntRect(0,0,0,0);
    sf::Image selectionImage;
    sf::Image selectionBackup;
    sf::Texture selectionTexture;
    sf::Sprite selectionSprite;
    sf::Vector2i selectionStartWindow{0,0};
    sf::Vector2i selectionDragStart{0,0};
    sf::Vector2f selectionSpriteWindowPos{0.f,0.f};
    int selectionCalqueId = -1;
};
}  // namespace MyGimp
