#pragma once
#include "Window.h"
#include "glm\glm.hpp"
#include "glm\ext.hpp"

class Camera
{
	public:
	glm::mat4 transform;
	float near, far, aspect, fov;

	Camera() : near(1), far(100), aspect(nsfw::Window::instance().getWidth() / (float)nsfw::Window::instance().getHeight()), fov(90) {}

	virtual void update(const float time) {}
	virtual void lookAt(glm::vec3 in_pos, glm::vec3 in_target, glm::vec3 in_up) { transform = glm::inverse(glm::lookAt(in_pos, in_target, in_up)); }
	glm::mat4 getView()		  const { return glm::inverse(transform); }
	glm::mat4 getProjection() const { return glm::perspective(fov, aspect, near, far); }
};