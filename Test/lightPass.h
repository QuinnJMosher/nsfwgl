#pragma once
#include "gl_core_4_4.h"
#include "nsfw.h"
#include "render.h"
#include "glm\glm.hpp"
#include "Assets.h"

#include "DirectionLight.h"
#include "Camera.h"

class LightPass : public nsfw::RenderPass {
public:

	nsfw::Asset<nsfw::ASSET::TEXTURE>PositionMap, NormalMap;

	void prep()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, *fbo);
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

	void draw(const DirectionLight &lt, const Camera &cam) {
		setUniform("Projection", nsfw::UNIFORM::MAT4, glm::value_ptr(cam.getProjection()));
		setUniform("View", nsfw::UNIFORM::MAT4, glm::value_ptr(cam.getView()));
		
		setUniform("lightDirection", nsfw::UNIFORM::FLO4, glm::value_ptr(lt.direction));
		setUniform("lightDiffuse", nsfw::UNIFORM::FLO4, glm::value_ptr(lt.color));

		unsigned texVal = *PositionMap;
		setUniform("PosMap", nsfw::UNIFORM::TEX2, &texVal);
		texVal = *NormalMap;
		setUniform("NormMap", nsfw::UNIFORM::TEX2, &texVal);

		auto& ass = nsfw::Assets::instance();

		glBindVertexArray(ass.get<nsfw::ASSET::VAO>("Quad"));
		glDrawElements(GL_TRIANGLES, ass.get<nsfw::ASSET::VERTEX_COUNT>("Quad"), GL_UNSIGNED_INT, 0);
	}
};