cmake_minimum_required(VERSION 3.16)
project(MyGimp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required dependencies
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Try to find spdlog (optional)
find_package(spdlog QUIET)

# Enable testing
enable_testing()

# Try to find Criterion for unit tests
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    pkg_check_modules(CRITERION criterion)
endif()

# Source files (recursively find all .cpp files in src)
file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# Header files (recursively find all .h and .hpp files in src and include)
file(GLOB_RECURSE HEADERS
    ${CMAKE_SOURCE_DIR}/src/*.h
    ${CMAKE_SOURCE_DIR}/src/*.hpp
    ${CMAKE_SOURCE_DIR}/include/*.h
    ${CMAKE_SOURCE_DIR}/include/*.hpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} main.cpp)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)

# Optional spdlog integration
if(spdlog_FOUND)
    message(STATUS "spdlog found - enabling advanced logging")
    target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
    target_compile_definitions(${PROJECT_NAME} PRIVATE USE_SPDLOG)
else()
    message(STATUS "spdlog not found - using console fallback logging")
endif()

# Compilation options
option(ENABLE_DEBUG_LOGS "Enable debug logging (INFO level)" ON)
if(NOT ENABLE_DEBUG_LOGS OR CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(${PROJECT_NAME} PRIVATE NDEBUG)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

# Unit Tests Configuration
if(CRITERION_FOUND)
    message(STATUS "Criterion found - enabling unit tests")

    # Find all test files
    file(GLOB_RECURSE TEST_SOURCES
        ${CMAKE_SOURCE_DIR}/tests/*.cpp
    )

    # Create test executable
    add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES} ${SOURCES})

    # Include directories for tests
    target_include_directories(${PROJECT_NAME}_tests PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CRITERION_INCLUDE_DIRS}
    )

    # Link libraries for tests
    target_link_libraries(${PROJECT_NAME}_tests PRIVATE
        sfml-graphics sfml-window sfml-system
        ${CRITERION_LIBRARIES}
    )

    # Optional spdlog for tests
    if(spdlog_FOUND)
        target_link_libraries(${PROJECT_NAME}_tests PRIVATE spdlog::spdlog)
        target_compile_definitions(${PROJECT_NAME}_tests PRIVATE USE_SPDLOG)
    endif()

    # Set compilation flags for Criterion
    target_compile_options(${PROJECT_NAME}_tests PRIVATE ${CRITERION_CFLAGS_OTHER})
    target_link_directories(${PROJECT_NAME}_tests PRIVATE ${CRITERION_LIBRARY_DIRS})

    # Add test to CTest
    add_test(NAME MyGimpTests COMMAND ${PROJECT_NAME}_tests)

    # Set test output directory
    set_target_properties(${PROJECT_NAME}_tests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
    )
endif()
