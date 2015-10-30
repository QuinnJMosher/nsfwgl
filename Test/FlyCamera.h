#pragma once
#include "Camera.h"

class Window;

class FlyCamera : public Camera {
	float lastTime;

	glm::vec3 up, forward, right;
	glm::vec2 lastMousePos;

public:
	void start();
	virtual void update(const float time);
	virtual void lookAt(glm::vec3 in_pos, glm::vec3 in_target, glm::vec3 in_up);
	float mouseSen;
	float speed;
};