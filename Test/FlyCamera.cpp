#include "FlyCamera.h"
#include "Window.h"

void FlyCamera::start() {
	auto& context = nsfw::Window::instance();
	
	lastTime = context.getTime();

	double x, y;
	context.getMouse(&x, &y);
	lastMousePos = glm::vec2(x, y);
}

void FlyCamera::lookAt(glm::vec3 in_pos, glm::vec3 in_target, glm::vec3 in_up) {
	up = in_up;
	forward = glm::normalize((in_pos - in_target) * -1.f);
	right = glm::cross(forward, up);
	this->Camera::lookAt(in_pos, in_target, in_up);
}

void FlyCamera::update(const float time) {
	auto& context = nsfw::Window::instance();
	
	float deltaTime = time - lastTime;
	lastTime = time;

	//directional input
	float input_RL = 0;
	float input_UD = 0;
	if (context.getKey(87)) {//w
		input_UD += (speed * deltaTime);
	}
	if (context.getKey(83)) {//s
		input_UD -= (speed * deltaTime);
	}
	if (context.getKey(65)) {//a
		input_RL += (speed * deltaTime);
	}
	if (context.getKey(68)) {//d
		input_RL -= (speed * deltaTime);
	}

	//rotation input
	//TODO
}