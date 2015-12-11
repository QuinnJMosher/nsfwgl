#version 410

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Normal;
layout(location = 2) in vec4 Tangent;
layout(location = 3) in vec2 TexCoord;

out vec4 vPosition;
out vec4 vNormal;
out vec4 vTan;
out vec4 vBiTan;
out vec4 vShadowCoord;
out vec2 vUV;

uniform mat4 texSpaceOff;

uniform mat4 lightProjection;
uniform mat4 lightView;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

void main() {
	vPosition = View * Model * Position;
	vNormal = Model * Normal;
	vTan = normalize(Model * Tangent);
	vBiTan = normalize(Model * vec4(cross(Normal.xyz, Tangent.xyz), 0));
	vUV = TexCoord;
	
	gl_Position = Projection * View * Model * Position;
	vShadowCoord = texSpaceOff * lightProjection * lightView * Model * Position;
}