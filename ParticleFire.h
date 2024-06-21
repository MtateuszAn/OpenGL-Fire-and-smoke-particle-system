#pragma once
#include"Mesh.h"

class ParticleFire
{
public:
	//particle transform
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	float life;//particle courent life time
	float maxLife;//particle starting life time

	ParticleFire(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float life);
	void Update(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);// updates particle transform
	bool UpdateLife(float life);// updates particle life
};

