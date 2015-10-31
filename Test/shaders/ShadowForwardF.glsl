#version 410

in vec4 vNormal;
out vec3 FragColor;

uniform vec3 lightDirection;

void main() {
	
	float d = max(0, dot(normalize(normal), lightDirection));
	
	LightOutput = vec3(d, d, d, 1);
}