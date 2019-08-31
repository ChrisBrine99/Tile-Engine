#ifndef WINDOW_H
#define WINDOW_H

#include <glfw3.h>

namespace graphics {
	class Window {
	private:
		GLFWwindow* m_Window;

		const char *m_Name;
		int m_Width, m_Height;
		double m_TargetFPS;
		bool m_Running;
	public:
		Window();															// Default Constructor
		Window(const char *name, int width, int height, double TargetFPS);	// User-Defined Constructor
		~Window();															// Default Deconstructor

		void Run();				// The Main Program Loop
		void HandleEvents();	// Handles All Program Events
		void Update();			// Updates Object Physics
		void Draw(float alpha); // Render Everything to the Screen

		static void KeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods);	// Takes In Keyboard Input
	private:
		bool Init();	// Initializes the Game Window
	};
}

#endif
