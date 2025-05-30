project "Feldespato"
    kind "StaticLib"
    language "C++"
    cppdialect "C++23"

    targetdir "%{wks.location}/build/bin/%{cfg.buildcfg}/Feldespato"
    objdir "%{wks.location}/build/bin/%{cfg.buildcfg}/Feldespato/obj"

    files {
        "default_assets/**", -- NOT SOURCES
        "include/*.hpp",
        "src/**.hpp",
        "src/**.cpp"
    }

    includedirs {
        "vendor/imgui/imgui",
        "vendor/glfw/glfw/include",
        "vendor/glad/glad4.6/include",
        "vendor/glm/glm",
        "vendor/stb/stb/include",
        "vendor/assimp/assimp/include",
        "vendor/assimp/_config_headers/",
		"vendor/assimp/_config_headers/assimp/",
    }

group "vendor"
    include "vendor/assimp/premake5.lua"
    include "vendor/glad/premake5.lua"
    include "vendor/glfw/premake5.lua"
    include "vendor/imgui/premake5.lua"
    include "vendor/stb/premake5.lua"
group ""