#version 410

layout (location = 0) in vec4 Position;
layout (location = 3) in vec2 TexCoord;

out vec2 vUV;
out vec4 vPos;

uniform mat4 View;
uniform mat4 Projection;

void main() {
	vUV = TexCoord;
	vPos = (Projection * View) * Position;
	gl_Position = (Projection * View) * Position;
}