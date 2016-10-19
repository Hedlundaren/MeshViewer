#include "CustomMesh.h"



CustomMesh::CustomMesh()
{
}


CustomMesh::~CustomMesh()
{
}

glm::vec3 CustomMesh::getMinBoundingBox() {
	return glm::vec3(minX, minY, minZ);
}

glm::vec3 CustomMesh::getMaxBoundingBox() {
	return glm::vec3(maxX, maxY, maxZ);
}

glm::vec3 CustomMesh::getCenter() {
	return center_point;
}

void CustomMesh::loadMesh(std::string name) {
	// Load triangle
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	
	vertices.clear();
	indices.clear();
	normals.clear();
	HE_vertices.clear();

	
	HE_vert m;
	//HE_vertices.push_back(m);
	vertices.push_back(glm::vec3());
	normals.push_back(glm::vec3());
	
	float BIG = 999999999999.9f;
	maxX = -BIG;
	maxY = -BIG;
	maxZ = -BIG;
	minX = BIG;
	minY = BIG;
	minZ = BIG;

	readFile(name + ".m");

	// TODO: 
	// Render coordinate axis (pivot)
	// Render ground plane
	// Bounding box
	// Flat shading
	// Smooth shading
	// Ortographic & Perspective
	// HALF EDGE STRUCTURE
	// ...

	for (int vertex_id = 0; vertex_id < HE_vertices.size(); vertex_id++) {
		// Transfer vertices to vertexbuffer
		vertices.push_back(glm::vec3(HE_vertices[vertex_id].x, HE_vertices[vertex_id].y, HE_vertices[vertex_id].z));
		// Transfer normals to normalbuffer
		normals.push_back(glm::vec3(HE_vertices[vertex_id].nx, HE_vertices[vertex_id].ny, HE_vertices[vertex_id].nz));
	}

	// Model vertices
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float) * 3, &vertices[0], GL_STATIC_DRAW); // Give our vertices to OpenGL.
	glEnableVertexAttribArray(0); // 1rst attribute buffer : vertices
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(float) * 3,  // stride
		(void*)0			// array buffer offset
	);

	// Model normals
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1); // 3rd attribute buffer : normals
	glVertexAttribPointer(
		1,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_TRUE,                         // normalized?
		sizeof(float) * 3,                // stride
		(void*)0                          // array buffer offset
	);


	// Model indices
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

}

void CustomMesh::draw(GLFWwindow *window) {
	// Draw model
	glPointSize(2.0);
	glLineWidth(1.0);

	//Draw Object
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	//Normals
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glNormalPointer(GL_FLOAT, sizeof(glm::vec3), (void*)0);

	if (glfwGetKey(window, GLFW_KEY_3)) point_render = true; line_render = false; triangle_render = false;
	if (glfwGetKey(window, GLFW_KEY_4)) point_render = false; line_render = true; triangle_render = false;
	if (glfwGetKey(window, GLFW_KEY_5)) point_render = false; line_render = false; triangle_render = true;
	

	if ( point_render) {
		// Draw the triangles !
		glDrawElements(
			GL_POINTS,      // mode
			indices.size(),    // count
			GL_UNSIGNED_INT,   // type
			(void*)0           // element array buffer offset
		);
	}
	else if (line_render){
		// Draw the triangles !

		glDrawElements(
			GL_LINES,      // mode
			indices.size(),    // count
			GL_UNSIGNED_INT,   // type
			(void*)0           // element array buffer offset
		);

	}
	else if(triangle_render){
		// Draw the triangles !
		glDrawElements(
			GL_TRIANGLES,      // mode
			indices.size(),    // count
			GL_UNSIGNED_INT,   // type
			(void*)0           // element array buffer offset
		);
	}
}



void CustomMesh::readFile(std::string file_name) {
	std::ifstream in_file;

	in_file.open("models/" + file_name);
	std::string line;

	if (in_file.is_open())
	{
		while (getline(in_file, line))
		{
			std::istringstream iss(line); // Open string stream

			std::vector<std::string> elements; // Store elements of each row
			while (iss)
			{
				std::string sub;
				iss >> sub;
				elements.push_back(sub);
			}
			iss.str(std::string());

			// Treat vec
			if (elements.size() > 0) {

				if (elements[0] == "Face") {
	
					// Convert string to integers
					int index_1 = atoi(elements[2].c_str());
					int index_2 = atoi(elements[3].c_str());
					int index_3 = atoi(elements[4].c_str());

					// Push indices
					indices.push_back(index_1);
					indices.push_back(index_2);
					indices.push_back(index_3);
					
					// Calculate normal
					//glm::vec3 v1 = glm::vec3(HE_vertices[index_1].x, HE_vertices[index_1].y, HE_vertices[index_1].z);
					//glm::vec3 v2 = glm::vec3(HE_vertices[index_2].x, HE_vertices[index_2].y, HE_vertices[index_2].z);
					//glm::vec3 v3 = glm::vec3(HE_vertices[index_3].x, HE_vertices[index_3].y, HE_vertices[index_3].z);
					//glm::vec3 e1 = v2 - v1;
					//glm::vec3 e2 = v3 - v1;
					//glm::vec3 normal = glm::normalize(glm::cross(e1, e2));

					//normals.push_back(normal);
					//normals.push_back(normal);
					//normals.push_back(normal);
					

				}

				else if (elements[0] == "Vertex") {
					//std::cout << elements[0] << ": " << elements[2] << " " << elements[3] << " " << elements[4] << std::endl;

					loadVertex(elements, vertices);
				}
			}


		}
		in_file.close();
		calcCenter();
	}
}


void CustomMesh::loadVertex(std::vector<std::string> &elements, std::vector<glm::vec3> &vertices) {
	if (elements[2] == "0") elements[2] = "0.0";
	if (elements[3] == "0") elements[3] = "0.0";
	if (elements[4] == "0") elements[4] = "0.0";

	float x = atof(elements[2].c_str());
	float y = atof(elements[3].c_str());
	float z = atof(elements[4].c_str());

	if (x < minX) minX = x;
	if (y < minY) minY = y;
	if (z < minZ) minZ = z;
	if (x > maxX) maxX = x;
	if (y > maxX) maxY = y;
	if (z > maxX) maxZ = z;

	// HE vertices
	HE_vert v;
	v.x = atof(elements[2].c_str());
	v.y = atof(elements[3].c_str());
	v.z = atof(elements[4].c_str());

	glm::vec3 normal = glm::normalize(glm::vec3(v.x, v.y, v.z));

	v.nx = normal.x;
	v.ny = normal.y;
	v.nz = normal.z;

	HE_vertices.push_back(v);
}

void CustomMesh::calcCenter() {
	float x = (minX + maxX) / 2.0f;
	float y = (minY + maxY) / 2.0f;
	float z = (minZ + maxZ) / 2.0f;
	center_point = glm::vec3(x, y, z);
}
