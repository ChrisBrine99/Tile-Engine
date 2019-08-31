#include <iostream>
#include <chrono>
#include "Window.h"

namespace graphics {
	Window::Window() { // Creates a generic window with a resolution of 640 by 480.
		m_Name = "Default Window";
		m_Width = 640;
		m_Height = 480;
		m_TargetFPS = 60.0;
		m_Running = Init();
	}

	Window::Window(const char *name, int width, int height, double targetFPS) { // Creates a unique window with user defined parameters
		m_Name = name;
		m_Width = width;
		m_Height = height;
		m_TargetFPS = targetFPS;
		m_Running = Init();
	}

	Window::~Window() { // Default Destructor

	}

	void Window::HandleEvents() { // Handles All Program Events
		// Check all events
		glfwPollEvents();

		// Check if the Window should close at the end of the update
		if (glfwWindowShouldClose(m_Window)) {
			glfwSetWindowShouldClose(m_Window, true);
			m_Running = false;
		}
	}

	void Window::Update(){ // Update Events, Handle Input, and Update Physics
		
	}

	void Window::Draw(float alpha) { // Render Everything to the Screen
		int width, height;
		glfwGetFramebufferSize(m_Window, &width, &height);
		glViewport(0, 0, width, height);

		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.5f, -0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(-0.5f, 0.5f);
		glEnd();

		glfwSwapBuffers(m_Window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::KeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods) { // Handle Keyboard Inputs
		if (action == GLFW_PRESS) { // Handling Key Presses
			if (key == GLFW_KEY_ESCAPE) {
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
		}
	}

	void Window::Run() { // The Main Program Loop
		using namespace std::chrono_literals;
		using clock = std::chrono::high_resolution_clock;
		using std::chrono::nanoseconds;
		nanoseconds const timeStep(1ms);
		nanoseconds lag(0ns);
		auto startTime = clock::now();
		// The Program Loop
		while (m_Running) {
			auto deltaTime = clock::now() - startTime;
			startTime = clock::now();
			lag += std::chrono::duration_cast<nanoseconds>(deltaTime);
			// Handle Program Events
			HandleEvents();
			// Update Physics
			while (lag >= timeStep) {
				lag -= timeStep;
				Update();
			}
			// Draw to the Screen
			auto alpha = (float)lag.count() / timeStep.count();
			Draw(alpha);
		}
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