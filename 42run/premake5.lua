project "42run"
    kind "ConsoleApp"
    language "C++"

    targetdir "%{wks.location}/build/bin/%{cfg.buildcfg}/42run"
    objdir "%{wks.location}/build/bin/%{cfg.buildcfg}/42run"

    files {
        "src/**.hpp",
        "src/**.cpp"
    }

    links {
        "Feldespato",
        "OpenGL32"
    }

    includedirs {
        "%{wks.location}/Feldespato/vendor/imgui/imgui",
        "%{wks.location}/Feldespato/vendor/glfw/glfw/include",
        "%{wks.location}/Feldespato/vendor/glad/glad4.6/include",
        "%{wks.location}/Feldespato/vendor/glm/glm",
        "%{wks.location}/Feldespato/vendor/stb/stb/include",
    }