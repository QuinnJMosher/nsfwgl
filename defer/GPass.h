#pragma once

#include "../nsfwgl/nsfw.h"

#include "Camera.h"
#include "Geometry.h"
#include "../nsfwgl/gl_core_4_4.h"

class GPass : public nsfw::RenderPass
{


public:	
	void prep() { 
		glEnable(GL_DEPTH_TEST);
		glBindFramebuffer(GL_FRAMEBUFFER, *fbo);
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(*shader);
		//TODO_D("glUseProgram, glClear, glBindFrameBuffer, glViewPort, glEnable etc..."); 
	}

	void post() { 
		glDisable(GL_DEPTH_TEST);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glUseProgram(0);
		//TODO_D("Unset any gl settings"); 
	}

	GPass(const char *shaderName, const char *fboName) : RenderPass(shaderName, fboName) {}

	void draw(const Camera &c, const Geometry &g)	
	{
		setUniform("Projection",	nsfw::UNIFORM::TYPE::MAT4, glm::value_ptr(c.getProjection()));
		setUniform("View",			nsfw::UNIFORM::TYPE::MAT4, glm::value_ptr(c.getView()));
		setUniform("Model",			nsfw::UNIFORM::TYPE::MAT4, glm::value_ptr(g.transform));

		setUniform("Diffuse",		nsfw::UNIFORM::TEX2,  g.diffuse,  0);
		setUniform("Normal",		nsfw::UNIFORM::TEX2,  g.normal,   1);
		setUniform("Specular",		nsfw::UNIFORM::TEX2,  g.specular, 2);

		setUniform("SpecularPower", nsfw::UNIFORM::FLO1, (void*)&g.specPower);

		glBindVertexArray(*g.mesh);
		glDrawElements(GL_TRIANGLES, *g.tris, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		//TODO_D("bindVAO and Draw Elements!");
	}
};