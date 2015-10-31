#pragma once
#include "gl_core_4_4.h"
#include "nsfw.h"
#include "render.h"
#include "glm\glm.hpp"
#include "Assets.h"

#include "DirectionLight.h"
#include "Camera.h"
#include "GameObject.h"

class ShadowLightPass : public nsfw::RenderPass {
public:

	nsfw::Asset<nsfw::ASSET::TEXTURE>PositionMap, NormalMap, ShadowMap;

	void prep()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(0.f, 0.f, 0.f, 0.f);
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(*shader);
	}

	void post() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_BLEND);
		glUseProgram(0);
	}

	glm::mat4 texSpaceOff(0.5f, 0.0f, 0.0f, 0.0f,
						  0.0f, 0.5f, 0.0f, 0.0f,
						  0.0f, 0.0f, 0.5f, 0.0f,
						  0.5f, 0.5f, 0.5f, 1.0f);

	void draw(const DirectionLight &lt, const Camera &cam) {

		setUniform("lightDirection", nsfw::UNIFORM::FLO3, glm::value_ptr(lt.direction));

		setUniform("lightProjection", nsfw::UNIFORM::MAT4, glm::value_ptr(lt.getProjection()));
		setUniform("lightView", nsfw::UNIFORM::MAT4, glm::value_ptr(lt.getView()));

		auto& ass = nsfw::Assets::instance();

		glBindVertexArray(ass.get<nsfw::ASSET::VAO>("Quad"));
		glDrawElements(GL_TRIANGLES, ass.get<nsfw::ASSET::VERTEX_COUNT>("Quad"), GL_UNSIGNED_INT, 0);
	}
};