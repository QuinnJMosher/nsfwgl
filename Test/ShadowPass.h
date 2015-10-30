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

		glm::vec3 cameraPos = glm::vec3(cam.transform[3][0], cam.transform[3][1], cam.transform[3][2]);
		setUniform("CameraPos", nsfw::UNIFORM::FLO3, glm::value_ptr(cameraPos));

		setUniform("lightDirection", nsfw::UNIFORM::FLO3, glm::value_ptr(lt.direction));
		setUniform("lightDiffuse", nsfw::UNIFORM::FLO3, glm::value_ptr(lt.color));

		unsigned texVal = *PositionMap;
		setUniform("PosMap", nsfw::UNIFORM::TEX2, &texVal, 0);
		texVal = *NormalMap;
		setUniform("NormMap", nsfw::UNIFORM::TEX2, &texVal, 1);

		auto& ass = nsfw::Assets::instance();

		glBindVertexArray(ass.get<nsfw::ASSET::VAO>("Quad"));
		glDrawElements(GL_TRIANGLES, ass.get<nsfw::ASSET::VERTEX_COUNT>("Quad"), GL_UNSIGNED_INT, 0);
	}
};