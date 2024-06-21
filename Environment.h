#pragma once
#include"Mesh.h"
#include"OBJLoader.h"

class Environment
{
public:
	glm::mat4 matrix = glm::mat4(1.0f);
	glm::vec3 translation = glm::vec3(0.0f, -0.05f, 0.0f);
	glm::quat rotation = glm::angleAxis(glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // 180-degree rotation around the X-axis
	glm::vec3 scale = glm::vec3(0.5f, 0.5f, 0.5f);

	std::vector<Mesh> MeshList;

	Environment();
	void Draw(Shader& shader, Camera& camera);

};

