#ifndef WINDOW_H
#define WINDOW_H

#include <glfw3.h>

namespace graphics {
	class Window {
	private:
		GLFWwindow* m_Window;

		const char *m_Name;
		int m_Width, m_Height;
		bool m_Running;
	public:
		Window(const char *name, int width, int height);
		~Window();

		void Run() const;
		void Update();
		void Draw();

		static void KeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods);

		bool isRunning();
	private:
		bool Init();
	};
}

#endif
