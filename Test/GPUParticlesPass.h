#pragma once
#include "gl_core_4_4.h"
#include "render.h"
#include "Assets.h"
#include "ParticleVertex.h"
#include <string>
#include "Camera.h"
#include "glm\ext.hpp"

class GPUParticleEmitter : public nsfw::RenderPass {
	
public:
	void Prep() {
		glBindFramebuffer(GL_FRAMEBUFFER, *targetBuffer);
	}
	void Post() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void Update(float time, const Camera& cam) {

		//update
		shader = updateShader.name.c_str();
		glUseProgram(*updateShader);

		float deltaTime = time - lastDrawTime;
		lastDrawTime = time;

		setUniform("time", nsfw::UNIFORM::FLO1, &time);
		setUniform("deltaTime", nsfw::UNIFORM::FLO1, &deltaTime);

		setUniform("emitterPosition", nsfw::UNIFORM::FLO3, glm::value_ptr(position));
		setUniform("lifeSpan", nsfw::UNIFORM::FLO1, &lifeSpan);
		setUniform("emissionInterval", nsfw::UNIFORM::FLO1, &emmissionInterval);
		setUniform("speed", nsfw::UNIFORM::FLO1, &speed);
		setUniform("size", nsfw::UNIFORM::FLO1, &size);
		setUniform("color", nsfw::UNIFORM::FLO4, glm::value_ptr(color));
		
		glEnable(GL_RASTERIZER_DISCARD);
		if (updatingBuffer0) {
			glBindVertexArray(*VAO_0);
			glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, *VBO_1);
		} else {
			glBindVertexArray(*VAO_1);
			glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, *VBO_0);
		}

		glBeginTransformFeedback(GL_POINTS);
		glDrawArrays(GL_POINTS, 0, maxParicles);

		//cleanup Update
		glEndTransformFeedback();
		glDisable(GL_RASTERIZER_DISCARD);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, 0);

		//Draw
		shader = drawShader.name.c_str();
		glUseProgram(*drawShader);

		setUniform("Projection", nsfw::UNIFORM::MAT4, glm::value_ptr(cam.getProjection()));
		setUniform("View", nsfw::UNIFORM::MAT4, glm::value_ptr(cam.getView()));
		setUniform("CamTransform", nsfw::UNIFORM::MAT4, glm::value_ptr(cam.transform));

		if (updatingBuffer0) {
			glBindVertexArray(*VAO_1);
		}
		else 
		{
			glBindVertexArray(*VAO_0);
		}
		glDrawArrays(GL_POINT, 0, maxParicles);

		updatingBuffer0 = !updatingBuffer0;
	}

	void init(const char* in_assetName, const char* in_drawShaderName, const char* in_updatShaderName, unsigned int in_maxParticles = 100) {
		assert(in_maxParticles != 0);
		
		auto& ass = nsfw::Assets::instance();
		std::string namePrefix = in_assetName;

		ass.makeVAO(namePrefix.c_str() , in_maxParticles);
		maxParicles = in_maxParticles;
		VAO_0 = (namePrefix + "_0").c_str();
		VAO_1 = (namePrefix + "_1").c_str();
		VBO_0 = (namePrefix + "_0").c_str();
		VBO_1 = (namePrefix + "_1").c_str();

		drawShader = in_drawShaderName;
		updateShader = in_updatShaderName;

		float lastDrawTime = 0.f;

		position = glm::vec3(0.f, 0.f, 0.f);
		lifeSpan = 2.f;
		speed    = 1.f;
		size	 = 1.f;
		color	 = glm::vec4(1.f, 0.f, 0.f, 1.f);

	}
	unsigned int getMaxParticles() { return maxParicles; };

	glm::vec3 position;

	float lifeSpan;
	float emmissionInterval;
	float speed;
	//direction will be random
	float size;
	glm::vec4 color;

	nsfw::Asset<nsfw::ASSET::FBO> targetBuffer;

private:
	bool updatingBuffer0;

	nsfw::Asset<nsfw::ASSET::VAO> VAO_0;
	nsfw::Asset<nsfw::ASSET::VAO> VAO_1;

	nsfw::Asset<nsfw::ASSET::VBO> VBO_0;
	nsfw::Asset<nsfw::ASSET::VBO> VBO_1;

	nsfw::Asset<nsfw::ASSET::SHADER> updateShader;
	nsfw::Asset<nsfw::ASSET::SHADER>   drawShader;

	unsigned int maxParicles;
	//nsfw::ParticleVertex* particles;

	float lastDrawTime;

};