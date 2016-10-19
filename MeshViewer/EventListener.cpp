#include "EventListener.h"



EventListener::EventListener()
{
}


EventListener::~EventListener()
{
}


void EventListener::init(GLFWwindow *window) {


}

void EventListener::poll(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_4)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // GL_FILL || GL_LINE
		glDisable(GL_CULL_FACE); // Cull triangles which normal is not towards the camera
	}

	if (glfwGetKey(window, GLFW_KEY_5)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // GL_FILL || GL_LINE
		glEnable(GL_CULL_FACE); // Cull triangles which normal is not towards the camera
		renderOption = 5.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_6)) {
		renderOption = 6.0f;

	}

}
