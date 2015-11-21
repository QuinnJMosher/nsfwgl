#pragma once
#include "glm\glm.hpp"

struct ParticleVertex
{
	glm::vec3 position;
	glm::vec3 velocity;
	float size;
	float lifeTime;
};