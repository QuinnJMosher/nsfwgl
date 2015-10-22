#version 410

layout (location = 0) in vec4 Position;
layout (location = 3) in vec2 TexCoord;

out vec2 vUV;

void main() {
	vUV = TexCoord;
	gl_Position = Position;
}