#pragma once
#include "gl_core_4_4.h"
#include "nsfw.h"
#include "render.h"
#include "glm\glm.hpp"

#include "GameObject.h"
#include "Camera.h"

class CompPass : public nsfw::RenderPass {
public:

	nsfw::Asset<nsfw::ASSET::TEXTURE>diffusePassTex;
	nsfw::Asset<nsfw::ASSET::TEXTURE>lightPassTex;

	void prep()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(1.f, 1.f, 0.f, 1.f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(*shader);
	}

	void post() {
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST);
		glUseProgram(0);
	}

	void draw() {
		unsigned texVal = *diffusePassTex;
		setUniform("Diffuse", nsfw::UNIFORM::TEX2, &texVal, 0);
		texVal = *lightPassTex;
		setUniform("Light", nsfw::UNIFORM::TEX2, &texVal, 1);

		auto& ass = nsfw::Assets::instance();

		glBindVertexArray(ass.get<nsfw::ASSET::VAO>("Quad"));
		glDrawElements(GL_TRIANGLES, ass.get<nsfw::ASSET::VERTEX_COUNT>("Quad"), GL_UNSIGNED_INT, 0);
	}
};