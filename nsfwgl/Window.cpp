#include "Window.h"

#include "gl_core_4_4.h"
#include "nsfw.h"
#include "GLFW\glfw3.h"

#include <glm\glm.hpp>
#include <glm\ext.hpp>


void nsfw::Window::init(unsigned width, unsigned height)
{
	//TODO_D("Should create and set an active windowing context. ONLY GLFW! No GL!");
	this->width = width;
	this->height = height;

	if (window != nullptr) {
		#ifdef _DEBUG
		std::cerr << "Close Current glfw context before calling init again!\n";
		#endif
		return;
	}

	if (glfwInit() == false) {
		return;
	}

	window = glfwCreateWindow(width, height, "nsfwgl", nullptr, nullptr);
	if (window == nullptr) {
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	//ogl Load funcs?
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		glfwDestroyWindow(window);
		glfwTerminate();
		return;
	}

}

void nsfw::Window::step()
{
	//TODO_D("GLFW poll events and swap buffers is all that should really be here! No GL!");
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void nsfw::Window::term()
{
	//TODO();
	glfwDestroyWindow(window);
	window = nullptr;//probably redundant
	glfwTerminate();

	width = 0;
	height = 0;
}

float nsfw::Window::getTime() const
{
	//TODO();
	return glfwGetTime();
}

bool nsfw::Window::getKey(unsigned k) const
{
	//TODO();
	return glfwGetKey(window, k);
}

bool nsfw::Window::getShouldClose() const
{
	//TODO();
	return glfwWindowShouldClose(window);
}

unsigned nsfw::Window::getWidth() const
{
	//TODO();
	return width;
}

unsigned nsfw::Window::getHeight() const
{
	//TODO();
	return height;
}

glm::mat4 nsfw::Window::getTexelAdjustmentMatrix() const
{
	TODO_D("Implemented, not tested.");

	glm::vec3 texelSize = 1.0f/glm::vec3(width,height,0);
	glm::vec3 halfTexel = texelSize * 0.5f; // bottom left

	// scale up to the appropriate size, then shift it to line up w/center of texels
	return glm::translate(halfTexel) * glm::scale(glm::vec3(1, 1, 1) - texelSize);	
}

void nsfw::Window::getMouse(double* x, double* y) {
	glfwGetCursorPos(window, x, y);
}