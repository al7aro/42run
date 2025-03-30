project "imgui"
    dir = "imgui/"
	kind "StaticLib"
	language "C++"

    targetdir "%{wks.location}/build/bin/%{cfg.buildcfg}/vendor/imgui"
    objdir "%{wks.location}/build/bin/%{cfg.buildcfg}/vendor/imgui"

	files {
		dir .. "imconfig.h",
		dir .. "imgui.h",
		dir .. "imgui.cpp",
		dir .. "imgui_draw.cpp",
		dir .. "imgui_internal.h",
		dir .. "imgui_widgets.cpp",
		dir .. "imstb_rectpack.h",
		dir .. "imstb_textedit.h",
		dir .. "imstb_truetype.h",
		dir .. "imgui_demo.cpp",
		dir .. "imgui_tables.cpp",
		dir .. "backends/imgui_impl_glfw.cpp",
		dir .. "backends/imgui_impl_glfw.h",
		dir .. "backends/imgui_impl_opengl3.cpp",
		dir .. "backends/imgui_impl_opengl3.h",
	}

	includedirs {
		dir,
		dir .. "backends/",
		"../glfw/glfw/include"
	}