#version 410

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Velocity;
layout(location = 2) in float Size;
layout(location = 3) in float lifeTime;

out vec3 pPosition;
out float pSize;
out float pLifeTime;

void main() {
	pLifeTime = lifeTime;
	pSize = Size;
	pPosition = Position;
}