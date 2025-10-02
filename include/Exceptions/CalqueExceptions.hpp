#pragma once
#include "Exceptions/Exceptions_A.hpp"

namespace MyGimp {
class Calque_InvalidSize : public Exception_A {
 public:
    explicit Calque_InvalidSize(const std::string &message)
        : Exception_A("Invalid Size: " + message) {}
};

class Calque_FileError : public Exception_A {
 public:
    explicit Calque_FileError(const std::string &message)
        : Exception_A("File Error: " + message) {}
};
}  // namespace MyGimp