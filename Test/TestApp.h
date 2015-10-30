#pragma once
#include "nsfw.h"
#include "Application.h"

//objects
#include "Camera.h"
#include "GameObject.h"
//passes
#include "GeoPass.h"
#include "lightPass.h"
#include "ShadowPass.h"
#include "ShadowLighting.h"

#include "ForwardPass.h"
#include "CompPass.h"

class TestApp : public nsfw::Application {
	
	//objects
	Camera cam;
	GameObject go1;
	GameObject go2;
	DirectionLight dl;

	//passes
	GeoPass gp;
	LightPass lp;
	ShadowPass sp;
	ShadowLightPass slp;
	//final passes
	ForwardPass fp;
	CompPass cp;

	float ScrW, ScrH;

public:
	void onStep();
	void onPlay();
	void onInit();
	void onTerm();
};