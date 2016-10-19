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
	out_vertices.clear();
	vertices.clear();
	indices.clear();
	normals.clear();


	vertices.push_back(glm::vec3());
	
	HE_vert m;
	HE_vertices.push_back(m);
	
	float BIG = 999999999999.9f;
	maxX = -BIG;
	maxY = -BIG;
	maxZ = -BIG;
	minX = BIG;
	minY = BIG;
	minZ = BIG;

	readFile(name + ".m", vertices, indices, normals);

	/*===================
	Bunny Debug
	verts: 40003
	faces: 80000
	=====================*/
	std::cout << "vertices size: " << vertices.size() << std::endl <<
		"normals size: " << normals.size() << std::endl <<
		"indices size: " << indices.size() << std::endl <<
		"ratio : " << (float) indices.size() / (float)vertices.size() << std::endl << std::endl;

	// Model vertices
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW); // Give our vertices to OpenGL.
	glEnableVertexAttribArray(0); // 1rst attribute buffer : vertices	
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Model normals
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glEnableVertexAttribArray(1); // 3rd attribute buffer : normals
	glVertexAttribPointer(
		1,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_TRUE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);


	// Model indices
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	

	


	std::cout << vertices[0].y << std::endl;
	std::cout << indices[0] << std::endl;
	std::cout << normals[0].x << std::endl;

}

void CustomMesh::draw() {
	// Draw model
	glPointSize(25.0);
	glLineWidth(1.0);

	//Draw Object
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	//vertices
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	//Normals
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glNormalPointer(GL_FLOAT, sizeof(glm::vec3), (void*)0);

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,      // mode
		indices.size(),    // count
		GL_UNSIGNED_INT,   // type
		(void*)0           // element array buffer offset
	);

	
}



void CustomMesh::readFile(std::string file_name, std::vector<glm::vec3> &vertices, std::vector<unsigned> &indices, std::vector<glm::vec3> &normals) {
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
					
					glm::vec3 e1;
					glm::vec3 e2;

					e1 = vertices[index_2] - vertices[index_1];
					e2 = vertices[index_3] - vertices[index_1];

					// Calculate normal
					glm::vec3 normal = glm::normalize(glm::cross(e1, e2));

					normals.push_back(normal);
					normals.push_back(normal);
					normals.push_back(normal);




					

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

	if (elements[2] == "0.0" && elements[3] == "0.0" && elements[4] == "0.0") std::cout << "HEJEEJEJEJE " << elements[1] << std::endl;
	vertices.push_back(glm::vec3(x, y, z));

	// HE vertices
	HE_vert v;
	v.x = atof(elements[2].c_str());
	v.y = atof(elements[3].c_str());
	v.z = atof(elements[4].c_str());
	HE_vertices.push_back(v);


}

void CustomMesh::calcCenter() {
	float x = (minX + maxX) / 2.0f;
	float y = (minY + maxY) / 2.0f;
	float z = (minZ + maxZ) / 2.0f;
	center_point = glm::vec3(x, y, z);
}
