#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>

#include"Mesh.h"

static Mesh loadOBJ(const char* fileName, std::vector <Texture> textures, glm::vec3 color = glm::vec3(1.f,1.f,1.f)) {

	//vectors of vertex portions
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texUVs;
	
	//Face vectors
	std::vector<GLint> positionsIndicies;
	std::vector<GLint> normalsIndicies;
	std::vector<GLint> texUVsIndicies;

	std::vector<Vertex> vertices;
	std::vector <GLuint> indices;

	//file
	std::stringstream ss;
	std::ifstream file(fileName);
	

	if (!file.is_open()) 
	{
		throw "ERROR loadOBJ Could not open file.";
	}

	std::string line = "";
	std::string prefix = "";

	glm::vec3 tmpV3;
	glm::vec2 tmpV2;
	GLint tmpGLint;

	GLint fcounter;

	//Read line
	while (std::getline(file, line)) 
	{
		ss.clear();
		ss.str(line);
		ss >> prefix;
		if (prefix == "v") //Vertex position
		{
			ss >> tmpV3.x >> tmpV3.y >> tmpV3.z;
			positions.push_back(tmpV3);
		}
		else if (prefix == "vt") //Vertex texture
		{
			ss >> tmpV2.x >> tmpV2.y;
			texUVs.push_back(tmpV2);
		}
		else if (prefix == "vn") //Vertex normals
		{
			ss >> tmpV3.x >> tmpV3.y >> tmpV3.z;
			normals.push_back(tmpV3);
		}
		else if (prefix == "f") //Faces
		{
			int counter = 0;
			while (ss >> tmpGLint) {
				if (counter == 0)
					positionsIndicies.push_back(tmpGLint);
				else if (counter == 1)
					texUVsIndicies.push_back(tmpGLint);
				else if (counter == 2)
					normalsIndicies.push_back(tmpGLint);
				if (ss.peek() == '/')
				{
					++counter;
					ss.ignore(1, '/');
				}else if(ss.peek() == ' ')
				{
					++counter;
					ss.ignore(1, ' ');
				}

				if (counter > 2)
					counter = 0;
			}
		}

		
	}
	vertices.resize(positionsIndicies.size(), Vertex());

	//
	for (size_t i = 0; i < vertices.size(); ++i)
	{
		indices.push_back(i);
		vertices[i].position = positions[positionsIndicies[i]-1];
		vertices[i].texUV = texUVs[texUVsIndicies[i]-1];
		vertices[i].normal = normals[normalsIndicies[i]-1];
		vertices[i].color = color;
	}

	Mesh mesh(vertices, indices, textures);

	return mesh;
}