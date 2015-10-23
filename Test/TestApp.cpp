#include "TestApp.h"
#include "Window.h"

void TestApp::onStep() {
	fp.prep();
	fp.draw(go, cam);
	fp.post();
};

void TestApp::onPlay() {
	cam.lookAt(glm::vec3(10, 10, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	go.trasform = glm::mat4(1);
	go.diffuse = "Cyan";
	go.mesh = "Quad";
	go.tris = "Quad";

	fp.shader = "basic";
	//fp.fbo = "Screen";
}

void TestApp::onInit() {
	nsfw::Assets::instance().loadShader("basic", "./shaders/BasicV.glsl", "./shaders/BasicF.glsl");
};

void TestApp::onTerm() {

};