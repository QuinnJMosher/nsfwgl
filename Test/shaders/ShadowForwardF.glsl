#version 410

in vec4 vPosition;
in vec4 vNormal;
in vec4 vTan;
in vec4 vBiTan;
in vec4 vShadowCoord;
in vec2 vUV;

out vec4 FragColor;

uniform vec3 lightDirection;
uniform float shadowBais = 0.01;

uniform sampler2D shadowMap;
uniform sampler2D albedo;
uniform sampler2D normalMap;

void main() {
	
	float d = max(0, dot(normalize(vNormal.xyz), lightDirection));
	
	vec4 shadowColor = texture(shadowMap, vShadowCoord.xy);
	
	if (shadowColor.z < vShadowCoord.z - shadowBais) {
		d = 0;
	}
	
	FragColor = vec4(d, d, d, 1);
}