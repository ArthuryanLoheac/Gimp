cmake_minimum_required(VERSION 3.16)
project(MyGimp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
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
    ${CMAKE_SOURCE_DIR}/src/MainApp/*.cpp
)

# Header files (recursively find all .h and .hpp files in src and include)
file(GLOB_RECURSE HEADERS
    ${CMAKE_SOURCE_DIR}/src/MainApp/*.h
    ${CMAKE_SOURCE_DIR}/src/MainApp/*.hpp
    ${CMAKE_SOURCE_DIR}/include/*.h
    ${CMAKE_SOURCE_DIR}/include/*.hpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} main.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE -fprofile-arcs -ftest-coverage)
target_link_libraries(${PROJECT_NAME} PRIVATE --coverage)
# Export all symbols from the executable so dlopen'd plugins can resolve symbols
if(UNIX)
    target_link_options(${PROJECT_NAME} PRIVATE "-rdynamic")
endif()

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src/MainApp
)

# Ensure top-level Pencils headers are visible to the main target
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src/Plugins/Pencils
)

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

# Build each Pencil as a shared library (.so) so pencils can be loaded/packaged separately
# This will create one SHARED target per .cpp file found in the top-level `Pencils/` folder.
file(GLOB PENCIL_SOURCES
    ${CMAKE_SOURCE_DIR}/src/Plugins/Pencils/*.cpp
)
set(PENCIL_LIB_TARGETS "")
if(PENCIL_SOURCES)
    message(STATUS "Found Pencil source files: ${PENCIL_SOURCES}")
    foreach(p_src IN LISTS PENCIL_SOURCES)
        get_filename_component(p_name ${p_src} NAME_WE)
        # Name the target after the source file (e.g. Pencil_Circle -> Pencil_Circle)
        add_library(${p_name} SHARED ${p_src})
        set_target_properties(${p_name} PROPERTIES
            POSITION_INDEPENDENT_CODE ON
            OUTPUT_NAME ${p_name}
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/libs"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/libs"
        )
        target_include_directories(${p_name} PRIVATE
            ${CMAKE_SOURCE_DIR}
            ${CMAKE_SOURCE_DIR}/src
            ${CMAKE_SOURCE_DIR}/include
            ${CMAKE_SOURCE_DIR}/src/MainApp
        )
        target_link_libraries(${p_name} PRIVATE sfml-graphics sfml-window sfml-system)
        list(APPEND PENCIL_LIB_TARGETS ${p_name})
    endforeach()

    # Link created pencil shared libs into main executable (and tests if present)
    if(PENCIL_LIB_TARGETS)
        message(STATUS "Created pencil shared libs: ${PENCIL_LIB_TARGETS}")
        # After building the main executable, copy all generated .so files into a `libs/` folder
        # located next to the executable (e.g. `/path/to/MyGimp/libs/`) so runtime loader
        # can use a dedicated directory.
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/libs"
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_BINARY_DIR}/libs"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/libs"
            COMMENT "Copying Pencil .so files to $<TARGET_FILE_DIR:${PROJECT_NAME}>/libs for ${PROJECT_NAME}"
        )
        if(TARGET MyGimp_tests)
            target_link_libraries(MyGimp_tests PRIVATE ${PENCIL_LIB_TARGETS})
        endif()
    endif()
else()
    message(STATUS "No Pencil sources found in ${CMAKE_SOURCE_DIR}src/Plugins/Pencils; skipping shared lib creation")
endif()

# Compilation options
option(ENABLE_DEBUG_LOGS "Enable debug logging (INFO level)" ON)
if(NOT ENABLE_DEBUG_LOGS OR CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(${PROJECT_NAME} PRIVATE NDEBUG)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

# --- Ensure Assets are available in the build/runtime directories ---
set(ASSETS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/Assets")
set(ASSETS_BINARY_DIR "${CMAKE_BINARY_DIR}/Assets")
if(EXISTS ${ASSETS_SOURCE_DIR})
    message(STATUS "Assets directory found at ${ASSETS_SOURCE_DIR}; configuring copy to ${ASSETS_BINARY_DIR}")

    # Create binary assets directory and copy all files at configure time preserving structure
    file(MAKE_DIRECTORY ${ASSETS_BINARY_DIR})
    file(GLOB_RECURSE ASSET_FILES RELATIVE ${ASSETS_SOURCE_DIR} "${ASSETS_SOURCE_DIR}/*")
    foreach(_asset IN LISTS ASSET_FILES)
        get_filename_component(_asset_dir "${_asset}" DIRECTORY)
        if(NOT "${_asset_dir}" STREQUAL "")
            file(MAKE_DIRECTORY "${ASSETS_BINARY_DIR}/${_asset_dir}")
        endif()
        configure_file("${ASSETS_SOURCE_DIR}/${_asset}" "${ASSETS_BINARY_DIR}/${_asset}" COPYONLY)
    endforeach()

    # Also copy assets to the runtime output directory after building the main target
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${ASSETS_SOURCE_DIR}" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/Assets"
        COMMENT "Copying Assets to runtime directory for ${PROJECT_NAME}"
    )
else()
    message(STATUS "No Assets directory found at ${ASSETS_SOURCE_DIR}; skipping asset copy")
endif()

# Unit Tests Configuration
if(CRITERION_FOUND)
    message(STATUS "Criterion found - enabling unit tests")

    # Copy test resources to build directory
    file(GLOB_RECURSE TEST_RESOURCES
        ${CMAKE_SOURCE_DIR}/tests/Images/*
    )

    if(TEST_RESOURCES)
        # Create the tests/Images directory in the build location
        file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/tests/Images)

        # Copy all test resource files
        foreach(RESOURCE ${TEST_RESOURCES})
            get_filename_component(RESOURCE_NAME ${RESOURCE} NAME)
            configure_file(${RESOURCE} ${CMAKE_SOURCE_DIR}/tests/Images/${RESOURCE_NAME} COPYONLY)
        endforeach()

        message(STATUS "Copied test resources: ${TEST_RESOURCES}")
    endif()

    # Find all test files
    file(GLOB TEST_SOURCES
        ${CMAKE_SOURCE_DIR}/tests/*.cpp
    )

    # Create a single test executable containing all tests
    add_executable(MyGimp_tests ${TEST_SOURCES} ${SOURCES})
    target_compile_options(MyGimp_tests PRIVATE -fprofile-arcs -ftest-coverage)
    target_link_libraries(MyGimp_tests PRIVATE --coverage)
    # Ensure tests executable exports symbols too so dynamically-loaded libs can resolve references
    if(UNIX)
        target_link_options(MyGimp_tests PRIVATE "-rdynamic")
    endif()

    # Include directories for tests
    target_include_directories(MyGimp_tests PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src/MainApp
        ${CRITERION_INCLUDE_DIRS}
    )

    # Ensure pencils headers are visible to the tests as well
    target_include_directories(MyGimp_tests PRIVATE
        ${CMAKE_SOURCE_DIR}/src/Plugins/Pencils
    )

    # If pencil shared libs were created earlier, link them into the tests executable as well
    if(DEFINED PENCIL_LIB_TARGETS AND PENCIL_LIB_TARGETS)
        target_link_libraries(MyGimp_tests PRIVATE ${PENCIL_LIB_TARGETS})
    endif()

    # Link libraries for tests
    target_link_libraries(MyGimp_tests PRIVATE
        sfml-graphics sfml-window sfml-system
        ${CRITERION_LIBRARIES}
    )

    # Optional spdlog for tests
    if(spdlog_FOUND)
        target_link_libraries(MyGimp_tests PRIVATE spdlog::spdlog)
        target_compile_definitions(MyGimp_tests PRIVATE USE_SPDLOG)
    endif()

    # Set compilation flags for Criterion
    target_compile_options(MyGimp_tests PRIVATE ${CRITERION_CFLAGS_OTHER})
    target_link_directories(MyGimp_tests PRIVATE ${CRITERION_LIBRARY_DIRS})

    # Add single test to CTest with proper working directory
    add_test(NAME MyGimp_tests COMMAND MyGimp_tests)
    set_tests_properties(MyGimp_tests PROPERTIES
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )

    # Set test output directory
    set_target_properties(MyGimp_tests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
    )

    # After building the tests executable, copy all generated .so files into a `libs/` folder
    # located next to the test executable (e.g. `/path/to/MyGimp_tests/libs/`).
    add_custom_command(TARGET MyGimp_tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:MyGimp_tests>/libs"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_BINARY_DIR}/libs"
            "$<TARGET_FILE_DIR:MyGimp_tests>/libs"
        COMMENT "Copying Pencil .so files to $<TARGET_FILE_DIR:MyGimp_tests>/libs for MyGimp_tests"
    )

    message(STATUS "Created single test executable MyGimp_tests with sources: ${TEST_SOURCES}")
endif()
