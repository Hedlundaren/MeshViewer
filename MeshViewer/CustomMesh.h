#pragma once

#include <iostream>
#include <vector>
#include "glm/glm.hpp"

#include <sstream>
#include <fstream>

#ifdef _WIN32 // Windows
#include "GL/glew.h" // determines which OpenGL extensions are supported on the target platform
#endif

#include <GLFW/glfw3.h> // creating windows and contexts

// Half-edge structure
struct HE_vert;
struct HE_edge;
struct HE_face;

struct HE_vert {
	float x, y, z; // the vertex coordinates
	HE_edge* edge; // one of the half-edges emanating from the vertex
};

struct HE_edge {
	HE_vert* vert; // vertex at the end of the half-edge
	HE_edge* pair; // oppositely oriented half-edge
	HE_face* face; // the incident face
	HE_edge* prev; // previous half-edge around the face
	HE_edge* next; // next half-edge around the face
};

struct HE_face {
	HE_edge* edge; // one of the half-edges bordering the face
};


class CustomMesh
{


public:
	CustomMesh();
	~CustomMesh();
	void loadMesh(std::string name);
	void draw();

	glm::vec3 getMinBoundingBox();
	glm::vec3 getMaxBoundingBox();
	glm::vec3 getCenter();
	

private:
	float minX, minY, minZ,
		maxX, maxY, maxZ;
	
	glm::vec3 center_point;
	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;
	std::vector<glm::vec3> normals;

	std::vector<HE_vert> HE_vertices;
	std::vector<HE_edge> HE_edged;
	std::vector<HE_face> HE_faces;

	std::vector<glm::vec3> out_vertices;
	std::vector<glm::vec3> out_normals;

	// Read m-files
	void readFile(std::string file_name, std::vector<glm::vec3> &vertices, std::vector<unsigned> &indices, std::vector<glm::vec3> &normals);
	void loadVertex(std::vector<std::string> &elements, std::vector<glm::vec3> &vertices);
	void calcCenter();
	GLuint IBO;
	GLuint vbo;
	GLuint normalbuffer;

};

