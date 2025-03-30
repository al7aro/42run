project "AppName"
    kind "ConsoleApp"
    language "C++"

    targetdir "%{wks.location}/build/bin/%{cfg.buildcfg}/AppName"
    objdir "%{wks.location}/build/bin/%{cfg.buildcfg}/AppName"

    files {
        "src/**.hpp",
        "src/**.cpp"
    }

    links {
        "EngineName",
        "OpenGL32"
    }

    includedirs {
        "%{wks.location}/EngineName/vendor/imgui/imgui",
        "%{wks.location}/EngineName/vendor/glfw/glfw/include",
        "%{wks.location}/EngineName/vendor/glad/glad4.6/include",
        "%{wks.location}/EngineName/vendor/glm/glm",
        "%{wks.location}/EngineName/vendor/stb/stb/include",
    }