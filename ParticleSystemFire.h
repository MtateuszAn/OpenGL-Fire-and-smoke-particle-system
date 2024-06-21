#pragma once
#include "ParticleFire.h"
#include "time.h"
#include <list>

class ParticleSystemFire
{
public:
	//Emiter variables
	glm::vec3 startPosition;
	float emiterCircleSize =0.1f;
	float emitSpeed;
	//Particle variables
	Mesh particleMesh;
	int maxParticles;
	glm::vec3 particleTransform;
	glm::vec3 particleScale;
	float partycleLifeTime;

	std::vector<ParticleFire> particleList;
	float timeLastEmited = 0;


	ParticleSystemFire(Mesh mesh, glm::vec3 startPosition, float emiterCircleSize, float emitSpeed, int maxParticles, glm::vec3 particleTransform, glm::vec3 particleScale, float partycleLifeTime);
	//updates particle positions, destroys old particles and create new ones
	void Update();
	//draw particles
	void Draw(Shader& shader, Camera& camer);
private:
	float uniform();
	glm::vec3 randPoint();
};

