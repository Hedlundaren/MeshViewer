/*============ MESH VIEWER ================
This program is written by Simon Hedlund
Matric no: N1603915E
Latest update: 10/10/2016
System: Windows 10
GLversion: v4.3
==========================================*/

#include "main_includes.h"
#define WIDTH 1580
#define HEIGHT 1000

int main() {

	std::cout << "=====================\n";
	std::cout << "==== Mesh Viewer ====\n";
	std::cout << "=====================\n\n";

	WindowManager wm;
	wm.createWindow(WIDTH, HEIGHT);

	//Generate rotator
	MouseRotator rotator;
	rotator.init(wm.window);
	KeyTranslator trans;
	trans.init(wm.window);

	std::string model_name;
	model_name = "bunny";
	CustomMesh model;
	model.loadMesh(model_name);

	std::cout << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Language version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	// Shader programs
	GLuint program = LoadShader("shader.vert", "shader.frag");
	glUseProgram(program);


	// Uniforms
	GLint myLoc = glGetUniformLocation(program, "time");
	GLint myLoc2 = glGetUniformLocation(program, "renderOption");

	// Event listeners
	EventListener e;
	e.init(wm.window);

	double time = 0.0;
	double lastTime = 0.0;
	int nbFrames = 0;
	glm::vec3 center_pos = glm::vec3();

	/*===================================================
	==================== MAIN LOOP ======================
	====================================================*/
	do {
		time = glfwGetTime();

		//displayFPS(nbFrames, time, lastTime);

		e.poll(wm.window);

		// Rotator
		rotator.poll(wm.window);
		//std::cout << "theta: "<< rotator.theta << " phi: " << rotator.phi << std::endl;

		// Background color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float waveBG = .1f * sin(time) + .5f;
		glClearColor(waveBG, 0.0f,  0.3f, 1.0f);

		// Send Uniforms
		GLint MV_Loc, P_Loc, lDir_Loc, camDir_Loc = -1;
		glProgramUniform1f(program, myLoc, time);
		glProgramUniform1f(program, myLoc2, e.renderOption);

		MV_Loc = glGetUniformLocation(program, "MV");
		P_Loc = glGetUniformLocation(program, "P");
		lDir_Loc = glGetUniformLocation(program, "lDir");

		glm::mat4 MV, P;
		glm::mat4 M = glm::mat4(1.0f);

		float max_bound = glm::max(model.getMaxBoundingBox().x, model.getMaxBoundingBox().y) / 1000.0f;
		float trans_speed = max_bound * 600.0f;
		float zoom_speed = 0.3f;

		trans.poll(wm.window);
		glm::mat4 VRotX = glm::rotate(M, -rotator.phi, glm::vec3(0.0f, 1.0f, 0.0f)); //Rotation about y-axis
		glm::mat4 VRotY = glm::rotate(M, -rotator.theta, glm::vec3(1.0f, 0.0f, 0.0f)); //Rotation about x-axis
		glm::mat4 VTrans = glm::translate(M, glm::vec3( rotator.transX * trans_speed + trans.horizontal * trans_speed, rotator.transY * trans_speed, 0.0f));
		float scale_factor = 1.0f / 2000.0f;
		glm::mat4 VScale = glm::scale(M, glm::vec3(scale_factor));
		glm::vec4 eye_position = VRotX * VRotY / VScale * glm::vec4(0.0f, 0.0f, 3 * (max_bound), 1.0f);
		glm::mat4 V = VTrans * glm::lookAt(glm::vec3(eye_position), model.getCenter(),
			glm::vec3(0.0f, -1.0f, 0.0f));

		glfwSetScrollCallback(wm.window, scroll);
		P = glm::perspectiveFov(50.0f + zoom + trans.zoom *zoom_speed + rotator.zoom, static_cast<float>(WIDTH), static_cast<float>(HEIGHT), 0.1f, 100000.0f);
		
		float a = 0.01f;
		float b = +zoom + trans.zoom *zoom_speed + rotator.zoom;
		//P = glm::ortho(-10.0f*a + b, 10.0f*a + b, -10.0f*a + b, 10.0f*a + b);
		MV = V * M;

		//Calculate light direction
		glm::vec3 lDir = glm::vec3(1.0f, sin(time), 0.0f);

		//Send uniform variables to shaders
		glUniformMatrix4fv(MV_Loc, 1, GL_FALSE, &MV[0][0]);
		glUniformMatrix4fv(P_Loc, 1, GL_FALSE, &P[0][0]);
		glUniform3fv(lDir_Loc, 1, &lDir[0]);

		model.draw(wm.window);

		wm.setRenderSettings();
		
		glfwSwapInterval(0); // Sleep between swaps
		glfwSwapBuffers(wm.window); // Swap buffers
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(wm.window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(wm.window) == 0);


	//Clean up
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	return 0;
}




