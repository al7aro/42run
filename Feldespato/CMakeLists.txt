cmake_minimum_required(VERSION 3.4...3.28 FATAL_ERROR)

project(${ENGINE_NAME}
    LANGUAGES CXX
)

set(PROJECT_DIR ${CMAKE_SOURCE_DIR}/${ENGINE_NAME})
set(VENDOR_DIR ${PROJECT_DIR}/vendor)

# GLAD
set(GLAD_CMAKE_DIR ${VENDOR_DIR}/glad)
add_subdirectory(${GLAD_CMAKE_DIR})

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_CMAKE_DIR ${VENDOR_DIR}/glfw)
add_subdirectory(${GLFW_CMAKE_DIR})

# IMGUI
set(IMGUI_CMAKE_DIR ${VENDOR_DIR}/imgui)
add_subdirectory(${IMGUI_CMAKE_DIR})

# STB
set(STB_CMAKE_DIR ${VENDOR_DIR}/stb)
add_subdirectory(${STB_CMAKE_DIR})

# STB
set(ASSIMP_CMAKE_DIR ${VENDOR_DIR}/assimp)
add_subdirectory(${ASSIMP_CMAKE_DIR})

# OpenGL
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE ALL_SOURCES
    "./src/*.cpp"
    "./src/*.hpp"
    "./src/*.h"
	
	"./include/*.hpp"
	"./include/*.h"
)

foreach (src ${ALL_SOURCES})
    get_filename_component(dir ${src} DIRECTORY)
	string(REPLACE "${PROJECT_SOURCE_DIR}/./" "" desired_portion ${dir})
    source_group(${desired_portion} FILES ${src})
endforeach()

add_library(${ENGINE_NAME}
    STATIC
    ${ALL_SOURCES}
)

set_target_properties(${ENGINE_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${ENGINE_OUTPUT_DIRECTORY_DEBUG}
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${ENGINE_OUTPUT_DIRECTORY_DEBUG}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${ENGINE_OUTPUT_DIRECTORY_DEBUG}

    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${ENGINE_OUTPUT_DIRECTORY_RELEASE}
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${ENGINE_OUTPUT_DIRECTORY_RELEASE}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${ENGINE_OUTPUT_DIRECTORY_RELEASE}
	
	FOLDER ${WORKSPACE_NAME}/
)

# Libraries
target_link_libraries(${ENGINE_NAME} glfw)
target_link_libraries(${ENGINE_NAME} glad)
target_link_libraries(${ENGINE_NAME} imgui)
target_link_libraries(${ENGINE_NAME} stb)
target_link_libraries(${ENGINE_NAME} assimp)
target_link_libraries(${ENGINE_NAME} OpenGL::GL)

# Headers
target_include_directories(${ENGINE_NAME} PUBLIC "${PROJECT_DIR}/src")
target_include_directories(${ENGINE_NAME} PUBLIC "${IMGUI_CMAKE_DIR}/imgui")
target_include_directories(${ENGINE_NAME} PUBLIC "${GLFW_CMAKE_DIR}/glfw/include")
target_include_directories(${ENGINE_NAME} PUBLIC "${GLAD_CMAKE_DIR}/glad"${GLAD_VERSION}"/include")
target_include_directories(${ENGINE_NAME} PUBLIC "${STB_CMAKE_DIR}/stb/include")
target_include_directories(${ENGINE_NAME} PUBLIC "${ASSIMP_CMAKE_DIR}/assimp/include")
