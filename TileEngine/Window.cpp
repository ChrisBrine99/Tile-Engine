#include <iostream>

#include "Window.h"

namespace graphics {
	Window::Window(const char *name, int width, int height) {
		m_Name = name;
		m_Width = width;
		m_Height = height;
		m_Running = Init();
	}

	Window::~Window() {
		delete m_Window, m_Window = nullptr;
	}

	void Window::Update(){
		// Check all events
		glfwPollEvents();

		// Check if the Window should close at the end of the update
		if (glfwWindowShouldClose(m_Window)) {
			glfwSetWindowShouldClose(m_Window, true);
			m_Running = false;
		}
	}

	void Window::Draw() {
		int width, height;
		glfwGetFramebufferSize(m_Window, &width, &height);
		glViewport(0, 0, width, height);



		glfwSwapBuffers(m_Window);
	}

	void Window::KeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods) {
		if (action == GLFW_PRESS) { // Handling Key Presses
			if (key == GLFW_KEY_ESCAPE) {
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
		}
	}

	bool Window::isRunning() {
		return m_Running;
	}

	bool Window::Init() { // Initalizes the Window
		if (!glfwInit()) { // Terminate the program if glfw cannot initialize
			return false;
		}
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Name, NULL, NULL);
		if (!m_Window) { // Terminate the program if the window could not be created
			std::cout << "Failed to create GLFW Window" << std::endl;
			return false;
		}
		glfwMakeContextCurrent(m_Window);
		glfwSetKeyCallback(m_Window, KeyEvent);
		return true;
	}
}