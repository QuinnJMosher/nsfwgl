#version 410

in vec2 vUV;

out vec3 LightOut;

uniform vec3 CameraPos;

uniform vec3 LightDirection;
uniform vec3 LightColor;

uniform sampler2D PositionMap;
uniform sampler2D NormalMap;

void main() {

	vec3 normal = normalize(texture(NormalMap, vUV)).xyz;
	float specularPow = length(texture(NormalMap, vUV));
	vec3 position = texture(PositionMap, vUV).xyz;
	
	//ambient
	
	float lambert = max(0.0f, dot(normal, -LightDirection));
	vec3 diffuse = LightColor * lambert;
	
	vec3 eye = normalize(CameraPos - position);
	vec3 R = normalize(reflect(LightDirection, normal));
	
	float specTerm = pow(max(0.0f, dot(R, eye)), specularPow);
	vec3 specular = LightColor * specTerm;
	specular = clamp(specular, 0.0f, 1.0f);
	
	LightOut = (specular + diffuse);
	
}