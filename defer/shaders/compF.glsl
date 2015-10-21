#version 410

in vec2 vUV;

out vec4 fragColor;

uniform sampler2D Albedo;
uniform sampler2D Light;

void main() {
	vec3 light = texture(lightTexture, vUV).rgb;
	vec3 albedo = texture(albedoTexture, vUV).rgb;
	
	FragColor = vec4(albedo * light, 1);
}
