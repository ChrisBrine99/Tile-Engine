#include "Window.h"

using namespace graphics;

int main() {
	// Create the Window and Game Loop
	Window* window = new Window("Tile Engine", 800, 600);
	window->Run();
	while (window->isRunning()) {
		window->Update();
		window->Draw();
	}
	delete window, window = nullptr;
	return 0;
}