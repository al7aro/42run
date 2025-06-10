project "42run"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"

    targetdir "%{wks.location}/build/bin/%{cfg.buildcfg}/42run"
    objdir "%{wks.location}/build/bin/%{cfg.buildcfg}/42run/obj"

    files {
        "assets/**", -- NOT SOURCES
        "src/**",
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
        "stb",
    }

    includedirs {
        "%{wks.location}/Feldespato/include",
        "%{wks.location}/Feldespato/vendor/imgui/imgui",
        "%{wks.location}/Feldespato/vendor/glfw/glfw/include",
        "%{wks.location}/Feldespato/vendor/glad/glad4.6/include",
        "%{wks.location}/Feldespato/vendor/stb/stb/include",
    }