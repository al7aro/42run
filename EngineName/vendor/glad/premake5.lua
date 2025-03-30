project "glad"
    dir = "glad4.6/"
    kind "StaticLib"
    language "C"

    targetdir "%{wks.location}/build/bin/%{cfg.buildcfg}/vendor/glad"
    objdir "%{wks.location}/build/bin/%{cfg.buildcfg}/vendor/glad"

    files {
        dir .. "src/glad.c"
    }
    includedirs  {
        dir .. "include"
    }