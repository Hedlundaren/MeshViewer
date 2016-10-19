#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>


#include <fstream> // m-parser
#include <sstream> // m-parser
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>

#ifdef _WIN32 // Windows
#include "GL/glew.h" // determines which OpenGL extensions are supported on the target platform
#endif

#include <GLFW/glfw3.h> // creating windows and contexts

#include <glm/glm.hpp> // vector library
#include <glm/gtc/matrix_transform.hpp> // handles matrix transforms
#include <glm/gtx/transform.hpp> // calculates view projection

#include "Rotator.hpp" // Handles rotation and movement
#include "GLShader.hpp" // Loads shaders
#include <math.h> // Mathematical expressions eg. sin(time)

#include "WindowManager.h"
#include "CustomMesh.h"

#include "EventListener.h"

float zoom = 0.0f;





/*=============================================================
====================== MAIN FUNCTIONS =========================
===============================================================*/

void scroll(GLFWwindow* window, double x, double y) {
	zoom += (float)y * 0.007f;
}


void displayFPS(int &nbFrames, double &time, double &lastTime) {
	nbFrames++;
	if (time - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
								  // printf and reset timer
		printf("%f ms/frame\n", 1000.0 / double(nbFrames));
		std::cout << std::endl << nbFrames << " FPS\n";
		nbFrames = 0;
		lastTime += 1.0;
	}
}