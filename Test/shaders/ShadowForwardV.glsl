#version 410

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Normal;

out vec4 vNormal;
out vec4 vShadowCoord;

uniform mat4 texSpaceOff;

uniform mat4 lightProjection;
uniform mat4 lightView;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

void main() {
	vNormal = Normal;
	gl_Position = Projection * View * Model * Position;

	vShadowCoord = (texSpaceOff * (lightProjection * lightView)) * Position;
}