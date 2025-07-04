cmake_minimum_required(VERSION 3.4...3.28 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 23) # Or 14, 20, 23, etc.
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Optional, but recommended

# ---------------- COMMON ----------------

set(WORKSPACE_NAME "42run")
set(APP_NAME "42run")
set(ENGINE_NAME "Feldespato")

# COMMON OUTPUT DIRS
set(DEBUG_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin/Debug)
set(RELEASE_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin/Release)

# APP
set(APP_OUTPUT_DIRECTORY_DEBUG ${DEBUG_OUTPUT_DIR}/${APP_NAME})
set(APP_OUTPUT_DIRECTORY_RELEASE ${RELEASE_OUTPUT_DIR}/${APP_NAME})
# ENGINE
set(ENGINE_OUTPUT_DIRECTORY_DEBUG ${DEBUG_OUTPUT_DIR}/${ENGINE_NAME})
set(ENGINE_OUTPUT_DIRECTORY_RELEASE ${RELEASE_OUTPUT_DIR}/${ENGINE_NAME})

# GLAD
set(GLAD_OUTPUT_DIRECTORY_DEBUG ${DEBUG_OUTPUT_DIR}/${ENGINE_NAME}/vendor/glad)
set(GLAD_OUTPUT_DIRECTORY_RELEASE ${RELEASE_OUTPUT_DIR}/${ENGINE_NAME}/glad)
# GLFW
set(GLFW_OUTPUT_DIRECTORY_DEBUG ${DEBUG_OUTPUT_DIR}/${ENGINE_NAME}/vendor/glfw)
set(GLFW_OUTPUT_DIRECTORY_RELEASE ${RELEASE_OUTPUT_DIR}/${ENGINE_NAME}/glfw)
# IMGUI
set(IMGUI_OUTPUT_DIRECTORY_DEBUG ${DEBUG_OUTPUT_DIR}/${ENGINE_NAME}/vendor/imgui)
set(IMGUI_OUTPUT_DIRECTORY_RELEASE ${RELEASE_OUTPUT_DIR}/${ENGINE_NAME}/imgui)
# stb
set(STB_OUTPUT_DIRECTORY_DEBUG ${DEBUG_OUTPUT_DIR}/${ENGINE_NAME}/vendor/stb)
set(STB_OUTPUT_DIRECTORY_RELEASE ${RELEASE_OUTPUT_DIR}/${ENGINE_NAME}/stb)

# ----------------------------------------

project(${WORKSPACE_NAME})

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "Building on macOS")
    set(GLAD_VERSION "4.1")
    add_compile_definitions(PLATFORM_MACOS)
    set(PLATFORM_MACOS TRUE)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Building on Linux")
    set(PLATFORM_LINUX TRUE)
    set(GLAD_VERSION "4.6")
    add_compile_definitions(PLATFORM_LINUX)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Building on Windows")
    set(GLAD_VERSION "4.6")
    set(PLATFORM_WINDOWS TRUE)
    add_compile_definitions(PLATFORM_WINDOWS)
else()
    message(STATUS "Building on an unknown system: ${CMAKE_SYSTEM_NAME}")
endif()

add_compile_definitions(SANDBOX_ASSETS_DIRECTORY=\"${PROJECT_SOURCE_DIR}/42run/assets\")
add_compile_definitions(DEFAULT_ASSETS_DIRECTORY=\"${PROJECT_SOURCE_DIR}/Feldespato/default_assets\")

add_subdirectory(${ENGINE_NAME})
add_subdirectory(${APP_NAME})
