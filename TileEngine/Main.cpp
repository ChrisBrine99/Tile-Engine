#include "Window.h"

using namespace graphics;

int main() {
	// Create the Window
	Window* window = new Window("Tile Engine", 800, 600);
	window->Run();
	delete window, window = nullptr;
	return 0;
}