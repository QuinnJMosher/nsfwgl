#pragma once
#include "../nsfwgl/gl_core_4_4.h"
#include "../nsfwgl/nsfw.h"
#include "../nsfwgl/render.h"
#include "Camera.h"

class CPass : public nsfw::RenderPass
{
	nsfw::Asset<nsfw::ASSET::TEXTURE> albedo, position, normal, light;

public:
											
	CPass(const char *shaderName, const char *fboName) 
						  : RenderPass(shaderName, fboName), albedo("GPassAlbedo"), position("GPassPosition"), // NAMES ARE FROM ASSET LIBRARY!
											    normal("GPassNormal"), light("LPassColor")
												 {}


	void prep() { 
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(1, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(*shader);
		//TODO_D("glUseProgram, glClear, glBindFrameBuffer, glViewPort, glEnable etc..."); 
	}
	void post() { 
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glUseProgram(0);
		//TODO_D("Unset any gl settings"); 
	}


	void draw()
	{

		// Set uniforms for textures we're going to composite-> NAMES ARE FROM SHADER!
		setUniform("Albedo",	nsfw::UNIFORM::TEX2, albedo,   0);
		setUniform("Position",	nsfw::UNIFORM::TEX2, position, 1);
		setUniform("Normal",	nsfw::UNIFORM::TEX2, normal,   2);
		setUniform("Light",		nsfw::UNIFORM::TEX2, light,    3);

		setUniform("TexelScalar", nsfw::UNIFORM::MAT4, glm::value_ptr(nsfw::Window::instance().getTexelAdjustmentMatrix()));

		unsigned quadVAOHandle = nsfw::Assets::instance().get<nsfw::ASSET::VAO>("Quad");
		unsigned quadNumtris   = nsfw::Assets::instance().get<nsfw::ASSET::VERTEX_COUNT>("Quad");

		glBindVertexArray(quadVAOHandle);
		glDrawArrays(GL_TRIANGLES, 0, quadNumtris);
		//TODO_D("GL BindVAO/DrawElements with quad size and vao");
	}
};