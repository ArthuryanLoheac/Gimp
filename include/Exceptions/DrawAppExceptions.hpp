#pragma once
#include <string>

#include "Exceptions/Exceptions_A.hpp"

namespace MyGimp {

class DrawApp_Error : public Exception_A {
 public:
    explicit DrawApp_Error(const std::string &message)
        : Exception_A("DrawApp Error: " + message) {}
};

class DrawApp_ExportError : public DrawApp_Error {
 public:
    explicit DrawApp_ExportError(const std::string &message)
        : DrawApp_Error("Export Error: " + message) {}
};

class DrawApp_SaveError : public DrawApp_Error {
 public:
    explicit DrawApp_SaveError(const std::string &message)
        : DrawApp_Error("Save Error: " + message) {}
};

class DrawApp_LoadError : public DrawApp_Error {
 public:
    explicit DrawApp_LoadError(const std::string &message)
        : DrawApp_Error("Load Error: " + message) {}
};

class DrawApp_NoCalque : public DrawApp_Error {
 public:
    explicit DrawApp_NoCalque(const std::string &message)
        : DrawApp_Error("No Calque: " + message) {}
};
}  // namespace MyGimp
