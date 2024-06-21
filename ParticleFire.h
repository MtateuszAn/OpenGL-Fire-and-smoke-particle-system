#pragma once
#include"Mesh.h"

class ParticleFire
{
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	float life;
	float maxLife;

	ParticleFire(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float life);
	void Update(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	bool UpdateLife(float life);
};

