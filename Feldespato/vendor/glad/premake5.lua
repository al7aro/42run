project "glad"
    kind "StaticLib"
    language "C"

    targetdir "%{wks.location}/build/bin/%{cfg.buildcfg}/vendor/glad"
    objdir "%{wks.location}/build/bin/%{cfg.buildcfg}/vendor/glad/obj"

    filter "system:windows"
        files { "glad4.6/src/glad.c" }
        includedirs  { "glad4.6/include" }
    filter "system:linux"
        files { "glad4.6/src/glad.c" }
        includedirs  { "glad4.6/include" }
    filter "system:macosx"
        files { "glad4.1/src/glad.c" }
        includedirs  { "glad4.1/include" }
    filter {}