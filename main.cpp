# include <iostream>
# include <string>
# include <SFML/Graphics.hpp>
# include "Logger.h"
# include "src/App.hpp"


int main() {
    // Initialize logging system
    LOG_INIT();
    LOG_INFO("Starting My Gimp application");
    
    try {
        MyGimp::App app;
        app.init();
        app.run();
    } catch (const std::exception& e) {
        LOG_ERROR("Fatal error: " + std::string(e.what()));
        LOG_SHUTDOWN();
        return 1;
    }
    
    LOG_INFO("My Gimp application shutting down normally");
    LOG_SHUTDOWN();
    return 0;
}
