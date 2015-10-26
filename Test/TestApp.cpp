#include "TestApp.h"
#include "Window.h"

void TestApp::onStep() {

	float time = nsfw::Window::instance().getTime();
	go.trasform = glm::rotate(time * 10, glm::vec3(0, 1, 0)) * glm::scale(5.f, 5.f, 5.f);

	fp.prep();
	fp.draw(go, cam);
	fp.post();

	cp.prep();
	cp.draw();
	cp.post();
};

void TestApp::onPlay() {

	auto& ass = nsfw::Assets::instance();

	ass.loadShader("basic", "./shaders/BasicV.glsl", "./shaders/BasicF.glsl");
	ass.loadShader("composit", "./shaders/CompV.glsl", "./shaders/CompF.glsl");

	//ass.loadOBJ("obj", "./assets/cube.obj");
	ass.loadTexture("tex", "./assets/crate.png");
	ass.loadFBX("fbx", "./assets/soulspear/soulspear.fbx");
	const char* fboTexNames[] = { "fboTex1" };
	unsigned fboTexDepths[] = { nsfw::DEPTH::RGB };
	ass.makeFBO("testBuff", 800, 600, 1, fboTexNames, fboTexDepths);
	cam.lookAt(glm::vec3(10, 10, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	go.trasform = glm::mat4(1);
	go.diffuse = "fbx_soulspear_diffuse.tga";
	//go.diffuse = "tex";
	go.mesh = "fbx_SoulSpear_Low:SoulSpear_Low1";
	go.tris = "fbx_SoulSpear_Low:SoulSpear_Low1";
	//go.mesh = "obj";
	//go.tris = "obj";

	fp.shader = "basic";
	fp.fbo = "testBuff";
	//fp.fbo = "Screen";

	cp.diffusePassTex = "fboTex1";
	cp.shader = "composit";

	cam.aspect = 800 / 600.f;//nsfw::Window::instance().getWidth() / (float)nsfw::Window::instance().getHeight();
}

void TestApp::onInit() {
	
};

void TestApp::onTerm() {

};