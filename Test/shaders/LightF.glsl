#version 410

in vec2 vTexCoord;
out vec3 LightOutput;

uniform vec3 CameraPos;
uniform float SpecPow = 2;

uniform vec3 lightDirection;
uniform vec3 lightDiffuse;

uniform sampler2D PosMap;
uniform sampler2D NormMap;

void main() {
	vec3 normal = normalize(texture(NormMap, vTexCoord).xyz);
	vec3 position = texture(PosMap, vTexCoord).xyz;
	
	vec3 ambient = lightDiffuse * (1.f / 3.f);
	
	float lambert = max(0, dot(normal, -lightDirection));
	vec3 diffuse = lightDiffuse * lambert;
	
	vec3 eye = normalize(CameraPos - position);
	vec3 R = normalize(reflect(lightDirection, normal));
	
	float specTerm = pow(max(0.0f, dot(R, eye)), SpecPow);
	vec3 specular = lightDiffuse * specTerm;
	specular = clamp(specular, 0.0f, 1.0f);
	
	LightOutput = (ambient + diffuse + specular);
}