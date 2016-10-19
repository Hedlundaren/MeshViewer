#pragma once


#include <glm/glm.hpp> // vector library
#include <GLFW/glfw3.h> // creating windows and contexts

class CubeMesh
{
public:
	CubeMesh();
	~CubeMesh();

	float min_x = -1.0f;
	float min_y = -1.0f;
	float min_z = -1.0f;
	float max_x = 1.0f;
	float max_y = 1.0f;
	float max_z = 1.0f;


	glm::vec3 box_verts[8] = { // Vertices
		glm::vec3(min_x, min_y, max_z), // 0
		glm::vec3(min_x, min_y, min_z), // 1
		glm::vec3(max_x, min_y, min_z), // 2
		glm::vec3(max_x, min_y, max_z), // 3
		glm::vec3(min_x, max_y, max_z), // 4
		glm::vec3(min_x, max_y, min_z), // 5
		glm::vec3(max_x, max_y, min_z), // 6
		glm::vec3(max_x, max_y, max_z), // 7
	};

	GLuint box_indices[24] = { // Box Lines
		0, 1, // 0
		1, 2, // 1
		2, 3, // 2
		3, 0, // 3
		0, 4, // 4
		1, 5, // 5
		2, 6, // 6
		3, 7, // 7
		4, 5, // 8
		5, 6, // 9
		6, 7, // 10
		7, 4, // 11
	};
};

