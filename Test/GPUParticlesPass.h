#pragma once
#include "render.h"

class Camera;

class GPUParticleEmitter : public nsfw::RenderPass {

	void Prep();
	void Post();
	void Draw(float time, const Camera& cam);


};