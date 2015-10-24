#pragma once
#include "nsfw.h"
#include "Application.h"

#include "Camera.h"
#include "GameObject.h"
#include "ForwardPass.h"
#include "CompPass.h"

class TestApp : public nsfw::Application {
	Camera cam;
	GameObject go;
	ForwardPass fp;
	CompPass cp;

public:
	void onStep();
	void onPlay();
	void onInit();
	void onTerm();
};