#include "TestApp.h"
#include "Window.h"
#include "glm/ext.hpp"

void TestApp::onStep() {

	float time = nsfw::Window::instance().getTime();
	go.trasform = glm::rotate(time * 10, glm::vec3(0, 1, 0)) * glm::scale(5.f, 5.f, 5.f) * glm::translate(0.f, -2.f, 0.f);

	//fp.prep();
	//fp.draw(go, cam);
	//fp.post();

	gp.prep();
	gp.draw(go, cam);
	gp.post();

	lp.prep();
	lp.draw(dl, cam);
	lp.post();

	cp.prep();
	cp.draw();
	cp.post();
};

void TestApp::onPlay() {

	auto& ass = nsfw::Assets::instance();

	ass.loadShader("basic", "./shaders/BasicV.glsl", "./shaders/BasicF.glsl");
	ass.loadShader("composit", "./shaders/CompV.glsl", "./shaders/CompF.glsl");
	//load GeoShader

	//ass.loadOBJ("obj", "./assets/cube.obj");
	ass.loadTexture("tex", "./assets/crate.png");
	ass.loadFBX("fbx", "./assets/soulspear/soulspear.fbx");

	const char* baseTexNames[] = { "fboTex1" };
	unsigned baseTexDepths[] = { nsfw::DEPTH::RGB };
	ass.makeFBO("testBuff", 800, 600, 1, baseTexNames, baseTexDepths);

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

	//setup GeoPass
	const char* geoTexNames[] = { "geoDiffuse", "geoNormal", "geoDepth" };
	unsigned geoTexDepths[] = { nsfw::DEPTH::RGB, nsfw::DEPTH::RGB, nsfw::DEPTH::RGB };
	ass.makeFBO("geoBuff", 800, 600, 3, geoTexNames, geoTexDepths);
	gp.fbo = "geoBuff";
	ass.loadShader("geoShader", "./shaders/GeoV.glsl", "./shaders/GeoF.glsl");
	gp.shader = "geoShader";

	//setup LightPass
	const char* lightTexNames[] = { "lightTex" };
	unsigned lightTexDepths[] = { nsfw::DEPTH::RGB };
	ass.makeFBO("lightBuff", 800, 600, 1, lightTexNames, lightTexDepths);
	lp.fbo = "lightBuff";
	ass.loadShader("lightShader", "./shaders/lightV.glsl", "./shaders/lightF.glsl");
	lp.shader = "lightShader";
	lp.PositionMap = "geoDepth";
	lp.NormalMap = "geoNormal";

	//setup light
	dl.direction = glm::normalize(glm::vec3(-3, 0, 0));
	dl.color = glm::vec3(0.7f, 0.7f, 0.7f);

	//setup composite
	cp.diffusePassTex = "geoDiffuse";
	cp.lightPassTex = "lightTex";
	cp.shader = "composit";

	cam.aspect = 800 / 600.f;//nsfw::Window::instance().getWidth() / (float)nsfw::Window::instance().getHeight();
}

void TestApp::onInit() {
	
};

void TestApp::onTerm() {

};