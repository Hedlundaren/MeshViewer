#pragma once

#ifdef _WIN32 // Windows
#include "GL/glew.h" // determines which OpenGL extensions are supported on the target platform
#endif

#include <GLFW/glfw3.h> // creating windows and contexts

class EventListener
{
public:
	EventListener();
	~EventListener();

	void init(GLFWwindow *window);
	void poll(GLFWwindow *window);

	float renderOption = 5.0f;


};

