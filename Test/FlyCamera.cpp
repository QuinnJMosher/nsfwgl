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
		input_RL -= (speed * deltaTime);
	}
	if (context.getKey(68)) {//d
		input_RL += (speed * deltaTime);
	}

	//create movement mat
	glm::mat4 totalMovementMat = glm::translate((forward * input_UD) + (right * input_RL));
	transform = totalMovementMat * transform;

	//rotation input
	double mouseX, mouseY;
	context.getMouse(&mouseX, &mouseY);
	glm::vec2 deltaMouse = glm::vec2(mouseX - lastMousePos.x, mouseY - lastMousePos.y);
	lastMousePos = glm::vec2(mouseX, mouseY);

	glm::vec3 currentPos = glm::vec3(transform[3]);

	glm::vec3 inFrontOfMe = ((forward * 10.f) + currentPos);
	glm::vec3 turnRightLeft = glm::rotate(forward, (mouseSen * deltaTime) * -deltaMouse.y, right);
	glm::vec3 turnUpDown = glm::rotate(forward, (mouseSen * deltaTime) * -deltaMouse.x, up);


	if (context.getKey('E')) {
		this->lookAt(currentPos, inFrontOfMe + (turnRightLeft + turnUpDown) * 10.f, up);
	}
}