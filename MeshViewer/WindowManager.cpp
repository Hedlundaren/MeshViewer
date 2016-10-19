#include "WindowManager.h"
#include <iostream>


WindowManager::WindowManager()
{
}


WindowManager::~WindowManager()
{
}

void WindowManager::createWindow(const unsigned width, const unsigned height) {
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		exit(-1);

	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // We want OpenGL 4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

	window = glfwCreateWindow(width, height, "Simon Hedlund - Mesh Viewer", NULL, NULL); // Full screen - glfwGetPrimaryMonitor()

	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		exit(-1);
	}

	glfwSetWindowPos(window, 950, 310);
	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();



	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		exit(-1);

	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glEnable(GL_CULL_FACE); // Cull triangles which normal is not towards the camera

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // GL_FILL || GL_LINE

	glEnable(GL_DEPTH_TEST); // Enable depth test

	glDepthFunc(GL_LESS); // Accept fragment if it closer to the camera than the former one

	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Enable alpha channel
}

void WindowManager::setRenderSettings() {
	
	

}