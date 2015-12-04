#version 410

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Velocity;
layout(location = 2) in float size;
layout(location = 3) in float lifeTime;

out vec3 pPosition;
out float pLifeTime;

void main() {
	pLifeTime = lifeTime;
	pPosition = Position;
}