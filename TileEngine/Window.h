#ifndef WINDOW_H
#define WINDOW_H

#include <glew.h>
#include <glfw3.h>

namespace graphics {
	class Window {
	public:
		bool key[GLFW_KEY_LAST] = { false };				// Checks Which Key Is Currently Being Pressed/Held Down/Released
		bool button[GLFW_MOUSE_BUTTON_LAST] = { false };	// Checks Which Mouse Buttons are Currently Pressed/Held Down/Released
		double mouseX, mouseY;								// The Position of the Mouse Cursor On Screen
	private:
		GLFWwindow* m_Window;

		const char *m_Name;			// The Name That Appears on the Window
		int m_Width, m_Height;		// The Width and Height of the Window
		bool m_Running;				// Lets the Program Know When To Terminate
	public:
		Window();											// Default Constructor
		Window(const char *name, int width, int height);	// User-Defined Constructor
		~Window();											// Default Deconstructor

		void HandleEvents();			// Handles All Program Events
		void Update(double deltaTime);	// Updates Object Physics
		void Draw();					// Render Everything to the Screen
		void Run();						// The Main Program Loop

		static void KeyEvent(GLFWwindow *window, int key_, int scancode, int action, int mods);	// Takes In Keyboard Input
		static void MouseEvent(GLFWwindow *window, int button_, int action, int mods);			// Takes In Mouse Input
		static void MouseMoved(GLFWwindow *window, double x, double y);							// Gets the Mouse's Posiiton on Screen
	private:
		bool Init();	// Initializes the Window
	};
}

#endif
