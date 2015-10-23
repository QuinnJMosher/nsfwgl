#include "TestApp.h"
#include "Window.h"

void TestApp::onStep() {

	float time = nsfw::Window::instance().getTime();
	go.trasform = glm::rotate(time * 10, glm::vec3(0, 1, 0));

	fp.prep();
	fp.draw(go, cam);
	fp.post();
};

void TestApp::onPlay() {

	auto& ass = nsfw::Assets::instance();

	ass.loadOBJ("obj", "./assets/cube.obj");
	cam.lookAt(glm::vec3(10, 10, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	go.trasform = glm::mat4(1);
	go.diffuse = "Cyan";
	go.mesh = "obj";
	go.tris = "obj";

	fp.shader = "basic";
	//fp.fbo = "Screen";

	cam.aspect = 800 / 600.f;//nsfw::Window::instance().getWidth() / (float)nsfw::Window::instance().getHeight();
}

void TestApp::onInit() {
	nsfw::Assets::instance().loadShader("basic", "./shaders/BasicV.glsl", "./shaders/BasicF.glsl");
	
};

void TestApp::onTerm() {

};