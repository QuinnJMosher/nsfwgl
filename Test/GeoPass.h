#pragma once
#include "gl_core_4_4.h"
#include "nsfw.h"
#include "render.h"
#include "glm\glm.hpp"

#include "GameObject.h"
#include "Camera.h"

class GeoPass : public nsfw::RenderPass {
public:

	void prep()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, *fbo);
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(*shader);
	}

	void post() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST);
		glUseProgram(0);
	}

	void draw(const GameObject &go, const Camera &cam) {
		setUniform("Projection", nsfw::UNIFORM::MAT4, glm::value_ptr(cam.getProjection()));
		setUniform("View", nsfw::UNIFORM::MAT4, glm::value_ptr(cam.getView()));

		setUniform("Model", nsfw::UNIFORM::MAT4, glm::value_ptr(go.trasform));
		unsigned texVal = *go.diffuse;
		setUniform("Diffuse", nsfw::UNIFORM::TEX2, &texVal);

		glBindVertexArray(*go.mesh);
		glDrawElements(GL_TRIANGLES, *go.tris, GL_UNSIGNED_INT, 0);
	}
};