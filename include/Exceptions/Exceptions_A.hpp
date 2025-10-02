#pragma once

#include <exception>
#include <string>

namespace MyGimp {
class Exception_A : public std::exception {
 protected:
    std::string _message;

 public:
    explicit Exception_A(const std::string &message) : _message(message) {}
    virtual ~Exception_A() = default;

    const char *what() const noexcept override {
        return _message.c_str();
    }
};
}  // namespace MyGimp
