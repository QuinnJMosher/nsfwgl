#include "ParticleEmitter.h"
#include <random>
#include <algorithm>
#include "glm\ext.hpp"

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

	nextParticleTime = 0;
}

void ParticleEmitter::MakeParticle() {
	if (firstEmptyLocation < particleBankSize) {

		Particle newPart = Particle();

		newPart.position = startLocation;
		newPart.velocity = glm::vec4(
							glm::normalize(glm::vec3(rand() % 20 - 10, rand() % 20 - 10, rand() % 20 - 10)),
							0);
		/*newPart.velocity = glm::vec4(
			glm::normalize(glm::vec3(1, 0, 1)),
			0);*/
		newPart.velocity *= startSpeed;
		newPart.size = startSize;
		newPart.lifetime = lifeLength;

		particleBank[firstEmptyLocation] = newPart;
		firstEmptyLocation++;

		nextParticleTime = 0;
	}
}

void ParticleEmitter::Update(float in_time, bool in_forceSort) {

	bool listHasChanged = false;

	deltaTime = in_time - lastTime;
	lastTime = in_time;

	for (int i = 0; i < firstEmptyLocation; i++) {

		particleBank[i].lifetime -= deltaTime;

		if (IsParticleAlive(i)) {
			particleBank[i].position += particleBank[i].velocity * deltaTime;
		}
		else 
		{
			KillParticle(i);
			listHasChanged = true;
		}
	}

	nextParticleTime += deltaTime;

	if (nextParticleTime > intervalTime) {
		MakeParticle();
		listHasChanged = true;
	}

	if (listHasChanged || in_forceSort) {
		SortParticleBank();
	}
}

glm::mat4 ParticleEmitter::GetParticleMatrix(const unsigned in_particle) const {
	glm::vec3 pos(particleBank[in_particle].position);
	float	  scl(particleBank[in_particle].size);
	
	return glm::translate(pos) * glm::scale(scl, scl, scl);
}

bool ParticleEmitter::IsParticleAlive(const unsigned in_particle) const {
	return (particleBank[in_particle].lifetime > 0);
}

unsigned ParticleEmitter::GetFirstEmptyLocation() const {
	return firstEmptyLocation;
}

unsigned ParticleEmitter::GetBankSize() const {
	return particleBankSize;
}

//this function is either entierly moot or I'm forgetting something important
void ParticleEmitter::KillParticle(const unsigned in_particle) {
	particleBank[in_particle].lifetime = 0; 
}

void ParticleEmitter::SortParticleBank() {
	std::sort(particleBank, particleBank + particleBankSize, ParticleSrtFunc);

	int i = 0;
	while (i < particleBankSize) {
		if (!IsParticleAlive(i)) {
			firstEmptyLocation = i;
			break;
		}
		i++;
	}
}

bool ParticleEmitter::ParticleSrtFunc(Particle& left, Particle& right) {
	return left.lifetime > right.lifetime;
}