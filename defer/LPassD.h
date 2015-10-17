#pragma once
#include "../nsfwgl/gl_core_4_4.h"
#include "../nsfwgl/nsfw.h"
#include "../nsfwgl/render.h"

#include "Light.h"
#include "Camera.h"

class LPassD : public nsfw::RenderPass
{
	nsfw::Asset<nsfw::ASSET::TEXTURE> position, normal;

public:
	LPassD(const char *shaderName, const char *fboName) : RenderPass(shaderName, fboName),
														position("GPassPosition"), normal("GPassNormal") {}

	void prep() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);

		glBindFramebuffer(GL_FRAMEBUFFER, *fbo);
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(*shader);
		//TODO_D("glUseProgram, glClear, glBindFrameBuffer, glViewPort, glEnable etc..."); 
	}
	void post() { 
		glDisable(GL_BLEND);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glUseProgram(0);
		//TODO_D("Unset any gl settings"); 
	}


	void draw(const Camera &c, const LightD &l)
	{
		setUniform("Projection", nsfw::UNIFORM::TYPE::MAT4, glm::value_ptr(c.getProjection()));
		setUniform("View",       nsfw::UNIFORM::TYPE::MAT4, glm::value_ptr(c.getView()));
		setUniform("Model",		 nsfw::UNIFORM::TYPE::MAT4, glm::value_ptr(c.transform));

		setUniform("PositionMap", nsfw::UNIFORM::TYPE::TEX2, position, 0);
		setUniform("NormalMap",   nsfw::UNIFORM::TYPE::TEX2, normal,   1);

		setUniform("LightDirection", nsfw::UNIFORM::TYPE::FLO3, glm::value_ptr(l.direction));
		setUniform("LightColor",     nsfw::UNIFORM::TYPE::FLO3, glm::value_ptr(l.color));

		setUniform("TexelScalar",    nsfw::UNIFORM::MAT4, glm::value_ptr(nsfw::Window::instance().getTexelAdjustmentMatrix()));

		unsigned quadVAOHandle  = nsfw::Assets::instance().get<nsfw::ASSET::VAO>("Quad");
		unsigned quadNumtris    = nsfw::Assets::instance().get<nsfw::ASSET::VERTEX_COUNT>("Quad");


		glBindVertexArray(quadVAOHandle);
		glDrawArrays(GL_TRIANGLES, 0, quadNumtris);
		//TODO_D("GL BindVAO/DrawElements with quad size and vao");
	}
};