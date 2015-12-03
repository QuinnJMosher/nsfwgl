#pragma once
#include "render.h"
#include "Assets.h"
#include "ParticleVertex.h"

class Camera;

class GPUParticleEmitter : public nsfw::RenderPass {
	
public:
	void Prep();
	void Post();
	void Draw(float time, const Camera& cam);

	void init(unsigned int in_maxParticles);
	unsigned int getMaxParticles();

	glm::vec3 position;

	float lifeSpan;
	float speed;
	//direction will be random
	float size;

	nsfw::Asset<nsfw::ASSET::VAO> model;
	nsfw::Asset<nsfw::ASSET::VERTEX_COUNT> modelVerts;
	nsfw::Asset<nsfw::ASSET::TEXTURE> tex;

private:
	nsfw::ParticleVertex* particles;
	unsigned int maxParicles;

};