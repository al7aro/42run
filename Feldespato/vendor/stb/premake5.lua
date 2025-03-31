project "stb"
    dir = "stb/"
    kind "StaticLib"
    language "C"

    targetdir "%{wks.location}/build/bin/%{cfg.buildcfg}/vendor/stb"
    objdir "%{wks.location}/build/bin/%{cfg.buildcfg}/vendor/glfw/stb"

    files {
        dir .. "stb_image.c"
    }