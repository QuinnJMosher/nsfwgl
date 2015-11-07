#include "TestApp.h"
#include "Window.h"
#include "glm/ext.hpp"
#include "FlyCamera.h"

void TestApp::onStep() {

	float time = nsfw::Window::instance().getTime();
	go1.trasform = glm::rotate(time * 10, glm::vec3(0, 1, 0)) * glm::scale(3.f, 3.f, 3.f);

	cam->update(time);

	gp.prep();
	gp.draw(go1, cam);
	gp.draw(go2, cam);
	gp.draw(go3, cam);
	gp.post();

	sp.prep();
	sp.draw(go3, dl);
	sp.draw(go1, dl);
	sp.draw(go2, dl);
	sp.post();

	lp.prep();
	lp.draw(dl, cam);
	lp.post();

	/*slp.prep();
	slp.draw(go3, dl, cam);
	slp.draw(go1, dl, cam);
	slp.draw(go2, dl, cam);
	slp.post();*/

	cp.prep();
	cp.draw();
	cp.post();

	/*fp.prep();
	fp.draw();
	fp.post();*/
};

void TestApp::onPlay() {

	ScrW = (float)nsfw::Window::instance().getWidth();
	ScrH = (float)nsfw::Window::instance().getHeight();

	auto& ass = nsfw::Assets::instance();

	ass.loadShader("basic", "./shaders/BasicV.glsl", "./shaders/BasicF.glsl");
	ass.loadShader("composit", "./shaders/CompV.glsl", "./shaders/CompF.glsl");
	//load GeoShader

	//ass.loadTexture("tex", "./assets/crate.png");
	ass.loadFBX("spear", "./assets/soulspear/soulspear.fbx");
	ass.loadFBX("bunny", "./assets/bunny/Bunny.fbx");

	const char* baseTexNames[] = { "fboTex1" };
	unsigned baseTexDepths[] = { nsfw::DEPTH::RGB };
	ass.makeFBO("testBuff", ScrW, ScrH, 1, baseTexNames, baseTexDepths);


	go1.trasform = glm::mat4(1);
	go1.diffuse = "spear_soulspear_diffuse.tga";
	go1.mesh = "spear_SoulSpear_Low:SoulSpear_Low1";
	go1.tris = "spear_SoulSpear_Low:SoulSpear_Low1";

	go2.trasform = glm::translate(glm::vec3(-10.0f, 0.0f, 0.0f)) * glm::scale(glm::vec3(0.7f, 0.7f, 0.7f));
	go2.diffuse = "Cyan";
	go2.mesh = "bunny_Mesh";
	go2.tris = "bunny_Mesh";


	go3.trasform = glm::rotate(90.f, glm::vec3(1, 0, 0)) * glm::scale(20.f,20.f,1.f);
	go3.mesh = "Quad";
	go3.tris = "Quad";
	go3.diffuse = "Cyan";

	fp.shader = "basic";
	fp.fbo = "testBuff";

	//setup GeoPass
	const char* geoTexNames[] = { "geoDiffuse", "geoNormal", "geoPos" };
	unsigned geoTexDepths[] = { nsfw::DEPTH::RGB, nsfw::DEPTH::RGB, nsfw::DEPTH::RGB };
	ass.makeFBO("geoBuff", ScrW, ScrH, 3, geoTexNames, geoTexDepths);
	gp.fbo = "geoBuff";
	ass.loadShader("geoShader", "./shaders/GeoV.glsl", "./shaders/GeoF.glsl");
	gp.shader = "geoShader";

	//setup LightPass
	const char* lightTexNames[] = { "lightTex" };
	unsigned lightTexDepths[] = { nsfw::DEPTH::RGB };
	ass.makeFBO("lightBuff", ScrW, ScrH, 1, lightTexNames, lightTexDepths);
	lp.fbo = "lightBuff";
	ass.loadShader("lightShader", "./shaders/lightV.glsl", "./shaders/lightF.glsl");
	lp.shader = "lightShader";
	lp.PositionMap = "geoPos";
	lp.NormalMap = "geoNormal";
	lp.ShadowMap = "shadowTex";

	//setup shadow pass
	const char* shadowTexNames[] = { "shadowTex" };
	unsigned shadowTexDepths[] = { nsfw::DEPTH::RGB };
	ass.makeFBO("shadowBuff", 1024, 1024, 1, shadowTexNames, shadowTexDepths);
	sp.fbo = "shadowBuff";
	ass.loadShader("shadowShader", "./shaders/ShadowV.glsl", "./shaders/ShadowF.glsl");
	sp.shader = "shadowShader";
	sp.ScrWidth = ScrW;
	sp.ScrHeight = ScrH;
	sp.BufWidth = 1024;
	sp.BufHeight = 1024;

	//setup shadow light pass
	/*const char* shadLtTexNames[] = { "shadLtTex" };
	unsigned shadLtDepths[] = { nsfw::DEPTH::RGB };
	ass.makeFBO("shadLtBuff", ScrW, ScrH, 1, shadLtTexNames, shadLtDepths);
	slp.fbo = "shadLtBuff";*/
	ass.loadShader("shadLtShader", "./shaders/ShadowForwardV.glsl", "./shaders/ShadowForwardF.glsl");
	slp.shader = "shadLtShader";
	slp.ShadowMap = "shadowTex";

	//setup light
	dl.direction = glm::normalize(glm::vec3(0, -1, 1));
	dl.color = glm::vec3(0.7f, 0.7f, 0.7f);

	//setup composite
	cp.diffusePassTex = "geoDiffuse";
	cp.lightPassTex = "lightTex";
	cp.shader = "composit";

	//cp.lightPassTex = "geoNormal";

	//forwad pass directly draws one texture
	fp.Tex = "shadLtTex";

	//setup camera
	//fly cam only
	FlyCamera* flyCamPrep = new FlyCamera();
	flyCamPrep->speed = 10;
	flyCamPrep->mouseSen = 20;
	cam = flyCamPrep;
	//cam = new Camera();
	cam->lookAt(glm::vec3(0, 10, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	cam->aspect = ScrW / ScrH;
}

void TestApp::onInit() {
	
};

void TestApp::onTerm() {

};