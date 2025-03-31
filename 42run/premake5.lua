project "42run"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"

    targetdir "%{wks.location}/build/bin/%{cfg.buildcfg}/42run"
    objdir "%{wks.location}/build/bin/%{cfg.buildcfg}/42run/obj"

    files {
        "src/**.hpp",
        "src/**.cpp"
    }

    filter "system:linux"
        links { "GL", "X11" }
    filter "system:macosx"
        links { "-framework OpenGL" }
    filter {}

    links {
        "Feldespato",
        "imgui",
        "glfw",
        "glad",
        "assimp",
        "stb",
    }

    includedirs {
        "%{wks.location}/Feldespato/include",
        "%{wks.location}/Feldespato/vendor/imgui/imgui",
        "%{wks.location}/Feldespato/vendor/glfw/glfw/include",
        "%{wks.location}/Feldespato/vendor/glad/glad4.6/include",
        "%{wks.location}/Feldespato/vendor/glm/glm",
        "%{wks.location}/Feldespato/vendor/stb/stb/include",
        "%{wks.location}/Feldespato/vendor/assimp/assimp/include",
        "%{wks.location}/Feldespato/vendor/assimp/_config_headers/",
		"%{wks.location}/Feldespato/vendor/assimp/_config_headers/assimp/",
    }