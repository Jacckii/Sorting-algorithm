#pragma once
#include <GLFW/glfw3.h>

class GUI
{
public:
	GUI();
	~GUI();
	void Draw();
private:
	GLFWwindow* window;
};

