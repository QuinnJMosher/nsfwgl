#pragma once
#include "gl_core_4_4.h"
#include "nsfw.h"
#include "render.h"
#include "glm\glm.hpp"
#include "glm\ext.hpp"
#include "Assets.h"

#include "DirectionLight.h"
#include "GameObject.h"

class ShadowPass : public nsfw::RenderPass {
public:

	float ScrWidth, ScrHeight;
	float BufWidth, BufHeight;

	void prep()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, *fbo);
		glViewport(0, 0, BufWidth, BufHeight);
		glClearColor(0.f, 0.f, 0.f, 0.f);
		glClear(GL_DEPTH_BUFFER_BIT);

		glUseProgram(*shader);
	}

	void post() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glUseProgram(0);
		glViewport(0, 0, ScrWidth, ScrHeight);
	}

	void draw(const GameObject &go, const DirectionLight &lt) {

		setUniform("Model", nsfw::UNIFORM::MAT4, glm::value_ptr(go.trasform));
		setUniform("lightProjection", nsfw::UNIFORM::MAT4, glm::value_ptr(lt.getProjection()));
		setUniform("lightView", nsfw::UNIFORM::MAT4, glm::value_ptr(lt.getView()));

		glBindVertexArray(*go.mesh);
		glDrawElements(GL_TRIANGLES, *go.tris, GL_UNSIGNED_INT, 0);
	}
};