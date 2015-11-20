#pragma once
#include "glm\glm.hpp"
#include "Assets.h"

class Camera;

class ParticleEmitter {

public:
	nsfw::Asset<nsfw::ASSET::VAO>particleModel;
	nsfw::Asset<nsfw::ASSET::VERTEX_COUNT>particleTris;
	nsfw::Asset<nsfw::ASSET::TEXTURE>particleTex;

	glm::vec4 startLocation;
	float	  startSpeed;
	float	  startSize;
	float	  lifeLength;
	//entirely random direction for now
	float	  intervalTime;

	void init(const unsigned in_bankSize = 100); //asserts in_bankSize != 0;

	void MakeParticle();
	void Update(float in_time, bool in_forceSort = false);

	glm::mat4 GetParticleMatrix(const unsigned in_particle) const;
	bool IsParticleAlive(const unsigned in_particle) const;
	unsigned GetFirstEmptyLocation() const;
	
	unsigned GetBankSize() const;

	void SetBilboardContext(Camera* in_cam);

private:
	//bank management
	void KillParticle(const unsigned in_particle);

	void SortParticleBank();
	unsigned  firstEmptyLocation;

	//timeManagement
	float lastTime;
	float deltaTime;

	//bilboarding
	Camera* bilboardCam;

	float nextParticleTime; //ammount of time since last particle was emited

	struct Particle
	{
		Particle() {
			size = 0;
			lifetime = 0;
		}
		glm::vec4 position;
		glm::vec4 velocity;
		float	  size;
		float	  lifetime;
	};
	static bool ParticleSrtFunc(Particle& left, Particle& right);

	unsigned  particleBankSize;
	Particle* particleBank;
};