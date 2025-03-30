#pragma once

#include <iostream>
#include <string>

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace FT {
	class Window
	{
	private:
		GLFWwindow* m_window;
		std::string m_title;
		unsigned int m_width;
		unsigned int m_height;
		glm::vec2 m_mouse_pos;
	public:
		Window() = delete;
		Window(const std::string & title, unsigned int width, unsigned int height);
		~Window();
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		bool ShouldClose() { return(glfwWindowShouldClose(m_window)); }
		void PollEvents() { glfwPollEvents(); }
		void SwapBuffers() { glfwSwapBuffers(m_window); }

		void SetWindowSuffix(const std::string & suffix);

		int GetKey(int key);
		glm::vec2 GetMousePosPrev();
		glm::vec2 GetMousePos();
		int GetMouseButton(int button);

		void SetInputMode(int mode);
	};
} // namespace FT