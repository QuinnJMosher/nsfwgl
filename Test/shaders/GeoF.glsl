#version 410

in vec4 vPosition;
in vec4 vNormal;
in vec2 vTexCoord;

layout(location = 0) out vec3 tAlbedo;
layout(location = 1) out vec3 tNormals;
layout(location = 2) out vec3 tPositions;

uniform sampler2D Diffuse;

void main() {
	tAlbedo = texture(Diffuse, vTexCoord).xyz;
	tPositions = vPosition.xyz;
	tNormals = vNormal.xyz;
}