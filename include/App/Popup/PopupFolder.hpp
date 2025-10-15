#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class PopupFolder
{
 public:
    PopupFolder() = default;
    ~PopupFolder() = default;

    std::string openPopup(const std::string& name);

 private:
    std::string name;
    bool open;
};