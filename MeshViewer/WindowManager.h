#pragma once

#ifdef _WIN32 // Windows
#include "GL/glew.h" // determines which OpenGL extensions are supported on the target platform
#endif

#include <GLFW/glfw3.h> // creating windows and contexts


class WindowManager
{
public:
	WindowManager();
	~WindowManager();
	GLFWwindow* window; // (In the accompanying source code, this variable is global)
	void createWindow(const unsigned width, const unsigned height);
	void setRenderSettings();

	float zoom = 0.0f;
};

