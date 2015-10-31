#version 410

layout(location = 0) in vec4 Position;

uniform mat4 lightProjection;
uniform mat4 lightView;
uniform mat4 Model;

void main() {
	gl_Position = lightProjection * lightView * Model * Position;
}