#include <glfw3.h>
#include <iostream>

int main() {
	if (!glfwInit()) { // Terminate the program if glfw cannot initialize
		std::cout << "Cannot Initialize" << std::endl;
		system("PAUSE");
		return 0;
	}
	return 0;
}