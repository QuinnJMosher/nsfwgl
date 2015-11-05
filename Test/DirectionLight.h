#pragma once
#include "glm\glm.hpp"

struct DirectionLight {
	glm::vec3 direction;
	glm::vec3 color;

	glm::mat4 getView()		  const { return glm::lookAt(-direction, glm::vec3(0), glm::vec3(0, 1, 0)); }
	glm::mat4 getProjection() const { return glm::ortho<float>(-20, 20, -20, 20, -20, 20); }
};