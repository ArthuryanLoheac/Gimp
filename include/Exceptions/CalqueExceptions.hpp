#pragma once
#include <string>
#include "Exceptions/Exceptions_A.hpp"

namespace MyGimp {

class Calque_Error : public Exception_A {
 public:
    explicit Calque_Error(const std::string &message)
        : Exception_A("Calque Error: " + message) {}
};

class Calque_InvalidSize : public Calque_Error {
 public:
    explicit Calque_InvalidSize(const std::string &message)
        : Calque_Error("Invalid Size: " + message) {}
};

class Calque_FileError : public Calque_Error {
 public:
    explicit Calque_FileError(const std::string &message)
        : Calque_Error("File Error: " + message) {}
};
}  // namespace MyGimp
