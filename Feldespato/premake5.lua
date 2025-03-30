project "Feldespato"
    kind "StaticLib"
    language "C++"

    targetdir "%{wks.location}/build/bin/%{cfg.buildcfg}/Feldespato"
    objdir "%{wks.location}/build/bin/%{cfg.buildcfg}/Feldespato"

    files {
        "src/**.hpp",
        "src/**.cpp"
    }

    links {
        "glad",
        "glfw",
        "imgui",
        "stb",
        "assimp",
    }

    includedirs {
        "vendor/imgui/imgui",
        "vendor/glfw/glfw/include",
        "vendor/glad/glad4.6/include",
        "vendor/glm/glm",
        "vendor/stb/stb/include",
        "vendor/assimp/assimp/include",
        'vendor/assimp/assimp/_config_headers/',
		'vendor/assimp/assimp/_config_headers/assimp/',
    }

group "vendor"
    include "vendor/assimp/premake5.lua"
    include "vendor/glad/premake5.lua"
    include "vendor/glfw/premake5.lua"
    include "vendor/imgui/premake5.lua"
    include "vendor/stb/premake5.lua"
group ""