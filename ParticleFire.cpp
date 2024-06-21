#include "ParticleFire.h"
#include "time.h"

ParticleFire::ParticleFire(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float life)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
	this->life = life;
	this->maxLife = life;
}

void ParticleFire::Update(glm::vec3 position, glm::vec3 rotation, glm::vec3 scaleMulti)
{
	this->position += position * deltaTime;
	this->rotation += rotation * deltaTime;

	// Calculate scale based on the remaining life
	if (life > 2.0f / 3.0f * maxLife) {
		// Interval from maxLife to 2/3 maxLife (scale increases from 0 to 1)
		float t = (life - 2.0f / 3.0f * maxLife) / (maxLife - 2.0f / 3.0f * maxLife);
		this->scale = glm::vec3(1.0f) * (1.0f - t);
	}
	else {
		// Interval from 2/3 maxLife to 0 (scale decreases from 1 to 0)
		float t = life / (2.0f / 3.0f * maxLife);
		this->scale = glm::vec3(1.0f) * t;
	}
	this->scale *= scaleMulti;
}

bool ParticleFire::UpdateLife(float life)
{
	this->life -= life;
	if (this->life < 0)
		return false;
	else
		return true;
}
