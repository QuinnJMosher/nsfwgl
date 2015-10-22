#include "GPass.h"
#include "../nsfwgl/gl_core_4_4.h"

#include "../nsfwgl/Assets.h"

void GPass::prep() {
	glEnable(GL_DEPTH_TEST);
	//glBindFramebuffer(GL_FRAMEBUFFER, *fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(0, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(*shader);
	//TODO_D("glUseProgram, glClear, glBindFrameBuffer, glViewPort, glEnable etc..."); 
}

void GPass::post() {
	glDisable(GL_DEPTH_TEST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glUseProgram(0);
	//TODO_D("Unset any gl settings"); 
}

void GPass::draw(const Camera &c, const Geometry &g)
{

	setUniform("Projection", nsfw::UNIFORM::TYPE::MAT4, glm::value_ptr(c.getProjection()));
	setUniform("View", nsfw::UNIFORM::TYPE::MAT4, glm::value_ptr(c.getView()));
	setUniform("Model", nsfw::UNIFORM::TYPE::MAT4, glm::value_ptr(g.transform));

	unsigned texHandle = *g.diffuse;
	setUniform("Diffuse",  nsfw::UNIFORM::TEX2, &texHandle, 0);
	texHandle = *g.normal;
	setUniform("Normal",   nsfw::UNIFORM::TEX2, &texHandle, 1);
	texHandle = *g.specular;
	setUniform("Specular", nsfw::UNIFORM::TEX2, &texHandle, 2);

	setUniform("SpecularPower", nsfw::UNIFORM::FLO1, (void*)&g.specPower);

	unsigned cubeVAO = nsfw::Assets::instance().get<nsfw::ASSET::VAO>("Cube");
	unsigned cubeCT = nsfw::Assets::instance().get<nsfw::ASSET::VERTEX_COUNT>("Cube");
	glBindVertexArray(cubeVAO);
	glDrawElements(GL_TRIANGLES, cubeCT, GL_UNSIGNED_INT, 0);

	/*glBindVertexArray(*g.mesh);
	glDrawElements(GL_TRIANGLES, *g.tris, GL_UNSIGNED_INT, 0);*/
	glBindVertexArray(0);
	//TODO_D("bindVAO and Draw Elements!");
}