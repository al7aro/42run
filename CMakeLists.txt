cmake_minimum_required(VERSION 3.4...3.28 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(WORKSPACE_NAME "42run")
project(${WORKSPACE_NAME})

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "Building on macOS")
    add_compile_definitions(PLATFORM_MACOS)
    set(PLATFORM_MACOS TRUE)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Building on Linux")
    set(PLATFORM_LINUX TRUE)
    add_compile_definitions(PLATFORM_LINUX)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Building on Windows")
    set(PLATFORM_WINDOWS TRUE)
    add_compile_definitions(PLATFORM_WINDOWS)
else()
    message(STATUS "Building on an unknown system: ${CMAKE_SYSTEM_NAME}")
endif()
add_compile_definitions(DEFAULT_ASSETS_DIRECTORY=\"${PROJECT_SOURCE_DIR}/src/engine/default_assets\")
add_compile_definitions(SANDBOX_ASSETS_DIRECTORY=\"${PROJECT_SOURCE_DIR}/src/42run/assets\")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${WORKSPACE_NAME})

#################### SOURCES ####################
file(GLOB_RECURSE ALL_SOURCES
    "./src/*.cpp"
    "./src/*.hpp"
    "./src/*.c"
    "./src/*.h"
)
add_executable(${WORKSPACE_NAME} ${ALL_SOURCES})
#################################################

#################### LIBS ####################
# GLAD
add_subdirectory("vendor/glad")
target_link_libraries(${WORKSPACE_NAME} glad)
target_include_directories(${WORKSPACE_NAME} PUBLIC "vendor/glad/include")
# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("vendor/glfw")
target_link_libraries(${WORKSPACE_NAME} glfw)
target_include_directories(${WORKSPACE_NAME} PUBLIC "vendor/glfw/include")
# stb
add_subdirectory("vendor/stb")
target_link_libraries(${WORKSPACE_NAME} stb)
target_include_directories(${WORKSPACE_NAME} PUBLIC "vendor/stb/include")
# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${WORKSPACE_NAME} OpenGL::GL)
##############################################