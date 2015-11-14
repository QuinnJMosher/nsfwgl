#include "ParticleEmitter.h"
#include <random>

void ParticleEmitter::init(const unsigned in_bankSize) {
	
	assert(in_bankSize != 0);

	particleBankSize = in_bankSize;
	particleBank = new Particle[in_bankSize];

	particleModel = "Cube";
	particleTris  = "Cube";
	particleTex   = "Cyan";

	startLocation = glm::vec4(0, 0, 0, 1);
	startSpeed    = 1.f;
	startSize	  = 1.f;
	lifeLength    = 10.f;
	intervalTime  = 1.f;

	firstEmptyLocation = 0;

	lastTime  = 0;
	deltaTime = 0;

	nextParticleTime = intervalTime;
}

void ParticleEmitter::MakeParticle() {
	if (firstEmptyLocation < particleBankSize) {

		Particle newPart = Particle();

		newPart.position = startLocation;
		newPart.velocity = glm::vec4(
							glm::normalize(glm::vec3(rand() % 10, rand() % 10, rand() % 10)),
							0);
		newPart.size = startSize;
		newPart.lifetime = lifeLength;

		particleBank[firstEmptyLocation] = newPart;
		firstEmptyLocation++;

		nextParticleTime = intervalTime;
	}
}

void ParticleEmitter::Update(float in_time) {

	deltaTime = in_time - lastTime;
	lastTime = in_time;

	for (int i = 0; i < particleBankSize; i++) {

	}

}
