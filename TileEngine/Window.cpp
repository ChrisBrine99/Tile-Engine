#include <iostream>
#include <sstream>
#include <chrono>

#include "Window.h"

namespace graphics {
	Window::Window() { // Creates a generic window with a resolution of 640 by 480.
		m_Name = "Default Window";
		m_Width = 640;
		m_Height = 480;
		m_Running = Init();
	}

	Window::Window(const char *name, int width, int height) { // Creates a unique window with user defined parameters
		m_Name = name;
		m_Width = width;
		m_Height = height;
		m_Running = Init();
	}

	Window::~Window() { // Default Deconstructor
		glfwTerminate();
	}

	void Window::HandleEvents() { // Handles All Program Events
		// Check all events
		glfwPollEvents();

		// Handle Keyboard Input
		if (key[GLFW_KEY_ESCAPE]) {
			glfwSetWindowShouldClose(m_Window, true);
			std::cout << "PRESSED!" << std::endl;
		}

		// Check if the Window should close at the end of Handling Events
		if (glfwWindowShouldClose(m_Window)) {
			m_Running = false;
		}
	}

	void Window::Update(double deltaTime){ // Update Events, Handle Input, and Update Physics
		
	}

	void Window::Draw() { // Render Everything to the Screen
		glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
		// Clearing the Screen
		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Swap the currently displayed buffer
		glfwSwapBuffers(m_Window);
	}

	void Window::Run() { // The Main Program Loop
		double curTime = glfwGetTime();
		double lastTime = glfwGetTime();
		double deltaTime;
		while (m_Running) {
			curTime = glfwGetTime();
			deltaTime = curTime - lastTime;

			HandleEvents();		// Handle Program Events
			Update(deltaTime);	// Update Physics
			Draw();				// Render to Screen

			lastTime = curTime;

			// Display the Frame Rate on the Window's Title
			std::ostringstream title;
			title << m_Name << " (" << (int) (1.0f / deltaTime) << " FPS)";
			glfwSetWindowTitle(m_Window, title.str().c_str());
		}
	}

	void Window::KeyEvent(GLFWwindow *window, int key_, int scancode, int action, int mods) { // Handle Keyboard Inputs
		Window* window_ = (Window*) glfwGetWindowUserPointer(window);
		if (action == GLFW_PRESS) { // Handling Key Presses
			window_->key[key_] = true;
		} else if (action == GLFW_RELEASE) { // Handling Key Releases
			window_->key[key_] = false;
		}
	}

	void Window::MouseEvent(GLFWwindow *window, int button_, int action, int mods) {
		Window* window_ = (Window*)glfwGetWindowUserPointer(window);
		if (action == GLFW_PRESS) { // Handling Mouse Presses
			window_->button[button_] = true;
		} else if (action == GLFW_RELEASE) { // Handling Mouse Releases
			window_->button[button_] = false;
		}
	}

	void Window::MouseMoved(GLFWwindow *window, double x, double y) {
		Window* window_ = (Window*)glfwGetWindowUserPointer(window);
		window_->mouseX = x;
		window_->mouseY = y;
	}

	bool Window::Init() { // Initalizes the Window and GLEW Framework
		if (!glfwInit()) { // Terminate the program if glfw cannot initialize
			std::cout << "Could not initialize GLFW Libraries" << std::endl;
			return false;
		}
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Name, NULL, NULL);
		if (!m_Window) { // Terminate the program if the window could not be created
			std::cout << "Failed to create GLFW Window" << std::endl;
			return false;
		}
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowSizeLimits(m_Window, m_Width, m_Height, m_Width, m_Height);
		glfwSetWindowUserPointer(m_Window, this);
		// Setting up keyboard input, mouse input, and mouse motion tracking
		glfwSetKeyCallback(m_Window, KeyEvent);
		glfwSetMouseButtonCallback(m_Window, MouseEvent);
		glfwSetCursorPosCallback(m_Window, MouseMoved);
		if (glewInit() != GLEW_OK) {// Terminate the program if glew cannot initialize
			std::cout << "Could not initialize GLEW Extension Libraries" << std::endl;
			return false;
		}
		// Display some information about the current OpenGL version to the console
		std::cout << "OpenGL Version " << glGetString(GL_VERSION) << std::endl;
		return true;
	}
}