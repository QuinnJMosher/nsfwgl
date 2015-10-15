#pragma once
#include "../nsfwgl/render.h"

#include "Camera.h"
#include "Geometry.h"

class GPass : public nsfw::RenderPass
{
public:	
	void prep();

	void post();
	GPass(const char *shaderName, const char *fboName) : RenderPass(shaderName, fboName) {}

	void draw(const Camera &c, const Geometry &g);
};