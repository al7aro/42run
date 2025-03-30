project "GLFW"
    dir = "glfw/"
	kind "StaticLib"
	language "C"

    targetdir "%{wks.location}/build/bin/%{cfg.buildcfg}/vendor/glfw"
    objdir "%{wks.location}/build/bin/%{cfg.buildcfg}/vendor/glfw"

	files {
		dir .. "include/GLFW/glfw3.h",
		dir .. "include/GLFW/glfw3native.h",
		dir .. "src/glfw_config.h",
		dir .. "src/context.c",
		dir .. "src/init.c",
		dir .. "src/input.c",
		dir .. "src/monitor.c",
		dir .. "src/vulkan.c",
		dir .. "src/window.c"
	}

	filter "system:windows"
		files {
			dir .. "src/win32_init.c",
			dir .. "src/win32_joystick.c",
			dir .. "src/win32_monitor.c",
			dir .. "src/win32_time.c",
			dir .. "src/win32_thread.c",
			dir .. "src/win32_window.c",
			dir .. "src/wgl_context.c",
			dir .. "src/egl_context.c",
			dir .. "src/osmesa_context.c"
		}

		defines  {
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}
