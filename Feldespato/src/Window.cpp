#include "Window.hpp"

namespace FT {
	Window::Window(const std::string& title, unsigned int width, unsigned int height)
		: m_window(nullptr), m_title(title), m_width(width), m_height(height)
	{
		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW" << std::endl;
			return;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
#endif
#ifdef PLATFORM_MACOS
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
		if (m_window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(m_window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}

		/* OpenGL INFO */
		std::cout << "------------------------------------------------------------------------" << std::endl;
		std::cout << "OpenGL INFO:" << std::endl;
		std::cout << "" << "Vendor:\t\t\t\t" << glGetString(GL_VENDOR) << std::endl;
		std::cout << "" << "Renderer:\t\t\t" << glGetString(GL_RENDERER) << std::endl;
		std::cout << "" << "Version:\t\t\t" << glGetString(GL_VERSION) << std::endl;
		std::cout << "" << "Shading Language Version:\t" << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
		std::cout << "------------------------------------------------------------------------" << std::endl;

		double x, y;
		glfwGetCursorPos(m_window, &x, &y);
		m_mouse_pos = FT::vec2(x, y);

		// int pixel_density = 2;
		// glViewport(0, 0, width * pixel_density, height * pixel_density);
	}

	void Window::SetWindowSuffix(const std::string& suffix)
	{
		glfwSetWindowTitle(m_window, (m_title + suffix).c_str());
	}

	int Window::GetKey(int key)
	{
		return (glfwGetKey(m_window, key));
	}

	int Window::GetMouseButton(int button)
	{
		return (glfwGetMouseButton(m_window, button));
	}

	FT::vec2 Window::GetMousePosPrev()
	{
		return (m_mouse_pos);
	}

	FT::vec2 Window::GetMousePos()
	{
		double x, y;
		glfwGetCursorPos(m_window, &x, &y);
		m_mouse_pos = FT::vec2(x, y);
		return (FT::vec2(x, y));
	}

	void Window::SetInputMode(int mode)
	{
		if (glfwGetInputMode(m_window, GLFW_CURSOR) == mode)
			return;
		glfwSetInputMode(m_window, GLFW_CURSOR, mode);
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	int Window::GetWidth() const
	{
		return (m_width);
	}
	int Window::GetHeight() const
	{
		return (m_height);
	}
} // namespace FT