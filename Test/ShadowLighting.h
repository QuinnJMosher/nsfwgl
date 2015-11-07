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

	nsfw::Asset<nsfw::ASSET::TEXTURE>ShadowMap;

	void prep()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(0.f, 0.f, 0.f, 0.f);
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_ONE, GL_ONE);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(*shader);
	}

	void post() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST);
		glUseProgram(0);
	}

	void draw(const GameObject go, const DirectionLight &lt, const Camera* cam) {

		glm::mat4 texSpaceOff = glm::translate(.5f, .5f, .5f)*glm::scale(.5f,.5f,.5f);
		setUniform("texSpaceOff", nsfw::UNIFORM::MAT4, glm::value_ptr(texSpaceOff));

		setUniform("shadowMap", nsfw::UNIFORM::TEX2, ShadowMap, 0);

		setUniform("lightDirection", nsfw::UNIFORM::FLO3, glm::value_ptr(lt.direction));

		setUniform("lightProjection", nsfw::UNIFORM::MAT4, glm::value_ptr(lt.getProjection()));
		setUniform("lightView", nsfw::UNIFORM::MAT4, glm::value_ptr(lt.getView()));

		setUniform("Model", nsfw::UNIFORM::MAT4, glm::value_ptr(go.trasform));

		setUniform("Projection", nsfw::UNIFORM::MAT4, glm::value_ptr(cam->getProjection()));
		setUniform("View", nsfw::UNIFORM::MAT4, glm::value_ptr(cam->getView()));

		glBindVertexArray(*go.mesh);
		glDrawElements(GL_TRIANGLES, *go.tris, GL_UNSIGNED_INT, 0);
	}
};