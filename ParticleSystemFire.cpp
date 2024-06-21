#include "ParticleSystemFire.h"

ParticleSystemFire::ParticleSystemFire(Mesh mesh, glm::vec3 startPosition, float emiterCircleSize, float emitSpeed, int maxParticles, glm::vec3 particleTransform, glm::vec3 particleScale, float partycleLifeTime)
{
	this->particleMesh = mesh;
	this->startPosition = startPosition;
	this->emiterCircleSize = emiterCircleSize;
	this->emitSpeed = emitSpeed;
	this->timeLastEmited = emitSpeed;
	this->maxParticles = maxParticles;
	this->particleTransform = particleTransform;
	this->particleScale = particleScale;
	this->partycleLifeTime = partycleLifeTime;
}

void ParticleSystemFire::Update()
{
	//Emit new Particles
	if (particleList.size() < maxParticles && timeLastEmited >= emitSpeed) {
		glm::vec3 rotation = glm::vec3(0.0f);
		glm::vec3 scale = glm::vec3(1.0f);
		particleList.push_back(ParticleFire(randPoint(), rotation, particleScale, partycleLifeTime));
		timeLastEmited = 0;
	}
	else {
		timeLastEmited += deltaTime;
	}
	//Update All particles
	auto it = particleList.begin();
	while (it != particleList.end()) {
		ParticleFire& particleFire = *it;
		// if particle life is above zero
		if (particleFire.UpdateLife(deltaTime)) {
			// UpdateParticle
			particleFire.Update(particleTransform, glm::vec3(0.0f), particleScale);
			++it; // nextParticle
		}
		else {
			// Delate Particle
			it = particleList.erase(it);
		}
	}
}

void ParticleSystemFire::Draw(Shader& shader, Camera& camer)
{
	for (ParticleFire& particleFire : particleList)
	{
		particleMesh.Draw(shader, camer, glm::mat4(1.0f),particleFire.position, particleFire.rotation, particleFire.scale);
	}
}

float ParticleSystemFire::uniform() {
	return (double)rand() / RAND_MAX;
}

glm::vec3 ParticleSystemFire::randPoint() {
	float theta = 2 * 3.142 * uniform();
	float r = sqrt(uniform());
	return glm::vec3{
		startPosition.x + r * emiterCircleSize * cos(theta),
		startPosition.y,
		startPosition.z + r * emiterCircleSize * sin(theta)
	};
}