#version 410

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Normal;

out vec4 vNormal;

uniform mat4 lightProjection;
uniform mat4 lightView;
uniform mat4 Model;

void main() {
	vNormal = Normal;
	gl_Position = lightProjection * lightView * Model * Position;
}