#version 410

in vec4 vPosition;
in vec3 vNormal;
in vec3 vTangent;
in vec3 vBiTangent;
in vec2 vUV;

uniform sampler2D Diffuse;
uniform sampler2D Normal;
uniform sampler2D Specular;

uniform float SpecularPower;

layout(location = 0) out vec3 gpassAlbedo;
layout(location = 1) out vec3 gpassPosition;
layout(location = 2) out vec3 gpassNormal;

void main() {
	
	gpassAlbedo = texture(Diffuse, vUV).xyz;
	
	gpassPosition = vPosition.xyz;
	
	mat3 TBN = mat3(normalize(vTangent),
					normalize(vBiTangent),
					normalize(vNormal));
	vec3 N = texture(Normal, vUV).xyz;
	gpassNormal = normalize(TBN * N) * SpecularPower;
}