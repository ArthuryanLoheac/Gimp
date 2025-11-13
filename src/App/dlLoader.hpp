#pragma once
#include <dlfcn.h>

#include <string>
#include <memory>
#include <iostream>

template <typename T>
class dlLoader {
 public:
    class dlError : public std::exception {
     private:
        std::string message;

     public:
        explicit dlError(const std::string& errorMsg)
            : message("dlLoader: " + errorMsg) {}
        const char *what() const noexcept override {
            return message.c_str();
        }
    };

    static bool verifyLib(const std::string &path,
                          const std::string &createGetter,
                          const std::string &destroyGetter);
    static std::shared_ptr<T> getLib(const std::string &path,
        const std::string &createGetter,
        const std::string &destroyGetter);
};

template <typename T>
inline bool dlLoader<T>::verifyLib(const std::string &path,
    const std::string &createGetter,
    const std::string &destroyGetter) {
    void *handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << path << "(1): " << dlerror() << std::endl;
        return false;
    }
    void* createPtr = dlsym(handle, createGetter.c_str());
    if (!createPtr) {
        std::cerr << path << "(create): " << dlerror() << std::endl;
        dlclose(handle);
        return false;
    }
    void* destroyPtr = dlsym(handle, destroyGetter.c_str());
    if (!destroyPtr) {
        std::cerr << path << "(destroy): " << dlerror() << std::endl;
        dlclose(handle);
        return false;
    }
    try {
        auto testCreate = reinterpret_cast<T* (*)()>(createPtr);
        auto testDestroy = reinterpret_cast<void (*)(T*)>(destroyPtr);
        (void)testCreate; (void)testDestroy;
    } catch(const std::exception& e) {
        std::cerr << path << ": Bad format for entry point." << std::endl;
        return false;
    }
    dlclose(handle);
    return true;
}

template <typename T>
inline std::shared_ptr<T> dlLoader<T>::getLib(const std::string &path,
    const std::string &createGetter,
    const std::string &destroyGetter) {
    if (!verifyLib(path, createGetter, destroyGetter))
        throw dlError("Invalid lib");
    void *handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle)
        throw dlError("Can't open lib");
    auto createModule = reinterpret_cast<T* (*)()>
        (dlsym(handle, createGetter.c_str()));
    if (!createModule) {
        dlclose(handle);
        throw dlError("Can't find create symbol");
    }
    auto destroyModule = reinterpret_cast<void (*)(T*)>
        (dlsym(handle, destroyGetter.c_str()));
    if (!destroyModule) {
        dlclose(handle);
        throw dlError("Can't find destroy symbol");
    }
    T* raw = createModule();
    // Wrap raw pointer into shared_ptr with custom deleter that calls
    // the plugin-provided destroy function and then dlclose the handle.
    auto deleter = [destroyModule, handle](T* p) {
        if (p) destroyModule(p);
        if (handle) dlclose(handle);
    };
    std::shared_ptr<T> module(raw, deleter);
    return module;
}