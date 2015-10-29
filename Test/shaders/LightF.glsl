#version 410

in vec2 vTexCoord;
out vec3 LightOutput;

uniform vec3 lightDirection;
uniform vec3 lightDiffuse;

uniform sampler2D PosMap;
uniform sampler2D NormMap;

void main() {
	vec3 normal = normalize(texture(NormMap, vTexCoord).xyz);
	vec3 position = texture(PosMap, vTexCoord).xyz;
	
	float d = max(0, dot(normal, -lightDirection));
	
	LightOutput = (lightDiffuse * d);
}