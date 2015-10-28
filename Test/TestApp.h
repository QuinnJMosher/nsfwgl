#pragma once
#include "nsfw.h"
#include "Application.h"

#include "Camera.h"
#include "GameObject.h"
#include "ForwardPass.h"
#include "GeoPass.h"
#include "lightPass.h"
#include "CompPass.h"

class TestApp : public nsfw::Application {
	Camera cam;
	GameObject go;
	DirectionLight dl;
	ForwardPass fp;
	GeoPass gp;
	LightPass lp;
	CompPass cp;

public:
	void onStep();
	void onPlay();
	void onInit();
	void onTerm();
};